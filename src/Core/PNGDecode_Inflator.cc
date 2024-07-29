#include "PNGDecode_Zlib.hh"
#include "PNGDecode_Inflator.hh"

static constexpr unsigned long LENBASE[]   { 3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258 };
static constexpr unsigned long LENEXTRA[]  { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0 };
static constexpr unsigned long DISTBASE[]  { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577 };
static constexpr unsigned long DISTEXTRA[] { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13 };
static constexpr unsigned long CLCL[]      { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };

namespace volt::core {
  void Inflator::inflate(std::vector<unsigned char>& out, const std::vector<unsigned char>& in, size_t inpos) {
    size_t bp = 0, pos = 0;
    error = 0;
    unsigned long BFINAL = 0;
    while (not BFINAL and not error) {
      if (bp >> 3 >= in.size()) { error = 52; return; }
      BFINAL = Zlib::readBitFromStream(bp, &in[inpos]);
      unsigned long BTYPE = Zlib::readBitFromStream(bp, &in[inpos]);
      BTYPE += 2 * Zlib::readBitFromStream(bp, &in[inpos]);
      if (BTYPE == 3) { error = 20; return; }
      else if (BTYPE == 0) inflateNoCompression(out, &in[inpos], bp, pos, in.size());
      else inflateHuffmanBlock(out, &in[inpos], bp, pos, in.size(), BTYPE);
    }
    if (not error) out.resize(pos);
  }

  void Inflator::generateFixedTrees(HuffmanTree& tree, HuffmanTree& treeD) {
    std::vector<unsigned long> bitlen(288, 8), bitlenD(32, 5);;
    for (size_t i = 144; i <= 255; i++) bitlen[i] = 9;
    for (size_t i = 256; i <= 279; i++) bitlen[i] = 7;
    tree.makeFromLengths(bitlen, 15);
    treeD.makeFromLengths(bitlenD, 15);
  }

  unsigned long Inflator::huffmanDecodeSymbol(const unsigned char* in, size_t& bp, const HuffmanTree& codetree, size_t inlength) {
    bool decoded; unsigned long ct;
    for (size_t treepos = 0;;) {
      if ((bp & 0x07) == 0 and (bp >> 3) > inlength) { error = 10; return 0; }
      error = codetree.decode(decoded, ct, treepos, Zlib::readBitFromStream(bp, in)); if (error) return 0;
      if (decoded) return ct;
    }
  }

  void Inflator::getTreeInflateDynamic(HuffmanTree& tree, HuffmanTree& treeD, const unsigned char* in, size_t& bp, size_t inlength) {
    std::vector<unsigned long> bitlen(288, 0), bitlenD(32, 0);
    if (bp >> 3 >= inlength - 2) { error = 49; return; }
    size_t HLIT =  Zlib::readBitsFromStream(bp, in, 5) + 257;
    size_t HDIST = Zlib::readBitsFromStream(bp, in, 5) + 1;
    size_t HCLEN = Zlib::readBitsFromStream(bp, in, 4) + 4;
    std::vector<unsigned long> codelengthcode(19);
    for (size_t i = 0; i < 19; i++) codelengthcode[CLCL[i]] = (i < HCLEN) ? Zlib::readBitsFromStream(bp, in, 3) : 0;
    error = codelengthcodetree.makeFromLengths(codelengthcode, 7);
    if (error) return;
    size_t i = 0, replength;
    while (i < HLIT + HDIST) {
      unsigned long code = huffmanDecodeSymbol(in, bp, codelengthcodetree, inlength);
      if (error) return;
      if (code <= 15)  { if (i < HLIT) bitlen[i++] = code; else bitlenD[i++ - HLIT] = code; }
      else if (code == 16) {
        if (bp >> 3 >= inlength) { error = 50; return; }
        replength = 3 + Zlib::readBitsFromStream(bp, in, 2);
        unsigned long value;
        if ((i - 1) < HLIT) value = bitlen[i - 1];
        else value = bitlenD[i - HLIT - 1];
        for (size_t n = 0; n < replength; n++) {
          if (i >= HLIT + HDIST) { error = 13; return; }
          if (i < HLIT) bitlen[i++] = value; else bitlenD[i++ - HLIT] = value;
        }
      }
      else if (code == 17) {
        if (bp >> 3 >= inlength) { error = 50; return; }
        replength = 3 + Zlib::readBitsFromStream(bp, in, 3);
        for (size_t n = 0; n < replength; n++) {
          if (i >= HLIT + HDIST) { error = 14; return; }
          if (i < HLIT) bitlen[i++] = 0; else bitlenD[i++ - HLIT] = 0;
        }
      }
      else if (code == 18) {
        if (bp >> 3 >= inlength) { error = 50; return; }
        replength = 11 + Zlib::readBitsFromStream(bp, in, 7);
        for (size_t n = 0; n < replength; n++) {
          if (i >= HLIT + HDIST) { error = 15; return; }
          if (i < HLIT) bitlen[i++] = 0; else bitlenD[i++ - HLIT] = 0;
        }
      }
      else { error = 16; return; }
    }
    if (bitlen[256] == 0) { error = 64; return; }
    error = tree.makeFromLengths(bitlen, 15);
    if (error) return;
    error = treeD.makeFromLengths(bitlenD, 15);
    if (error) return;
  }

