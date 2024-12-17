cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_COMPILER "/usr/bin/g++" CACHE STRING "C++ compiler" FORCE)

project(MFSCE CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(main src/main.cpp src/register.cpp src/pc.cpp src/alu.cpp src/ram.cpp src/decoder.cpp src/cpu.cpp src/binary_loader.cpp)

target_compile_options(main PUBLIC -O2 -Wall)

