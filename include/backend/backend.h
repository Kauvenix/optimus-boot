#pragma once

#include <string>
using std::string;
class Backend {
public:
  virtual ~Backend() = default;

  virtual string get_current_profile() = 0;
  virtual int set_profile(string parameter_value) = 0;
};
