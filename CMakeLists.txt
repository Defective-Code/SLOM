# Standard setp lines for CMake
cmake_minimum_required(VERSION 3.10)
project(SLOM)
set(CMAKE_CXX_STANDARD 17)

# Add the source files directory
add_subdirectory(src)

# Add the tests directory
enable_testing()
add_subdirectory(tests)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)