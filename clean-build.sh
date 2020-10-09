#!/bin/sh

rm -Rf build/

mkdir build && \
conan install --build=missing . -if build/ && \
cmake . -B build/ && \
cmake --build build/
