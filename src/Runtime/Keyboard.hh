#pragma once

#include <optional>
#include <unordered_map>
#include "../Core/KeyboardX11.hh"
#include "../Core/KeyboardWin32.hh"

namespace volt::runtime {
  inline constexpr core::KeyValueType Key2Value(core::Key k) noexcept {
    return static_cast<core::KeyValueType>(k);
  }

  inline constexpr core::Key Value2Key(core::KeyValueType v) noexcept {
    return static_cast<core::Key>(v);
  }

  class Keyboard {
    std::unordered_map<core::Key, bool> m_keys;
    std::optional<std::unordered_map<core::Key, bool>::iterator> getIter(core::Key k) noexcept;
    std::optional<std::unordered_map<core::Key, bool>::const_iterator> getIter(core::Key k) const noexcept;
    bool getIterValue(core::Key k) const noexcept;
    void setIterValue(core::Key k, bool value) noexcept;
  public:
    Keyboard(void);
    Keyboard(const Keyboard &) = delete;
    Keyboard(Keyboard &&) = delete;
    Keyboard &operator=(const Keyboard &) = delete;
    Keyboard &operator=(Keyboard &&) = delete;
    bool IsKeyPressed(core::Key k) const noexcept;
    void OnKeyPressed(core::Key k) noexcept;
    void OnKeyReleased(core::Key k) noexcept;
  };
}
