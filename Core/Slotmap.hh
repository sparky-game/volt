#pragma once

#include <array>
#include <cstdint>

namespace volt::core {
  template <typename T, std::size_t N, typename I = uint64_t>
  struct Slotmap {
    using value_type     = T;
    using idx_type       = I;
    using gen_type       = idx_type;
    using key_type       = struct { idx_type id; gen_type gen; };
    using iterator       = value_type *;
    using const_iterator = const value_type *;
    constexpr Slotmap(void) noexcept;
    inline constexpr std::size_t size(void) const noexcept      { return m_size;                   }
    inline constexpr std::size_t max_size(void) const noexcept  { return N;                        }
    inline constexpr iterator begin(void) noexcept              { return m_data.begin();           }
    inline constexpr const_iterator cbegin(void) const noexcept { return m_data.cbegin();          }
    inline constexpr iterator end(void) noexcept                { return m_data.begin() + m_size;  }
    inline constexpr const_iterator cend(void) const noexcept   { return m_data.cbegin() + m_size; }
    constexpr void clear(void) noexcept;
    constexpr key_type push_back(value_type &&value);
    constexpr key_type push_back(const value_type &value);
    constexpr bool erase(key_type key) noexcept;
  private:
    idx_type m_size;
    idx_type m_freelist;
    gen_type m_generation;
    std::array<key_type, N> m_indices;
    std::array<value_type, N> m_data;
    std::array<idx_type, N> m_erase;
    constexpr void freelist_init(void) noexcept;
    constexpr idx_type allocate(void);
    constexpr void free(key_type key) noexcept;
    constexpr bool is_valid_key(key_type key) const noexcept;
  };
}
