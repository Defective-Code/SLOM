# Store list of sources to build into executable
set(SOURCES main.cpp)

# add_subdirectory(utilities)

# Add the executable
add_executable(SLOM ${SOURCES})

# Creating libraries of files to be tested
add_library(Input_Handling utilities/input_handler.cpp)
target_link_libraries(SLOM PUBLIC Input_Handling)
target_include_directories(Input_Handling PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/utilities")