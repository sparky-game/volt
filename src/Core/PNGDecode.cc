#include "PNGDecode.hh"
#include "PNGDecode_Zlib.hh"
#include "PNGDecode_HuffmanTree.hh"

namespace volt::core {
  struct PNGInfo {
    unsigned long width{0};
    unsigned long height{0};
    unsigned long colorType;
    unsigned long bitDepth;
    unsigned long compressionMethod;
    unsigned long filterMethod;
    unsigned long interlaceMethod;
    unsigned long key_r {0};
    unsigned long key_g {0};
    unsigned long key_b {0};
    bool key_defined;
    std::vector<unsigned char> palette;
  };

  struct PNG {
    PNGInfo info;
    int error;
    void decode(std::vector<unsigned char>& out, const unsigned char* in, size_t size, bool convert_to_rgba32);
    void readPngHeader(const unsigned char* in, size_t inlength);
    void unFilterScanline(unsigned char* recon, const unsigned char* scanline, const unsigned char* precon, size_t bytewidth, unsigned long filterType, size_t length);
    void adam7Pass(unsigned char* out,
                   unsigned char* linen,
                   unsigned char* lineo,
                   const unsigned char* in,
                   unsigned long w,
                   size_t passleft,
                   size_t passtop,
                   size_t spacex,
                   size_t spacey,
                   size_t passw,
                   size_t passh,
                   unsigned long bpp);
    static unsigned long readBitFromReversedStream(size_t& bitp, const unsigned char* bits);
    static unsigned long readBitsFromReversedStream(size_t& bitp, const unsigned char* bits, unsigned long nbits);
    void setBitOfReversedStream(size_t& bitp, unsigned char* bits, unsigned long bit);
    unsigned long read32bitInt(const unsigned char* buffer);
    int checkColorValidity(unsigned long colorType, unsigned long bd);
    unsigned long getBpp(const PNGInfo& info);
    int convert(std::vector<unsigned char>& out, const unsigned char* in, PNGInfo& infoIn, unsigned long w, unsigned long h);
    unsigned char paethPredictor(short a, short b, short c);
  };

