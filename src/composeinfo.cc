#include "composeinfo.h"
#include <glib.h>
#include "logging/logging.h"
#include "yaml2json.h"

namespace Docker {

ComposeInfo::ComposeInfo(const std::string& yaml) : json_(yaml) {}

bool ComposeInfo::getServices(std::vector<Json::Value>& services) {
  Json::Value p = json_.root_["services"];

  for (Json::ValueIterator ii = p.begin(); ii != p.end(); ++ii) {
    services.push_back(ii.key());
  }

  return !services.empty();
}

bool ComposeInfo::getImage(const Json::Value& service, std::string& image) {
  image = json_.root_["services"][service.asString()]["image"].asString();
  return !image.empty();
}

bool ComposeInfo::getHash(const Json::Value& service, std::string& hash) {
  hash = json_.root_["services"][service.asString()]["labels"]["io.compose-spec.config-hash"].asString();
  return !hash.empty();
}

}  // namespace Docker
