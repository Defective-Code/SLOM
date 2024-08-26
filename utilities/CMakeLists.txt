# Creating libraries of files to be tested

set(SOURCES get_data.cpp)

add_library(Utilities ${SOURCES})
#target_link_libraries(SLOM PUBLIC Utilities)
target_include_directories(Utilities PRIVATE ${CMAKE_SOURCE_DIR}/include)