#!/bin/sh
# Make sure to exit with the non-zero code when any command fails
set -e
# Make a file directory for download source code
mkdir -p ~/.bat_notify
# Switch to that repository
cd ~/.bat_notify
# Clone my Repository
git clone https://github.com/gauthamkrishna9991/bat_notify
# get into bat_notify directory
cd ./bat_notify
# Run the install script
./install.sh