  void PNG::decode(std::vector<unsigned char>& out, const unsigned char* in, size_t size, bool convert_to_rgba32) {
    error = 0;
    if (size == 0 or in == 0) { error = 48; return; }
    readPngHeader(&in[0], size); if (error) return;
    size_t pos = 33;
    std::vector<unsigned char> idat;
    bool IEND = false;
    info.key_defined = false;
    while (not IEND) {
      if (pos + 8 >= size) { error = 30; return; }
      size_t chunkLength = read32bitInt(&in[pos]); pos += 4;
      if (chunkLength > 2147483647) { error = 63; return; }
      if (pos + chunkLength >= size) { error = 35; return; }
      if (in[pos + 0] == 'I' and in[pos + 1] == 'D' and in[pos + 2] == 'A' and in[pos + 3] == 'T') {
        idat.insert(idat.end(), &in[pos + 4], &in[pos + 4 + chunkLength]);
        pos += (4 + chunkLength);
      }
      else if (in[pos + 0] == 'I' and in[pos + 1] == 'E' and in[pos + 2] == 'N' and in[pos + 3] == 'D') { pos += 4; IEND = true; }
      else if (in[pos + 0] == 'P' and in[pos + 1] == 'L' and in[pos + 2] == 'T' and in[pos + 3] == 'E') {
        pos += 4;
        info.palette.resize(4 * (chunkLength / 3));
        if (info.palette.size() > (4 * 256)) { error = 38; return; }
        for (size_t i = 0; i < info.palette.size(); i += 4) {
          for (size_t j = 0; j < 3; j++) info.palette[i + j] = in[pos++];
          info.palette[i + 3] = 255;
        }
      }
      else if (in[pos + 0] == 't' and in[pos + 1] == 'R' and in[pos + 2] == 'N' and in[pos + 3] == 'S') {
        pos += 4;
        if (info.colorType == 3) {
          if (4 * chunkLength > info.palette.size()) { error = 39; return; }
          for (size_t i = 0; i < chunkLength; i++) info.palette[4 * i + 3] = in[pos++];
        }
        else if (info.colorType == 0) {
          if (chunkLength != 2) { error = 40; return; }
          info.key_defined = 1; info.key_r = info.key_g = info.key_b = 256 * in[pos] + in[pos + 1]; pos += 2;
        }
        else if (info.colorType == 2) {
          if (chunkLength != 6) { error = 41; return; }
          info.key_defined = 1;
          info.key_r = 256 * in[pos] + in[pos + 1]; pos += 2;
          info.key_g = 256 * in[pos] + in[pos + 1]; pos += 2;
          info.key_b = 256 * in[pos] + in[pos + 1]; pos += 2;
        }
        else { error = 42; return; }
      }
      else {
        if (not (in[pos + 0] & 32)) { error = 69; return; }
        pos += (chunkLength + 4);
      }
      pos += 4;
    }
    unsigned long bpp = getBpp(info);
    std::vector<unsigned char> scanlines(((info.width * (info.height * bpp + 7)) / 8) + info.height);
    Zlib zlib;
    error = zlib.decompress(scanlines, idat); if (error) return;
    size_t bytewidth = (bpp + 7) / 8, outlength = (info.height * info.width * bpp + 7) / 8;
    out.resize(outlength);
    unsigned char* out_ = outlength ? &out[0] : 0;
    if (info.interlaceMethod == 0) {
      size_t linestart = 0, linelength = (info.width * bpp + 7) / 8;
      if (bpp >= 8)
        for (unsigned long y = 0; y < info.height; y++)
          {
            unsigned long filterType = scanlines[linestart];
            const unsigned char* prevline = (y == 0) ? 0 : &out_[(y - 1) * info.width * bytewidth];
            unFilterScanline(&out_[linestart - y], &scanlines[linestart + 1], prevline, bytewidth, filterType,  linelength); if (error) return;
            linestart += (1 + linelength);
          }
      else
        {
          std::vector<unsigned char> templine((info.width * bpp + 7) >> 3);
          for (size_t y = 0, obp = 0; y < info.height; y++) {
            unsigned long filterType = scanlines[linestart];
            const unsigned char* prevline = (y == 0) ? 0 : &out_[(y - 1) * info.width * bytewidth];
            unFilterScanline(&templine[0], &scanlines[linestart + 1], prevline, bytewidth, filterType, linelength); if (error) return;
            for (size_t bp = 0; bp < info.width * bpp;) setBitOfReversedStream(obp, out_, readBitFromReversedStream(bp, &templine[0]));
            linestart += (1 + linelength); //go to start of next scanline
          }
        }
    }
    else {
      size_t passw[] = {
        (info.width + 7) / 8,
        (info.width + 3) / 8,
        (info.width + 3) / 4,
        (info.width + 1) / 4,
        (info.width + 1) / 2,
        (info.width + 0) / 2,
        (info.width + 0) / 1
      };
      size_t passh[] = {
        (info.height + 7) / 8,
        (info.height + 7) / 8,
        (info.height + 3) / 8,
        (info.height + 3) / 4,
        (info.height + 1) / 4,
        (info.height + 1) / 2,
        (info.height + 0) / 2
      };
      size_t passstart[7] = {0};
      size_t pattern[] = { 0,4,0,2,0,1,0,0,0,4,0,2,0,1,8,8,4,4,2,2,1,8,8,8,4,4,2,2 };
      for (int i = 0; i < 6; i++) passstart[i + 1] = passstart[i] + passh[i] * ((passw[i] ? 1 : 0) + (passw[i] * bpp + 7) / 8);
      std::vector<unsigned char> scanlineo((info.width * bpp + 7) / 8), scanlinen((info.width * bpp + 7) / 8);
      for (int i = 0; i < 7; i++) adam7Pass(&out_[0],
                                           &scanlinen[0],
                                           &scanlineo[0],
                                           &scanlines[passstart[i]],
                                           info.width,
                                           pattern[i],
                                           pattern[i + 7],
                                           pattern[i + 14],
                                           pattern[i + 21],
                                           passw[i],
                                           passh[i],
                                           bpp);
    }
    if (convert_to_rgba32 and (info.colorType != 6 or info.bitDepth != 8)) {
      std::vector<unsigned char> data = out;
      error = convert(out, &data[0], info, info.width, info.height);
    }
  }

