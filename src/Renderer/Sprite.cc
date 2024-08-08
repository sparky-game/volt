#include <cassert>
#include "Sprite.hh"

namespace volt::renderer {
  Sprite::Sprite(const std::filesystem::path &path) {
    if (not std::filesystem::exists(path)) throw std::runtime_error { "`" + std::string(path) + "` does not represent a valid path" };
    m_data = LoadTexture(path.c_str());
    assert(IsTextureReady(m_data));
    m_width = m_data.width;
    m_height = m_data.height;
  }

  Sprite::~Sprite(void) {
    UnloadTexture(m_data);
  }
}
