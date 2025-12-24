cmake_minimum_required(VERSION 3.10)

project(MemoryManagementSimulator)

# Tell CMake where to find your header files
include_directories(src/allocator)
include_directories(src/CLI)
include_directories(src/cache)

add_executable(memsim 
    src/main.cpp
)