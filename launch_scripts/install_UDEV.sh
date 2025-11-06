#!/bin/bash
echo "adding udev rules"
sudo cp 99-anubis-udev.rules /etc/udev/rules.d
sudo udevadm trigger # loads the new udev rules
echo "udev rules added and loaded"