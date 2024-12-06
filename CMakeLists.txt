cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_COMPILER "/usr/bin/g++" CACHE STRING "C++ compiler" FORCE)

project(MFSCE CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(main src/main.cpp src/resister.cpp src/pc.cpp src/alu.cpp)

target_compile_options(main PUBLIC -O2 -Wall)

