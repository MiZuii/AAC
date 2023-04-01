cmake_minimum_required(VERSION 3.16.3)
project(AAC)

set(CMAKE_BUILD_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_BIN_PATH ${CMAKE_BUILD_PATH}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BIN_PATH})
set(LIBRARY_NAME "AAClib")

# test file target
set(TEST_FILE test)

# include directory with enums and structures
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)

# adding AAC library
add_library(${LIBRARY_NAME} STATIC AAC.cpp )
target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra)


add_executable(${TEST_FILE} main.cpp)
target_link_libraries(${TEST_FILE} ${LIBRARY_NAME})


set_target_properties(${TEST_FILE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
# turen off for now because stb image library was giving warnings
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

