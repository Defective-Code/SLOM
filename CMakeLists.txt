# Standard setp lines for CMake
cmake_minimum_required(VERSION 3.22.1)
project(SLOM)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(tests)