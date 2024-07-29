#pragma once

#include <vector>

namespace volt::core {
  struct Zlib {
    static unsigned long readBitFromStream(size_t& bitp, const unsigned char* bits);
    static unsigned long readBitsFromStream(size_t& bitp, const unsigned char* bits, size_t nbits);
    int decompress(std::vector<unsigned char>& out, const std::vector<unsigned char>& in);
  };
}
