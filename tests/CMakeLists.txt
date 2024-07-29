# add_executable(testing main_t.cpp)

# target_link_libraries(testing PUBLIC SLOM)

# tests/CMakeLists.txt

# Add the test executable
add_executable(tests main_t.cpp)

# Add the test to CTest
add_test(NAME SLOM_t COMMAND tests)