  void PNG::readPngHeader(const unsigned char* in, size_t inlength) {
    if (inlength < 29) { error = 27; return; }
    if (in[0] != 137 or in[1] != 80 or in[2] != 78 or in[3] != 71 or in[4] != 13 or in[5] != 10 or in[6] != 26 or in[7] != 10) { error = 28; return; }
    if (in[12] != 'I' or in[13] != 'H' or in[14] != 'D' or in[15] != 'R') { error = 29; return; }
    info.width = read32bitInt(&in[16]); info.height = read32bitInt(&in[20]);
    info.bitDepth = in[24]; info.colorType = in[25];
    info.compressionMethod = in[26]; if (in[26] != 0) { error = 32; return; }
    info.filterMethod = in[27]; if (in[27] != 0) { error = 33; return; }
    info.interlaceMethod = in[28]; if (in[28] > 1) { error = 34; return; }
    error = checkColorValidity(info.colorType, info.bitDepth);
  }

  void PNG::unFilterScanline(unsigned char* recon, const unsigned char* scanline, const unsigned char* precon, size_t bytewidth, unsigned long filterType, size_t length) {
    switch (filterType) {
    case 0:
      for (size_t i = 0; i < length; i++) recon[i] = scanline[i];
      break;
    case 1:
      for (size_t i = 0; i < bytewidth; i++) recon[i] = scanline[i];
      for (size_t i = bytewidth; i < length; i++) recon[i] = scanline[i] + recon[i - bytewidth];
      break;
    case 2:
      if (precon) {
        for (size_t i = 0; i < length; i++) recon[i] = scanline[i] + precon[i];
      }
      else {
        for (size_t i = 0; i < length; i++) recon[i] = scanline[i];
      }
      break;
    case 3:
      if (precon) {
        for (size_t i = 0; i < bytewidth; i++) recon[i] = scanline[i] + precon[i] / 2;
        for (size_t i = bytewidth; i < length; i++) recon[i] = scanline[i] + ((recon[i - bytewidth] + precon[i]) / 2);
      }
      else {
        for (size_t i = 0; i < bytewidth; i++) recon[i] = scanline[i];
        for (size_t i = bytewidth; i < length; i++) recon[i] = scanline[i] + recon[i - bytewidth] / 2;
      }
      break;
    case 4:
      if (precon) {
        for (size_t i = 0; i < bytewidth; i++) recon[i] = scanline[i] + paethPredictor(0, precon[i], 0);
        for (size_t i = bytewidth; i < length; i++) recon[i] = scanline[i] + paethPredictor(recon[i - bytewidth], precon[i], precon[i - bytewidth]);
      }
      else {
        for (size_t i = 0; i < bytewidth; i++) recon[i] = scanline[i];
        for (size_t i = bytewidth; i < length; i++) recon[i] = scanline[i] + paethPredictor(recon[i - bytewidth], 0, 0);
      }
      break;
    default:
      error = 36;
      return;
    }
  }

  void PNG::adam7Pass(unsigned char* out,
                      unsigned char* linen,
                      unsigned char* lineo,
                      const unsigned char* in,
                      unsigned long w,
                      size_t passleft,
                      size_t passtop,
                      size_t spacex,
                      size_t spacey,
                      size_t passw,
                      size_t passh,
                      unsigned long bpp) {
    if (passw == 0) return;
    size_t bytewidth = (bpp + 7) / 8, linelength = 1 + ((bpp * passw + 7) / 8);
    for (unsigned long y = 0; y < passh; y++) {
      unsigned char filterType = in[y * linelength], *prevline = (y == 0) ? 0 : lineo;
      unFilterScanline(linen, &in[y * linelength + 1], prevline, bytewidth, filterType, (w * bpp + 7) / 8); if (error) return;
      if (bpp >= 8) {
        for (size_t i = 0; i < passw; i++) {
          for (size_t b = 0; b < bytewidth; b++) {
            out[bytewidth * w * (passtop + spacey * y) + bytewidth * (passleft + spacex * i) + b] = linen[bytewidth * i + b];
          }
        }
      }
      else {
        for (size_t i = 0; i < passw; i++) {
          size_t obp = bpp * w * (passtop + spacey * y) + bpp * (passleft + spacex * i), bp = i * bpp;
          for (size_t b = 0; b < bpp; b++) setBitOfReversedStream(obp, out, readBitFromReversedStream(bp, &linen[0]));
        }
      }
      unsigned char* temp = linen;
      linen = lineo;
      lineo = temp;
    }
  }

