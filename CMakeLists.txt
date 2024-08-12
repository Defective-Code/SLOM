# Standard setp lines for CMake
cmake_minimum_required(VERSION 3.10)
project(SLOM)
set(CMAKE_CXX_STANDARD 17)

# Add header file folder
include_directories(include)

# Add the source code directory
add_subdirectory(src)

# Add the tests directory
enable_testing()
add_subdirectory(tests)