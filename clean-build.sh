#!/bin/sh

#export CC=/usr/local/bin/clang10
#export CXX=/usr/local/bin/clang++10

rm -Rf build/

mkdir build && \
conan install . -if build/ && \
#conan install --build=missing . -if build/ && \
cmake . -B build/ && \
#cmake . -DCMAKE_CXX_FLAGS="-pthread" -DCMAKE_CXX_COMPILER=/usr/local/bin/clang++10 -B build/
cmake --build build/
