#!/bin/sh

# Switch to the bat_notify directory
echo -e "\e[34mEntering bat_notify directory.\e[0m"
cd ~/.bat_notify/bat_notify

# Run the uninstall script
echo -e "\e[34mRunning the uninstall script.\e[0m"
./uninstall.sh

# Remove all files, including this one.
echo -e "\e[34mRemoving bat_notify directory.\e[0m"
rm -rf ~/.bat_notify/

echo "Cleaning up"
rm ~/.local/bin/uninstall_bat_notify

# bat_notify uninstalled successfully
echo -e "\e32mbat_notify uninstalled successfully.\3[0m"