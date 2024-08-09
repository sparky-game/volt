#include "VFS.hh"
#include "../Core/LogSystem.hh"

namespace volt::core {
  VFS::VFS(void) noexcept {
    VOLT_LOG_INFO("volt::core::VFS :: created successfully");
  }

  VFS::~VFS(void) noexcept {
    VOLT_LOG_INFO("volt::core::~VFS :: destroyed successfully");
  }

  void VFS::Mount(const std::filesystem::path &vpath, const std::filesystem::path &path) noexcept {
    auto it { m_mountPoints.find(vpath) };
    if (it != m_mountPoints.end()) return;
    it->second = path;
  }

  void VFS::Unmount(const std::filesystem::path &vpath) noexcept {
    m_mountPoints.erase(vpath);
  }

  std::optional<std::filesystem::path> VFS::Resolve(const std::filesystem::path &vpath) const noexcept {
    auto it { m_mountPoints.find(vpath) };
    if (it == m_mountPoints.end()) return {};
    return it->second;
  }
}
