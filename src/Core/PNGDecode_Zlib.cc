#include "PNGDecode_Zlib.hh"
#include "PNGDecode_Inflator.hh"

namespace volt::core {
  unsigned long Zlib::readBitFromStream(size_t& bitp, const unsigned char* bits) {
    unsigned long result = (bits[bitp >> 3] >> (bitp & 0x7)) & 1;
    bitp++;
    return result;
  }

  unsigned long Zlib::readBitsFromStream(size_t& bitp, const unsigned char* bits, size_t nbits) {
    unsigned long result = 0;
    for (size_t i = 0; i < nbits; i++) result += (readBitFromStream(bitp, bits)) << i;
    return result;
  }

  int Zlib::decompress(std::vector<unsigned char>& out, const std::vector<unsigned char>& in) {
    Inflator inflator;
    if (in.size() < 2) { return 53; }
    if ((in[0] * 256 + in[1]) % 31 != 0) { return 24; }
    unsigned long CM = in[0] & 15, CINFO = (in[0] >> 4) & 15, FDICT = (in[1] >> 5) & 1;
    if (CM != 8 or CINFO > 7) { return 25; }
    if (FDICT != 0) { return 26; }
    inflator.inflate(out, in, 2);
    return inflator.error;
  }
}
