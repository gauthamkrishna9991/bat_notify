#!/bin/sh

# Make it exit in case of any errors
set -e

echo -e "\e[34mDisabling bat_notify\e[0m"
systemctl disable --user bat_notify
echo -e "\e[34mStopping bat_notify\e[0m"
systemctl stop --user bat_notify
echo -e "\e[34mReload user daemon configs\e[0m"
systemctl --user daemon-reload
echo -e "\e[34mRemove Systemd Task\e[0m"
rm $HOME/.config/systemd/user/bat_notify.service
echo -e "\e[34mUninstall bat_notify\e[0m"
rm $HOME/.local/bin/bat_notify