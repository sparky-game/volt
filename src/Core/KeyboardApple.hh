#pragma once

#ifdef __APPLE__

namespace volt::core {
  using KeyValueType = uint32_t;

  // NOTE: using the Macintosh Toolbox Essentials manual from 1992
  // (https://developer.apple.com/library/archive/documentation/mac/pdf/MacintoshToolboxEssentials.pdf),
  // specifically under the figure C-2 that represents the domestic layout of the Apple Extended Keyboard II
  // (https://boredzo.org/blog/wp-content/uploads/2007/05/IMTx-virtual-keycodes.pdf).
  // In the figure, the virtual key codes are in decimal, here they need to be represented in hexadecimal (0x...).
  enum class Key {
    Backspace = 0x33
    // ...
  };
}

#endif  // __APPLE__
