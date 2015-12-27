#!/bin/bash

# This script contains all the configuration needed for the target RPi.
# It will most likely need to be run with root privileges.

# Add user 'www-data' to the group 'dialout', which owns the OBD-II device.
# This allows php to read and write to the device. Unfortunately, the current
# user must log out and log back in after making this change.
adduser www-data dialout
