### Installing envycontrol

gpu-profile-switcher requires envycontrol to be installed globally because it runs as a systemd service during boot.

Install envycontrol:

```bash
git clone https://github.com/bayasdev/envycontrol.git
cd envycontrol
pipx install .
sudo ln -s ~/.local/bin/envycontrol /usr/local/bin/envycontrol
```
