# Store list of sources to build into executable
set(SOURCES main.cpp wordle.cpp wordfind.cpp)
set(GAMES wordle.cpp wordfind.cpp)

add_library(Games STATIC ${GAMES})
target_link_libraries(Games PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# Add the executable
add_executable(SLOM main.cpp ${SOURCES})

target_link_libraries(SLOM PUBLIC Utilities)

#target_include_directories(SLOM ${CMAKE_SOURCE_DIR}/include)