  unsigned long PNG::readBitFromReversedStream(size_t& bitp, const unsigned char* bits) {
    unsigned long result = (bits[bitp >> 3] >> (7 - (bitp & 0x7))) & 1;
    bitp++;
    return result;
  }

  unsigned long PNG::readBitsFromReversedStream(size_t& bitp, const unsigned char* bits, unsigned long nbits) {
    unsigned long result = 0;
    for (size_t i = nbits - 1; i < nbits; i--) result += ((readBitFromReversedStream(bitp, bits)) << i);
    return result;
  }

  void PNG::setBitOfReversedStream(size_t& bitp, unsigned char* bits, unsigned long bit) {
    bits[bitp >> 3] |= (bit << (7 - (bitp & 0x7)));
    bitp++;
  }

  unsigned long PNG::read32bitInt(const unsigned char* buffer) {
    return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
  }

  int PNG::checkColorValidity(unsigned long colorType, unsigned long bd) {
    if ((colorType == 2 or colorType == 4 or colorType == 6)) {
      if (not (bd == 8 or bd == 16)) return 37;
      else return 0;
    }
    else if (colorType == 0) {
      if (not (bd == 1 or bd == 2 or bd == 4 or bd == 8 or bd == 16)) return 37;
      else return 0;
    }
    else if (colorType == 3) {
      if (not (bd == 1 or bd == 2 or bd == 4 or bd == 8)) return 37;
      else return 0;
    }
    else return 31;
  }

  unsigned long PNG::getBpp(const PNGInfo& info) {
    if (info.colorType == 2) return (3 * info.bitDepth);
    else if (info.colorType >= 4) return (info.colorType - 2) * info.bitDepth;
    else return info.bitDepth;
  }

