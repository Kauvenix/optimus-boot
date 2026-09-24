
#include "backend/backend_factory.h"

#include "backend/envycontrol.h"
#include <backend/backend.h>
#include <config.h>
#include <memory>

std::unique_ptr<Backend> BackendFactory::create(const std::string &name) {
  if (name == Config::backed_names[Config::ENVYCONTROL]) {
    return std::make_unique<Envycontrol>();
  }
  return nullptr;
}
