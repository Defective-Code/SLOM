# Add the tests directory

# Store list of sources to build into executable
set(SOURCES main_t.cpp test_utils.cpp input_handler_t.cpp)

# Add the test executable
add_executable(Tests ${SOURCES})

target_include_directories(Tests PRIVATE "${PROJECT_BINARY_DIR}" "${${PROJECT_SOURCE_DIR}}/src/utilities")

target_link_libraries(Tests Input_Handling)

# Add the test to CTest
add_test(NAME SLOM_t COMMAND Tests)