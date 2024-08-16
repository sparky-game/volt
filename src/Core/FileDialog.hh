#pragma once

namespace volt::core {
  struct FileDialog {
    static std::string Open(std::vector<std::string> &filter = {});
    static std::string Save(std::vector<std::string> &filter = {});
  };
}
