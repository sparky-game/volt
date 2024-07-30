#include <fstream>
#include "SpritePTC.hh"
#include "../Core/PNGDecode.hh"

namespace volt::renderer {
  SpritePTC::SpritePTC(const std::filesystem::path &path) {
    if (not std::filesystem::exists(path)) throw std::runtime_error { "`" + std::string(path) + "` does not represent a valid path" };
    std::ifstream ifs { path, std::ios::binary };
    if (not ifs) throw std::runtime_error { "unable to open file (`" + std::string(path) + "`)" };
    ifs.unsetf(std::ios::skipws);
    std::vector<unsigned char> raw { std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{} };
    std::vector<unsigned char> decoded;
    unsigned long width, height;
    if (not core::PNGDecode(decoded, width, height, raw.data(), raw.size())) throw std::runtime_error { "unable to decode PNG (`" + std::string(path) + "`)" };
    m_data.reserve(decoded.size() / 4);
    for (size_t i {0}; i < decoded.size(); i += 4) {
      uint32_t pixel {0};
      pixel |= decoded[i + 3] << 24;  // A (Alpha) -> 32 - 8  => byte num. 1
      pixel |= decoded[i + 0] << 16;  // R (Red)   -> 32 - 16 => byte num. 2
      pixel |= decoded[i + 1] << 8;   // G (Green) -> 32 - 24 => byte num. 3
      pixel |= decoded[i + 2];        // B (Blue)  -> 32 - 0  => byte num. 4
      m_data.push_back(pixel);
    }
    m_width = width;
    m_height = height;
  }
}
