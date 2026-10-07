
#pragma once
#include <array>
#include <map>
#include <string>
namespace Config {
bool save(const std::string &backend, const std::string &path);

enum BackendIndex {
  ENVYCONTROL = 0,
};
inline const std::array<std::string, 1> backed_names = {"envycontrol"};

inline constexpr const char *CONFIG_FILE =
    "/home/kauvenix/Desktop/optimus-boot.conf"; //"/etc/optimus-boot.conf";

int set_backend(std::string name);
std::map<std::string, std::string> get_config();
bool update_config(const std::map<std::string, std::string> &config);

void default_setup();
} // namespace Config
