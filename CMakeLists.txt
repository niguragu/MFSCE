cmake_minimum_required(VERSION 3.16)

project(MFSCE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_executable(main 
    src/main.cpp 
    src/register.cpp 
    src/pc.cpp 
    src/alu.cpp 
    src/ram.cpp 
    src/decoder.cpp 
    src/cpu.cpp 
    src/binary_loader.cpp
)

target_include_directories(main PRIVATE include)

target_compile_options(main PRIVATE 
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O2 -Wall>
)
