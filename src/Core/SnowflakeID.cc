#include <random>
#include "Timepoint.hh"
#include "SnowflakeID.hh"

static constexpr auto snowflake_id_len { 64 };
static constexpr auto timestamp_bits   { 42 };
static constexpr auto rand_num_bits    { snowflake_id_len - timestamp_bits };

static std::random_device rand_dev;
static std::mt19937_64 rand_gen { rand_dev() };
static std::uniform_int_distribution<uint64_t> rand_dist { 0, (1ULL << rand_num_bits) - 1 };

namespace volt::core {
  SnowflakeID::SnowflakeID(void)
    : m_timestamp{GetTimepointEpoch()}, m_random{rand_dist(rand_gen)}
  {
    m_id = (m_timestamp << rand_num_bits) | m_random;
  }

  SnowflakeID::SnowflakeID(value_type id) : m_id{id} {}
}
