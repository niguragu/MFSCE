cmake_minimum_required(VERSION 3.2)

project(MFSCE CXX)

include_directories(include)

add_executable(main src/main.cpp src/resister.cpp)

target_compile_options(main PUBLIC -O2 -Wall)