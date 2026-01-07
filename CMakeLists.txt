cmake_minimum_required(VERSION 3.10)

project(MemoryManagementSimulator)

# Set the C++ standard to 11 or 17 (needed for nullptr and other modern features)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Tell CMake where to look for header files (.hpp)
include_directories(src/allocator)
include_directories(src/CLI)
include_directories(src/cache)
include_directories("src/virtual memory") # Added this based on your project structure

# 2. Collect ALL .cpp source files
# This ensures that your implementation files are actually compiled
file(GLOB SOURCES 
    "src/*.cpp"
    "src/allocator/*.cpp"
    "src/CLI/*.cpp"
    "src/cache/*.cpp"
    "src/virtual memory/*.cpp"
)

# 3. Create the executable using the collected source files
add_executable(memsim ${SOURCES})