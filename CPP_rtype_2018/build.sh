#!/bin/bash

rm -rf build
mkdir build && cd build && conan install -s compiler.libcxx=libstdc++11 --build=missing ../  && cmake ../ -G "Unix Makefiles" && cmake --build . && mv bin/* ../
