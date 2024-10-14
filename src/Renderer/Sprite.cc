#include <cassert>
#include "Sprite.hh"

namespace volt::renderer {
  static Image default_texture { GenImageChecked(64, 64, 32, 32, WHITE, MAROON) };

  void Sprite::loadDefaultTexture(void) noexcept {
    assert(IsImageReady(default_texture));
    UnloadTexture(m_data);
    m_data = LoadTextureFromImage(default_texture);
    assert(IsTextureReady(m_data));
    m_width = m_data.width;
    m_height = m_data.height;
    m_name = "default";
  }

  Sprite::Sprite(void) {
    loadDefaultTexture();
  }

  Sprite::Sprite(const std::filesystem::path &path) {
    if (not std::filesystem::exists(path) or not std::filesystem::is_regular_file(path)) {
      throw std::runtime_error { "`" + std::string(path) + "` does not represent a valid path" };
    }
    m_data = LoadTexture(path.c_str());
    assert(IsTextureReady(m_data));
    m_width = m_data.width;
    m_height = m_data.height;
    m_name = path;
  }

  Sprite::Sprite(Sprite &&s) noexcept
    : m_width{s.m_width}, m_height{s.m_height}, m_data{s.m_data}, m_name{s.m_name}
  {
    // NOTE: leave the rvalue Sprite object in an invalid state (id <= 0), so when it gets destroyed (after it's moved)
    // it doesn't get unloaded from GPU's VRAM (i.e. leave the moved-from object as a hollow object (empty state)).
    s.m_width = 0;
    s.m_height = 0;
    s.m_data = {};
    s.m_name.clear();
  }

  Sprite::~Sprite(void) {
    UnloadTexture(m_data);
  }

  void Sprite::Reset(const std::filesystem::path &path) {
    static std::string failed_texture_name;
    if (path == m_name) return;
    if (not std::filesystem::exists(path) or not std::filesystem::is_regular_file(path)) {
      if (m_name != "default") loadDefaultTexture();
      throw std::runtime_error { "`" + std::string(path) + "` does not represent a valid path" };
    }
    if (path == failed_texture_name) return;
    UnloadTexture(m_data);
    m_data = LoadTexture(path.c_str());
    if (not IsTextureReady(m_data)) {
      failed_texture_name = path;
      loadDefaultTexture();
      return;
    }
    m_width = m_data.width;
    m_height = m_data.height;
    m_name = path;
  }
}