  void Inflator::inflateHuffmanBlock(std::vector<unsigned char>& out, const unsigned char* in, size_t& bp, size_t& pos, size_t inlength, unsigned long btype) {
    if (btype == 1) { generateFixedTrees(codetree, codetreeD); }
    else if (btype == 2) { getTreeInflateDynamic(codetree, codetreeD, in, bp, inlength); if (error) return; }
    for (;;) {
      unsigned long code = huffmanDecodeSymbol(in, bp, codetree, inlength); if (error) return;
      if (code == 256) return;
      else if (code <= 255) {
        if (pos >= out.size()) out.resize((pos + 1) * 2);
        out[pos++] = (unsigned char)(code);
      }
      else if (code >= 257 and code <= 285) {
        size_t length = LENBASE[code - 257], numextrabits = LENEXTRA[code - 257];
        if ((bp >> 3) >= inlength) { error = 51; return; }
        length += Zlib::readBitsFromStream(bp, in, numextrabits);
        unsigned long codeD = huffmanDecodeSymbol(in, bp, codetreeD, inlength); if (error) return;
        if (codeD > 29) { error = 18; return; }
        unsigned long dist = DISTBASE[codeD], numextrabitsD = DISTEXTRA[codeD];
        if ((bp >> 3) >= inlength) { error = 51; return; }
        dist += Zlib::readBitsFromStream(bp, in, numextrabitsD);
        size_t start = pos, back = start - dist;
        if (pos + length >= out.size()) out.resize((pos + length) * 2);
        for (size_t i = 0; i < length; i++) { out[pos++] = out[back++]; if (back >= start) back = start - dist; }
      }
    }
  }

  void Inflator::inflateNoCompression(std::vector<unsigned char>& out, const unsigned char* in, size_t& bp, size_t& pos, size_t inlength) {
    while ((bp & 0x7) != 0) bp++;
    size_t p = bp / 8;
    if (p >= inlength - 4) { error = 52; return; }
    unsigned long LEN = in[p] + 256 * in[p + 1], NLEN = in[p + 2] + 256 * in[p + 3]; p += 4;
    if (LEN + NLEN != 65535) { error = 21; return; }
    if (pos + LEN >= out.size()) out.resize(pos + LEN);
    if (p + LEN > inlength) { error = 23; return; }
    for (unsigned long n = 0; n < LEN; n++) out[pos++] = in[p++];
    bp = p * 8;
  }
}
