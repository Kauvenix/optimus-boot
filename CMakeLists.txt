cmake_minimum_required(VERSION 3.16)

project(optimus-boot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_executable(optimus-boot
  src/main.cpp
  src/profile_manager.cpp
  src/command.cpp
  src/backend/envycontrol.cpp
  src/backend/backend_factory.cpp
  src/config.cpp
)
