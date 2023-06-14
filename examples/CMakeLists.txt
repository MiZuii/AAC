cmake_minimum_required(VERSION 3.16.3)

project(EXAMPLES)

add_executable(example1 example_1.cpp)
target_link_libraries(example1 PRIVATE ${LIBRARY_NAME})
set_target_properties(example1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")