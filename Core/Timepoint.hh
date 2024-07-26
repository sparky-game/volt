#pragma once

#include <chrono>

namespace volt::core {
  using Timepoint = std::chrono::high_resolution_clock::time_point;

  Timepoint GetTimepoint(void);

  uint64_t GetTimepointEpoch(void);
}
