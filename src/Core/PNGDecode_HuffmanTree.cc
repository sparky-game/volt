#include "PNGDecode_HuffmanTree.hh"

namespace volt::core {
  int HuffmanTree::makeFromLengths(const std::vector<unsigned long>& bitlen, unsigned long maxbitlen) {
    unsigned long numcodes = (unsigned long)(bitlen.size()), treepos = 0, nodefilled = 0;
    std::vector<unsigned long> tree1d(numcodes), blcount(maxbitlen + 1, 0), nextcode(maxbitlen + 1, 0);
    for (unsigned long bits = 0; bits < numcodes; bits++) blcount[bitlen[bits]]++;
    for (unsigned long bits = 1; bits <= maxbitlen; bits++) nextcode[bits] = (nextcode[bits - 1] + blcount[bits - 1]) << 1;
    for (unsigned long n = 0; n < numcodes; n++) {
      if (bitlen[n] != 0) tree1d[n] = nextcode[bitlen[n]]++;
    }
    tree2d.clear();
    tree2d.resize(numcodes * 2, 32767);
    for (unsigned long n = 0; n < numcodes; n++) {
      for (unsigned long i = 0; i < bitlen[n]; i++) {
        unsigned long bit = (tree1d[n] >> (bitlen[n] - i - 1)) & 1;
        if (treepos > numcodes - 2) return 55;
        if (tree2d[2 * treepos + bit] == 32767) {
          if (i + 1 == bitlen[n]) {
            tree2d[2 * treepos + bit] = n;
            treepos = 0;
          }
          else {
            tree2d[2 * treepos + bit] = ++nodefilled + numcodes;
            treepos = nodefilled;
          }
        }
        else treepos = tree2d[2 * treepos + bit] - numcodes;
      }
    }
    return 0;
  }

  int HuffmanTree::decode(bool& decoded, unsigned long& result, size_t& treepos, unsigned long bit) const {
    unsigned long numcodes = (unsigned long)tree2d.size() / 2;
    if (treepos >= numcodes) return 11;
    result = tree2d[2 * treepos + bit];
    decoded = (result < numcodes);
    treepos = decoded ? 0 : result - numcodes;
    return 0;
  }
}
