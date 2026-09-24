#pragma once

#include "backend.h"
#include <string>
using std::string;
class Envycontrol : public Backend {
public:
  virtual string get_current_profile() override;
  virtual int set_profile(string parameter_value) override;
};
