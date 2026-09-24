#include <fstream>
#include <iostream>
#include <string>

#include <command.h>
#include <config.h>
#include <profile_manager.h>

using std::string;
int main(int argc, char *argv[]) {
  if (argc > 1) {
    string command = argv[1];
    if (command == "backend") {
      return 0;
    } else {
      std::cout << argv[0] << " invalid argument: " << argv[1];
      return -1;
    }
  }

  std::ifstream file(Config::CONFIG_FILE);

  if (!file) {
    std::cerr << "CONFIG_FILE no exist" << std::endl;
    return -1;
  }

  int debug_value = ProfileManager::run();
  if (debug_value == 0)
    std::cout << "\nGPUProfileManager completed successfully.";
  return debug_value;
  ;
}
