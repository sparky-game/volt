#include "Timepoint.hh"

extern "C" {
#include <raylib.h>
}

namespace volt::core {
  Timepoint GetTimepoint(void) {
    return std::chrono::high_resolution_clock::now();
  }

  uint64_t GetTimepointEpoch(void) {
    auto t { GetTimepoint() };
    auto dt { t.time_since_epoch() };
    return duration_cast<std::chrono::milliseconds>(dt).count();
  }

  float GetDeltaTime(void) {
    return GetFrameTime();
  }
}
