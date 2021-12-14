#!/bin/sh

set -e
# Make sure GCC or Clang Exists
if ! [[ $(command -v gcc) || $(command -v clang) ]]; then
    echo "Install a C Compiler"
fi
# Make sure Meson Exists
if ! [[ $(command -v meson) ]]; then
    echo "ERROR: Install Meson"
fi
# Make sure libnotify-devel exists
if [[ $(pkg-config --exists libnotify) ]]; then
    echo "ERROR: Install libnotify-dev(el)"
fi
# Install
echo -e "\e[34mSetting up a build directory\e[0m"
meson setup -Dbuildtype=release -Dprefix=$HOME/.local builddir
echo -e "\e[34mCompiling Source Code\e[0m"
meson compile -C builddir
echo -e "\e[34mInstalling bat_notify..\e[0m"
meson install -C builddir
echo -e "\e[34mInstalling Systemd Service File\e[0m"
envsubst < bat_notify.service > $HOME/.config/systemd/user/bat_notify.service
echo -e "\e[34mReloading all daemons\e[0m"
systemctl --user daemon-reload
echo -e "\e[34mEnable start-on-login for service\e[0m"
systemctl enable --user bat_notify.service
echo -e "\e[34mStarting bat_notify\e[0m"
systemctl start --user bat_notify.service
