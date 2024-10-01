# Standard setp lines for CMake
cmake_minimum_required(VERSION 3.10)
project(SLOM)
set(CMAKE_CXX_STANDARD 17)
include(CTest)

include_directories(include)

# Add the utilities code directory
add_subdirectory(utilities)

# Add the source code directory
add_subdirectory(src)

# Add the tests directory
# enable_testing()
# add_subdirectory(tests)