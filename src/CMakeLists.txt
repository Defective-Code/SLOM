# Store list of sources to build into executable
set(GAMES wordle.cpp wordfind.cpp)

# create the library for using the games
add_library(Games STATIC ${GAMES})
#target_link_libraries(Games PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Games PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Games PUBLIC ${CMAKE_SOURCE_DIR}/include) # add the header files to the Games library
target_link_libraries(Games PUBLIC Utilities)

# Add the executable
add_executable(SLOM main.cpp ${GAMES})

target_link_libraries(SLOM PUBLIC Utilities) # add the get data utility





