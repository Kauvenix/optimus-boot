#!/bin/bash
set -e

cmake -B release -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build release

gcc "src/gpu_select_profile/gpu_select_profile.c" \
  -o "release/optimus_boot_select_profile"

sudo install -Dm755 "release/optimus-boot" \
  "/usr/bin/optimus-boot"

sudo install -Dm644 "src/optimus-boot.service" \
  "/usr/lib/systemd/system/optimus-boot.service"

sudo install -Dm755 "release/optimus_boot_select_profile" \
"/usr/bin/optimus_boot_select_profile"
sudo install -Dm644 "src/gpu_select_profile/optimus-boot-select_profile.service" \
"/usr/lib/systemd/system/optimus-boot-select_profile.service"

sudo systemctl daemon-reload
