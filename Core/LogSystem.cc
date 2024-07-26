#ifndef VOLT_VERSION
#error The version number must be supplied from the build system.
#endif

#include "LogSystem.hh"
#include <spdlog/sinks/stdout_color_sinks.h>

#define XSTR(s) STR(s)
#define STR(s) #s

#if defined(__clang__)
#define CXX_VERSION __VERSION__
#elif defined(__GNUC__)
#define CXX_VERSION __VERSION__
#elif defined(_MSC_VER)
#define CXX_VERSION _MSC_FULL_VER
#else
#error Unsupported compiler.
#endif

namespace volt::core {
  void LogSystem::Init(void) {
    spdlog::set_pattern("%^[%O.%f] %v%$");
    s_logger = spdlog::stdout_color_mt("volt");
    s_logger->set_level(spdlog::level::debug);
    s_logger->info("GNU Volt version {} ({}) {} {}", XSTR(VOLT_VERSION), CXX_VERSION, __DATE__, __TIME__);
  }
}
