#pragma once

#include "Scene.hh"
#include "ProjectSpec.hh"

namespace volt::runtime {
  class Project {
    ProjectSpec m_spec;
    std::unordered_map<std::string, Scene> m_scenes;
  public:
    Project(const ProjectSpec &spec);
    Project(const Project &) = delete;
    Project(Project &&) = delete;
    Project &operator=(const Project &) = delete;
    Project &operator=(Project &&) = delete;
    Scene *CreateScene(const std::string &name);
    Scene *FindScene(const std::string &name);
  };
}
