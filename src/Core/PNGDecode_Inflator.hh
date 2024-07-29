#pragma once

#include "PNGDecode_HuffmanTree.hh"

namespace volt::core {
  struct Inflator {
    int error;
    HuffmanTree codetree, codetreeD, codelengthcodetree;
    void inflate(std::vector<unsigned char>& out, const std::vector<unsigned char>& in, size_t inpos = 0);
    void generateFixedTrees(HuffmanTree& tree, HuffmanTree& treeD);
    unsigned long huffmanDecodeSymbol(const unsigned char* in, size_t& bp, const HuffmanTree& codetree, size_t inlength);
    void getTreeInflateDynamic(HuffmanTree& tree, HuffmanTree& treeD, const unsigned char* in, size_t& bp, size_t inlength);
    void inflateHuffmanBlock(std::vector<unsigned char>& out, const unsigned char* in, size_t& bp, size_t& pos, size_t inlength, unsigned long btype);
    void inflateNoCompression(std::vector<unsigned char>& out, const unsigned char* in, size_t& bp, size_t& pos, size_t inlength);
  };
}
