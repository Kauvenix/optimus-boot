#include "backend/envycontrol.h"
#include <command.h>
#include <config.h>
#include <string>
using std::string;
string get_path_envycontrol() {
  auto file = Config::get_config();
  return file["backend_path"];
}

string Envycontrol::get_current_profile() {
  string result;
  Command::start_process(get_path_envycontrol().c_str(), {"--query"}, result);
  return result;
}
int Envycontrol::set_profile(string parameter_value) {
  string output;
  return Command::start_process(get_path_envycontrol().c_str(),
                                {"-s", parameter_value.c_str()}, output);
}
