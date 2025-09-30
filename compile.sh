#!/bin/bash

echo "Compiling Time Travelling File System..."
echo "========================================="

# Clean up old files
rm -f *.o program

# Compile each source file
echo "Compiling hashmap.cpp..."
g++ -c hashmap.cpp -o hashmap.o
if [ $? -ne 0 ]; then
    echo "ERROR: hashmap.cpp failed to compile"
    exit 1
fi

echo "Compiling maxheap.cpp..."
g++ -c maxheap.cpp -o maxheap.o
if [ $? -ne 0 ]; then
    echo "ERROR: maxheap.cpp failed to compile"
    exit 1
fi

echo "Compiling recheap.cpp..."
g++ -c recheap.cpp -o recheap.o
if [ $? -ne 0 ]; then
    echo "ERROR: recheap.cpp failed to compile"
    exit 1
fi

echo "Compiling tree.cpp..."
g++ -c tree.cpp -o tree.o
if [ $? -ne 0 ]; then
    echo "ERROR: tree.cpp failed to compile"
    exit 1
fi

echo "Compiling filesystem.cpp..."
g++ -c filesystem.cpp -o filesystem.o
if [ $? -ne 0 ]; then
    echo "ERROR: filesystem.cpp failed to compile"
    exit 1
fi

echo "Compiling main.cpp..."
g++ -c main.cpp -o main.o
if [ $? -ne 0 ]; then
    echo "ERROR: main.cpp failed to compile"
    exit 1
fi

# Link all object files
echo "Linking..."
g++ hashmap.o maxheap.o recheap.o tree.o filesystem.o main.o -o program
if [ $? -ne 0 ]; then
    echo "ERROR: Linking failed"
    exit 1
fi

echo "========================================="
echo "Compilation successful! Run with: ./program"
echo "========================================="