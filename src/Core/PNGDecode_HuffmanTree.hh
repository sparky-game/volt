#pragma once

#include <vector>

namespace volt::core {
  struct HuffmanTree {
    std::vector<unsigned long> tree2d;
    int makeFromLengths(const std::vector<unsigned long>& bitlen, unsigned long maxbitlen);
    int decode(bool& decoded, unsigned long& result, size_t& treepos, unsigned long bit) const;
  };
}
