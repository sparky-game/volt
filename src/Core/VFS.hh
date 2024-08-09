#pragma once

#include <optional>
#include <filesystem>
#include <unordered_map>

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
