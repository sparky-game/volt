#include <cassert>
#include <stdexcept>
#include "Slotmap.hh"

namespace volt::core {
  template <typename T, size_t N, typename I>
  constexpr Slotmap<T, N, I>::Slotmap(void) noexcept { clear(); }

  template <typename T, size_t N, typename I>
  constexpr void Slotmap<T, N, I>::clear(void) noexcept { freelist_init(); }

  template <typename T, size_t N, typename I>
  constexpr typename Slotmap<T, N, I>::key_type Slotmap<T, N, I>::push_back(value_type &&value) {
    auto alloc_id { allocate() };
    auto &slot { m_indices[alloc_id] };
    m_data[slot.id] = std::move(value);
    m_erase[slot.id] = alloc_id;
    auto key { slot };
    key.id = alloc_id;
    return key;
  }

  template <typename T, size_t N, typename I>
  constexpr typename Slotmap<T, N, I>::key_type Slotmap<T, N, I>::push_back(const value_type &value) {
    return push_back(value_type{value});
  }

  template <typename T, size_t N, typename I>
  constexpr bool Slotmap<T, N, I>::erase(key_type key) noexcept {
    if (not is_valid_key(key)) return false;
    free(key);
    return true;
  }

  template <typename T, size_t N, typename I>
  constexpr void Slotmap<T, N, I>::freelist_init(void) noexcept {
    for (idx_type i = 0; i < m_indices.size(); ++i) m_indices[i].id = i + 1;
    m_freelist = 0;
  }

  template <typename T, size_t N, typename I>
  constexpr typename Slotmap<T, N, I>::idx_type Slotmap<T, N, I>::allocate(void) {
    if (m_size >= N) throw std::runtime_error { "No space left in Slotmap" };
    assert(m_freelist < N);
    auto slot_id { m_freelist };
    m_freelist = m_indices[slot_id].id;
    auto &slot { m_indices[slot_id] };
    slot.id = m_size;
    slot.gen = m_generation;
    ++m_size;
    ++m_generation;
    return slot_id;
  }

  template <typename T, size_t N, typename I>
  constexpr void Slotmap<T, N, I>::free(key_type key) noexcept {
    assert(is_valid_key(key));
    auto &slot { m_indices[key.id] };
    auto data_id { slot.id };
    slot.id = m_freelist;
    slot.gen = m_generation;
    m_freelist = key.id;
    if (data_id != m_size - 1) {
      m_data[data_id] = m_data[m_size - 1];
      m_erase[data_id] = m_erase[m_size - 1];
      m_indices[m_erase[data_id]].id = data_id;
    }
    --m_size;
    ++m_generation;
  }

  template <typename T, size_t N, typename I>
  constexpr bool Slotmap<T, N, I>::is_valid_key(key_type key) const noexcept {
    if (key.id >= N or m_indices[key.id].gen != key.gen) return false;
    return true;
  }

  [[maybe_unused]] static consteval void tests(void) {
    // ...
  }
}
