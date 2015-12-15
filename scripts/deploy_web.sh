#!/bin/bash

# Remove any old data from deployment location.
rm /var/www/*

# Remove emacs backup files from web directory.
rm ../web/*~ 2>/dev/null

# Copy all files from our local web folder to production location.
cp ../web/* /var/www/
