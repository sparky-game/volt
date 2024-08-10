#include <cassert>
#include "Sprite.hh"
#include "../Core/LogSystem.hh"

namespace volt::renderer {
  Sprite::Sprite(const std::filesystem::path &path) {
    if (not std::filesystem::exists(path)) throw std::runtime_error { "`" + std::string(path) + "` does not represent a valid path" };
    m_data = LoadTexture(path.c_str());
    assert(IsTextureReady(m_data));
    m_width = m_data.width;
    m_height = m_data.height;
  }

  Sprite::Sprite(Sprite &&s) noexcept
    : m_width{s.m_width}, m_height{s.m_height}, m_data{s.m_data}
  {
    // NOTE: leave the rvalue Sprite object in an invalid state (id <= 0), so when it gets destroyed (after it's moved)
    // it doesn't get unloaded from GPU's VRAM (i.e. leave the moved-from object as a hollow object (empty state)).
    m_width = 0;
    m_height = 0;
    s.m_data = {};
  }

  Sprite::~Sprite(void) {
    UnloadTexture(m_data);
  }
}
