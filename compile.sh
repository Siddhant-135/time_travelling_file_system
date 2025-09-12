#!/bin/bash

echo "Compiling Time-Travelling File System..."

# Compile the project
g++ -std=c++17 -O2 -Wall -Wextra -o ../executable main.cpp classes.cpp

if [ $? -eq 0 ]; then
    echo "Compilation successful! Executable created: executable"
    echo "Run with: ./executable"
else
    echo "Compilation failed!"
    exit 1
fi