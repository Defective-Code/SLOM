# Store list of sources to build into executable
set(SOURCES main.cpp wordle.cpp wordfind.cpp)
set(GAMES wordle.cpp wordfind.cpp)

# Add the executable
add_executable(SLOM ${SOURCES})
target_include_directories(SLOM PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(Games STATIC ${GAMES})
target_link_libraries(Games PUBLIC ${CMAKE_CURRENT_LIST_DIR})


target_link_libraries(SLOM PUBLIC Utilities)



