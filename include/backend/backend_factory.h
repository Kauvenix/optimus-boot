#pragma once

#include <memory>
#include <string>

class Backend;

class BackendFactory {
public:
  static std::unique_ptr<Backend> create(const std::string &name);
};
