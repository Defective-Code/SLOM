# Creating libraries of files to be tested

set(SOURCES get_data.cpp)

add_library(Utilities STATIC ${SOURCES})
#target_link_libraries(SLOM PUBLIC Utilities)
target_include_directories(Utilities PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/utilities" "${PROJECT_SOURCE_DIR}/include")