### Installing envycontrol

Optimus Boot requires envycontrol to be installed globally because it runs as a systemd service during boot.

### Install EnvyControl
Requires pipx to be installed

```bash
git clone https://github.com/bayasdev/envycontrol.git
cd envycontrol
pipx install .
sudo ln -s ~/.local/bin/envycontrol /usr/local/bin/envycontrol
```

### Install OptimusBoot

Run the following commands from the OptimusBoot project directory:
```bash
sudo ./install.sh
sudo systemctl enable optimus-boot.service
sudo systemctl enable optimus-boot-select_profile.service
```
rebooting is recommended

### Unistall OptimusBoot:
```bash
sudo systemctl disable --now optimus-boot.service
sudo systemctl disable --now optimus-boot-select_profile.service
sudo rm "/usr/bin/optimus-boot"
sudo rm "/usr/lib/systemd/system/optimus-boot.service"
sudo rm "/usr/bin/optimus_boot_select_profile"
sudo rm "/usr/lib/systemd/system/optimus-boot-select_profile.service"
sudo systemctl daemon-reload
```
