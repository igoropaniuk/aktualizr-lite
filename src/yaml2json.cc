#include "yaml2json.h"
#include <logging/logging.h>
#include "utilities/utils.h"

Yaml2Json::Yaml2Json(const std::string& yaml) {
  std::string cmd("/usr/local/bin/fy-tool --mode json " + yaml);
  std::string data;

  // call the shell with a full path for security reasons
  if (Utils::shell(cmd, &data, true) != EXIT_SUCCESS) {
    throw std::runtime_error(("/usr/local/bin/fy-tool --mode json " + yaml).c_str());
  }

  std::istringstream sin(data);
  sin >> root_;
}
