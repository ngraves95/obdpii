#!/bin/bash

# This script contains all the configuration needed for the target RPi.
# It will most likely need to be run with root privileges.

# This adds the user 'pi' to the group 'dialout', which owns the OBD-II device.
adduser pi dialout
