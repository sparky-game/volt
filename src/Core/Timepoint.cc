#include "Timepoint.hh"

namespace volt::core {
  Timepoint GetTimepoint(void) {
    return std::chrono::high_resolution_clock::now();
  }

  uint64_t GetTimepointEpoch(void) {
    auto t { GetTimepoint() };
    auto dt { t.time_since_epoch() };
    return duration_cast<std::chrono::milliseconds>(dt).count();
  }
}
