#!/bin/bash

cd build; make clean;cd ..

sudo rm -rf build

# Create a directory named "build"
mkdir build

# Change to the "build" directory
cd build

# Run CMake to generate build files
cmake ..

# Use sudo to make and build with 7 parallel jobs
sudo make -j7


