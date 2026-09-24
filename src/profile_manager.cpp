#include <cctype>
#include <fstream>
#include <iostream>
#include <string_view>

#include "command.h"
#include <backend/backend.h>
#include <backend/backend_factory.h>
#include <profile_manager.h>

using std::getline;
using std::ifstream;
using std::string;

string read_cmdline() {
  ifstream archive("/proc/cmdline");
  if (!archive.is_open()) {
    return {};
  }
  string cmdline;
  getline(archive, cmdline);
  return cmdline;
}

string get_grub_parameter(const string &cmdline) {
  constexpr std::string_view key_parameter = "gpu_profile=";

  auto start_index = cmdline.find(key_parameter);
  if (start_index == string::npos) {
    return {};
  }
  start_index += key_parameter.length();

  auto end_index = cmdline.find(" ", start_index);
  if (end_index == string::npos) {
    end_index = cmdline.length();
  }

  const auto length_parameter = end_index - start_index;

  string value = cmdline.substr(start_index, length_parameter);

  for (char &character : value) { // tolower value
    character = std::tolower(static_cast<unsigned char>(character));
  }
  return value;
}

bool is_valid_profile(const string &profile) {
  return profile == "integrated" || profile == "hybrid" || profile == "nvidia";
}

namespace ProfileManager {
// AI assistance was used for debugging and comments.
// The implementation was written and reviewed by the author.
int run() {
  std::cout << "Starting GPUProfileManager...\n"
            << "Reading kernel command line...\n";

  const string cmdline = read_cmdline();
  if (cmdline.empty()) {
    std::cerr << "Failed to read /proc/cmdline.\n";
    return 1;
  }

  std::cout << "Searching for gpu_profile kernel parameter...\n";
  const string parameter_value = get_grub_parameter(cmdline);
  if (parameter_value.empty()) {
    std::cerr << "No gpu_profile parameter found. Nothing to do.\n";
    return 0;
  }
  std::cout << "Requested GPU profile: " << parameter_value
            << "\nValidating requested profile...\n";
  if (!is_valid_profile(parameter_value)) {
    std::cerr << "Invalid GPU profile: " << parameter_value << std::endl;
    return 1;
  }

  auto backend = BackendFactory::create("envycontrol");

  std::cout << "Reading current GPU profile...\n";
  string current_profile = backend->get_current_profile();
  std::cout << "Current GPU profile: " << current_profile << '\n';

  if (current_profile == parameter_value) {
    std::cout << "Requested profile is already active.\n";
    return 0;
  }
  std::cout << "Applying GPU profile: " << parameter_value << '\n';
  if (backend->set_profile(parameter_value) != 0) {
    std::cerr << "Failed to update GPU profile.\n";
    return 1;
  }
  std::cout << "GPU profile updated successfully.\n"
            << "Reboot required to apply changes.\n";
  string cache;
  std::cout << "Requesting system reboot...\n";
  if (Command::start_process("systemctl", {"reboot"}, cache) != 0) {
    std::cerr << "Failed to reboot the system.\n";
    return 1;
  }

  return 0;
}
} // namespace ProfileManager
