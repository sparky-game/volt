#pragma once

#include <optional>
#include <filesystem>
#include <unordered_map>

#if defined(__APPLE__) && defined(__MACH__)
// NOTE: only tested on `macOS 10.15.7 (Catalina) 19H15 x86_64` + `AppleClang 12.0.0`
template <>
struct std::hash<std::filesystem::path> {
  std::size_t operator()(const std::filesystem::path &p) const {
    return std::hash<std::string>()(p.string());
  }
};
#endif

namespace volt::core {
  class VFS {
    std::unordered_map<std::filesystem::path, std::filesystem::path> m_mountPoints;
  public:
    VFS(void) noexcept;
    ~VFS(void) noexcept;
    void Mount(const std::filesystem::path &vpath, const std::filesystem::path &path) noexcept;
    void Unmount(const std::filesystem::path &vpath) noexcept;
    std::optional<std::filesystem::path> Resolve(const std::filesystem::path &vpath) const noexcept;
  };
}
