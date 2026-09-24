#include <fstream>
#include <map>
#include <string>

#include <config.h>

namespace Config {

bool save(const std::string &backend, const std::string &path) {
  std::ofstream file("/etc/gpu-profile-switcher.conf");

  if (!file)
    return false;

  file << "backend=" << backend << "\n";
  file << "backend_path=" << path << "\n";

  return true;
}

std::map<std::string, std::string> get_config() {

  std::ifstream file(CONFIG_FILE);

  std::map<std::string, std::string> config;

  std::string line;
  while (std::getline(file, line)) {
    auto pos = line.find('=');
    if (pos == std::string::npos)
      continue;

    config[line.substr(0, pos)] = line.substr(pos + 1);
  }

  return config;
}

bool update_config(const std::map<std::string, std::string> &config) {
  std::ofstream file(CONFIG_FILE);

  if (!file)
    return false;

  for (const auto &[key, value] : config)
    file << key << '=' << value << '\n';

  return true;
}

} // namespace Config
