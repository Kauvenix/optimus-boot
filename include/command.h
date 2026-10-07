#pragma once
#include <initializer_list>
#include <string>
namespace Command {
int start_process(const char *program, std::initializer_list<const char *> args,
                  std::string &output);
}
