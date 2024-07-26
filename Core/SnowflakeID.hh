#pragma once

#include <cstdint>

namespace volt::core {
  struct SnowflakeID {
    using value_type = uint64_t;
    SnowflakeID(void);
    inline operator uint64_t(void) const noexcept { return m_id; }
  private:
    value_type m_id;
    uint64_t m_timestamp;
    uint64_t m_random;
  };
}
