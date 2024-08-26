# Store list of sources to build into executable
set(SOURCES main.cpp wordle.cpp wordfind.cpp)

# add_subdirectory(utilities)

# Add the executable
add_executable(SLOM ${SOURCES})

target_link_libraries(SLOM PRIVATE Utilities)

target_include_directories(SLOM PRIVATE ${CMAKE_SOURCE_DIR}/include)

