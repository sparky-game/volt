#pragma once

#include <filesystem>

namespace volt::runtime {
  struct ProjectSpec {
    std::string name;
    std::filesystem::path path;
    // TODO: if we create a scenegraph, then it's not needed
    // std::string start_scene;
  };
}
