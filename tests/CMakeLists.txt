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

add_definitions(-DTEST_RESOURCES_FILE_PATH="${CMAKE_SOURCE_DIR}/tests/resources/") # define the directory for the test input files for the get data methods

add_executable(test_get_data "get_data_t.cpp")
target_link_libraries(test_get_data Utilities) # add the utilities library as that is what we are testing with this test
add_test(Get_Data_Test test_get_data)

add_executable(test_wordfind "wordfind_t.cpp")
target_link_libraries(test_wordfind Games) 
add_test(Wordfind_Test test_wordfind)

add_executable(test_wordle "wordle_t.cpp")
target_link_libraries(test_wordle Games)
add_test(Wordle_Test test_wordle)

add_executable(test_hangman "hangman_t.cpp")
target_link_libraries(test_hangman Games)
add_test(Hangman_Test test_hangman)

add_executable(test_wordmatchbingo "wordmatchbingo_t.cpp")
target_link_libraries(test_wordmatchbingo Games) #this is optional if you don't require an external library
add_test(Wordmatchbingo_Test test_wordmatchbingo)