# Add the tests directory

# Store list of sources to build into executable
set(SOURCES main_t.cpp get_data_t.cpp)

# Add the test executable
add_executable(Tests ${SOURCES})

# Define the testing macro for the unit test target
target_compile_definitions(Tests PRIVATE TESTING)

# include_directories(${CMAKE_SOURCE_DIR})

target_include_directories(Tests PRIVATE "${${PROJECT_SOURCE_DIR}}/utilities")

target_link_libraries(Tests PRIVATE Utilities)

# Add the test to CTest
add_test(NAME SLOM_t COMMAND Tests)