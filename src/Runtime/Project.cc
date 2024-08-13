#include "Project.hh"
#include "../Core/LogSystem.hh"

namespace volt::runtime {
  Project::Project(const ProjectSpec &spec)
    : m_spec{spec}
  {}

  Scene *Project::CreateScene(const std::string &name) {
    auto result { m_scenes.emplace(std::piecewise_construct, std::forward_as_tuple(name), std::forward_as_tuple(name)) };
    if (not result.second) VOLT_LOG_WARN("volt::runtime::Project::CreateScene :: already existing `{}` scene, skipping creation", name);
    return &result.first->second;
  }

  Scene *Project::FindScene(const std::string &name) {
    auto it { m_scenes.find(name) };
    if (it == m_scenes.end()) return nullptr;
    return &it->second;
  }
}
