# Creating libraries of files to be tested

# Define the path to the data file as a preprocessor macro
add_definitions(-DDATA_FILE_PATH="${CMAKE_SOURCE_DIR}/Data/MaoriWordsData.txt")

set(SOURCES get_data.cpp)

add_library(Utilities ${SOURCES})
#target_link_libraries(SLOM PUBLIC Utilities)
target_include_directories(Utilities PRIVATE ${CMAKE_SOURCE_DIR}/include)