# Add the tests directory

#THESE DECLARATIONS ARE LEGACY, DO NOT USE!!!
# Store list of sources to build into executable
#set(SOURCES main_t.cpp get_data_t.cpp)

# Add the test executable
#add_executable(Tests ${SOURCES})

# Define the testing macro for the unit test target
#target_compile_definitions(Tests PRIVATE TESTING)

# target_link_libraries(Tests Utilities)

# target_include_directories(Tests PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Add the test to CTest
# add_test(NAME SLOM_t COMMAND Tests)

#TO ADD A NEW TEST, USE THE FOLLOWING :

#add_executable(name_of_the_executable "source.cpp")
#target_link_libraries(the_library_you_need_to_use ) #this is optional if you don't require an external library
#add_test(name_of_the_test name_of_the_executable)

#replace the name_of_the_executable, source.cpp, the_library_you_need_to_use, name_of_the_test with whatever is relevant to you

add_definitions(-DTEST_RESOURCES_FILE_PATH="${CMAKE_SOURCE_DIR}/tests/resources/")

add_executable(test_get_data "get_data_t.cpp")
target_link_libraries(test_get_data Utilities) 
add_test(Get_Data_Test test_get_data)

add_executable(test_wordfind "wordfind_t.cpp")
target_link_libraries(test_wordfind PRIVATE Utilities)
target_link_libraries(test_wordfind PRIVATE Games)
add_test(Wordfind_Test test_wordfind)