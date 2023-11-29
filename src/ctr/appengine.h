#ifndef AKTUALIZR_LITE_CTR_APP_ENGINE_H
#define AKTUALIZR_LITE_CTR_APP_ENGINE_H

#include "docker/restorableappengine.h"

namespace ctr {

class AppEngine : public Docker::RestorableAppEngine {
 public:

   AppEngine(
      boost::filesystem::path store_root, boost::filesystem::path install_root, boost::filesystem::path docker_root,
      Docker::RegistryClient::Ptr registry_client, Docker::DockerClient::Ptr docker_client,
      std::string client = "/sbin/skopeo", std::string docker_host = "unix:///var/run/docker.sock",
      std::string compose_cmd = "/usr/bin/docker-compose", std::string composectl_cmd = "/usr/bin/composectl",
      StorageSpaceFunc storage_space_func = RestorableAppEngine::GetDefStorageSpaceFunc(),
      ClientImageSrcFunc client_image_src_func = [](const Docker::Uri& /* app_uri */,
                                                    const std::string& image_uri) { return "docker://" + image_uri; },
      bool create_containers_if_install = true, bool offline = false):
        Docker::RestorableAppEngine(store_root, install_root, docker_root, registry_client, docker_client, client, docker_host, compose_cmd, storage_space_func, client_image_src_func), composectl_cmd_{composectl_cmd} {}


  Result fetch(const App& app) override;

 private:
  const std::string composectl_cmd_;
};

}  // namespace ctr

#endif  // AKTUALIZR_LITE_CTR_APP_ENGINE_H