  int PNG::convert(std::vector<unsigned char>& out, const unsigned char* in, PNGInfo& infoIn, unsigned long w, unsigned long h) {
    size_t numpixels = w * h, bp = 0;
    out.resize(numpixels * 4);
    unsigned char* out_ = out.empty() ? 0 : &out[0];
    if (infoIn.bitDepth == 8 and infoIn.colorType == 0) {
      for (size_t i = 0; i < numpixels; i++) {
        out_[4 * i + 0] = out_[4 * i + 1] = out_[4 * i + 2] = in[i];
        out_[4 * i + 3] = (infoIn.key_defined and in[i] == infoIn.key_r) ? 0 : 255;
      }
    }
    else if (infoIn.bitDepth == 8 and infoIn.colorType == 2) {
      for (size_t i = 0; i < numpixels; i++) {
        for (size_t c = 0; c < 3; c++) out_[4 * i + c] = in[3 * i + c];
        out_[4 * i + 3] = (infoIn.key_defined == 1       and
                           in[3 * i + 0] == infoIn.key_r and
                           in[3 * i + 1] == infoIn.key_g and
                           in[3 * i + 2] == infoIn.key_b) ? 0 : 255;
      }
    }
    else if (infoIn.bitDepth == 8 and infoIn.colorType == 3) {
      for (size_t i = 0; i < numpixels; i++) {
        if (4U * in[i] >= infoIn.palette.size()) return 46;
        for (size_t c = 0; c < 4; c++) out_[4 * i + c] = infoIn.palette[4 * in[i] + c];
      }
    }
    else if (infoIn.bitDepth == 8 and infoIn.colorType == 4) {
      for (size_t i = 0; i < numpixels; i++) {
        out_[4 * i + 0] = out_[4 * i + 1] = out_[4 * i + 2] = in[2 * i + 0];
        out_[4 * i + 3] = in[2 * i + 1];
      }
    }
    else if (infoIn.bitDepth == 8 and infoIn.colorType == 6) {
      for (size_t i = 0; i < numpixels; i++) {
        for (size_t c = 0; c < 4; c++) out_[4 * i + c] = in[4 * i + c];
      }
    }
    else if (infoIn.bitDepth == 16 and infoIn.colorType == 0) {
      for (size_t i = 0; i < numpixels; i++) {
        out_[4 * i + 0] = out_[4 * i + 1] = out_[4 * i + 2] = in[2 * i];
        out_[4 * i + 3] = (infoIn.key_defined and 256U * in[i] + in[i + 1] == infoIn.key_r) ? 0 : 255;
      }
    }
    else if (infoIn.bitDepth == 16 and infoIn.colorType == 2) {
      for (size_t i = 0; i < numpixels; i++) {
        for (size_t c = 0; c < 3; c++) out_[4 * i + c] = in[6 * i + 2 * c];
        out_[4 * i + 3] = (infoIn.key_defined                      and
                           256U*in[6*i+0]+in[6*i+1] == infoIn.key_r and
                           256U*in[6*i+2]+in[6*i+3] == infoIn.key_g and
                           256U*in[6*i+4]+in[6*i+5] == infoIn.key_b) ? 0 : 255;
      }
    }
    else if (infoIn.bitDepth == 16 and infoIn.colorType == 4) {
      for (size_t i = 0; i < numpixels; i++) {
        out_[4 * i + 0] = out_[4 * i + 1] = out_[4 * i + 2] = in[4 * i];
        out_[4 * i + 3] = in[4 * i + 2];
      }
    }
    else if (infoIn.bitDepth == 16 and infoIn.colorType == 6) {
      for (size_t i = 0; i < numpixels; i++) {
        for (size_t c = 0; c < 4; c++) out_[4 * i + c] = in[8 * i + 2 * c];
      }
    }
    else if (infoIn.bitDepth < 8 and infoIn.colorType == 0) {
      for (size_t i = 0; i < numpixels; i++) {
        unsigned long value = (readBitsFromReversedStream(bp, in, infoIn.bitDepth) * 255) / ((1 << infoIn.bitDepth) - 1);
        out_[4 * i + 0] = out_[4 * i + 1] = out_[4 * i + 2] = (unsigned char)(value);
        out_[4 * i + 3] = (infoIn.key_defined and value and ((1U << infoIn.bitDepth) - 1U) == infoIn.key_r and ((1U << infoIn.bitDepth) - 1U)) ? 0 : 255;
      }
    }
    else if (infoIn.bitDepth < 8 and infoIn.colorType == 3) {
      for (size_t i = 0; i < numpixels; i++) {
        unsigned long value = readBitsFromReversedStream(bp, in, infoIn.bitDepth);
        if (4 * value >= infoIn.palette.size()) return 47;
        for (size_t c = 0; c < 4; c++) out_[4 * i + c] = infoIn.palette[4 * value + c];
      }
    }
    return 0;
  }

  unsigned char PNG::paethPredictor(short a, short b, short c) {
    short p = a + b - c, pa = p > a ? (p - a) : (a - p), pb = p > b ? (p - b) : (b - p), pc = p > c ? (p - c) : (c - p);
    return (unsigned char)((pa <= pb and pa <= pc) ? a : pb <= pc ? b : c);
  }

  bool PNGDecode(std::vector<unsigned char>& out_image,
                 unsigned long& image_width,
                 unsigned long& image_height,
                 const unsigned char* in_png,
                 std::size_t in_size,
                 bool convert_to_rgba32) {
    PNG decoder; decoder.decode(out_image, in_png, in_size, convert_to_rgba32);
    image_width = decoder.info.width; image_height = decoder.info.height;
    return decoder.error ? false : true;
  }
}
