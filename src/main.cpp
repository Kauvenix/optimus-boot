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

  if (!std::ifstream(Config::CONFIG_FILE)) {
    Config::default_setup();
    if (!std::ifstream(Config::CONFIG_FILE)) {
      std::cerr << "CONFIG_FILE no exist" << Config::CONFIG_FILE << std::endl;
      return -1;
    }
  }
  int debug_value = ProfileManager::run();
  if (debug_value == 0)
    std::cout << "\nOptimus-Boot completed successfully.";
  return debug_value;
  ;
}
