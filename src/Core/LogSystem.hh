#pragma once

#include <spdlog/spdlog.h>

#define VOLT_LOG_FATAL(...) ::volt::core::LogSystem::GetLogger()->critical(__VA_ARGS__)
#define VOLT_LOG_ERROR(...) ::volt::core::LogSystem::GetLogger()->error(__VA_ARGS__)
#define VOLT_LOG_WARN(...)  ::volt::core::LogSystem::GetLogger()->warn(__VA_ARGS__)
#define VOLT_LOG_INFO(...)  ::volt::core::LogSystem::GetLogger()->info(__VA_ARGS__)
#ifndef NDEBUG
#define VOLT_LOG_DEBUG(...) ::volt::core::LogSystem::GetLogger()->debug(__VA_ARGS__)
#else
#define VOLT_LOG_DEBUG(...)
#endif

namespace volt::core {
  class LogSystem {
    static inline std::shared_ptr<spdlog::logger> s_logger;
  public:
    static void Init(void);
    static inline std::shared_ptr<spdlog::logger> &GetLogger(void) noexcept { return s_logger; }
  };
}
