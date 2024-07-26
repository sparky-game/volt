#include "Keyboard.hh"

namespace volt::runtime {
  std::optional<std::unordered_map<core::Key, bool>::iterator> Keyboard::getIter(core::Key k) noexcept {
    auto it { m_keys.find(k) };
    if (it != m_keys.end()) return it;
    return {};
  }

  std::optional<std::unordered_map<core::Key, bool>::const_iterator> Keyboard::getIter(core::Key k) const noexcept {
    auto it { m_keys.find(k) };
    if (it != m_keys.end()) return it;
    return {};
  }

  bool Keyboard::getIterValue(core::Key k) const noexcept {
    if (auto it { getIter(k) }) return (*it)->second;
    return false;
  }

  void Keyboard::setIterValue(core::Key k, bool value) noexcept {
    if (auto it { getIter(k) }) (*it)->second = value;
  }

  Keyboard::Keyboard(void)
    : m_keys{{
        { core::Key::Backspace,   false },
        { core::Key::Enter,       false },
        { core::Key::Tab,         false },
        { core::Key::Pause,       false },
        { core::Key::Capital,     false },
        { core::Key::Escape,      false },
        { core::Key::Modechange,  false },
        { core::Key::Space,       false },
        { core::Key::Pageup,      false },
        { core::Key::Pagedown,    false },
        { core::Key::End,         false },
        { core::Key::Home,        false },
        { core::Key::Left,        false },
        { core::Key::Up,          false },
        { core::Key::Right,       false },
        { core::Key::Down,        false },
        { core::Key::Select,      false },
        { core::Key::Print,       false },
        { core::Key::Execute,     false },
        { core::Key::Insert,      false },
        { core::Key::Delete,      false },
        { core::Key::Help,        false },
        { core::Key::Num0,        false },
        { core::Key::Num1,        false },
        { core::Key::Num2,        false },
        { core::Key::Num3,        false },
        { core::Key::Num4,        false },
        { core::Key::Num5,        false },
        { core::Key::Num6,        false },
        { core::Key::Num7,        false },
        { core::Key::Num8,        false },
        { core::Key::Num9,        false },
        { core::Key::A,           false },
        { core::Key::B,           false },
        { core::Key::C,           false },
        { core::Key::D,           false },
        { core::Key::E,           false },
        { core::Key::F,           false },
        { core::Key::G,           false },
        { core::Key::H,           false },
        { core::Key::I,           false },
        { core::Key::J,           false },
        { core::Key::K,           false },
        { core::Key::L,           false },
        { core::Key::M,           false },
        { core::Key::N,           false },
        { core::Key::O,           false },
        { core::Key::P,           false },
        { core::Key::Q,           false },
        { core::Key::R,           false },
        { core::Key::S,           false },
        { core::Key::T,           false },
        { core::Key::U,           false },
        { core::Key::V,           false },
        { core::Key::W,           false },
        { core::Key::X,           false },
        { core::Key::Y,           false },
        { core::Key::Z,           false },
        { core::Key::LSuper,      false },
        { core::Key::RSuper,      false },
        { core::Key::Numpad0,     false },
        { core::Key::Numpad1,     false },
        { core::Key::Numpad2,     false },
        { core::Key::Numpad3,     false },
        { core::Key::Numpad4,     false },
        { core::Key::Numpad5,     false },
        { core::Key::Numpad6,     false },
        { core::Key::Numpad7,     false },
        { core::Key::Numpad8,     false },
        { core::Key::Numpad9,     false },
        { core::Key::Multiply,    false },
        { core::Key::Add,         false },
        { core::Key::Separator,   false },
        { core::Key::Subtract,    false },
        { core::Key::Decimal,     false },
        { core::Key::Divide,      false },
        { core::Key::F1,          false },
        { core::Key::F2,          false },
        { core::Key::F3,          false },
        { core::Key::F4,          false },
        { core::Key::F5,          false },
        { core::Key::F6,          false },
        { core::Key::F7,          false },
        { core::Key::F8,          false },
        { core::Key::F9,          false },
        { core::Key::F10,         false },
        { core::Key::F11,         false },
        { core::Key::F12,         false },
        { core::Key::F13,         false },
        { core::Key::F14,         false },
        { core::Key::F15,         false },
        { core::Key::F16,         false },
        { core::Key::F17,         false },
        { core::Key::F18,         false },
        { core::Key::F19,         false },
        { core::Key::F20,         false },
        { core::Key::F21,         false },
        { core::Key::F22,         false },
        { core::Key::F23,         false },
        { core::Key::F24,         false },
        { core::Key::Numlock,     false },
        { core::Key::Scroll,      false },
        { core::Key::NumpadEqual, false },
        { core::Key::LShift,      false },
        { core::Key::RShift,      false },
        { core::Key::LControl,    false },
        { core::Key::RControl,    false },
        { core::Key::LAlt,        false },
        { core::Key::RAlt,        false },
        { core::Key::Semicolon,   false },
        { core::Key::Equal,       false },
        { core::Key::Comma,       false },
        { core::Key::Minus,       false },
        { core::Key::Period,      false },
        { core::Key::Slash,       false },
        { core::Key::Grave,       false }
      }}
  {}

  bool Keyboard::IsKeyPressed(core::Key k) const noexcept {
    return getIterValue(k);
  }

  void Keyboard::OnKeyPressed(core::Key k) noexcept {
    setIterValue(k, true);
  }

  void Keyboard::OnKeyReleased(core::Key k) noexcept {
    setIterValue(k, false);
  }
}
