#!/bin/bash

# Copy main to web directory.
cp -f ../backend/main /var/www/

# Make main only executable.
chmod 111 /var/www/main
