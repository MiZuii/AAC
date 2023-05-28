cmake_minimum_required(VERSION 3.16.3)
project(AAC LANGUAGES CXX)

set(LIBRARY_NAME "AAClib")
set(AAC_VERSION 1.0)

# AAC library target
add_library(${LIBRARY_NAME} STATIC)

message(" + Project dir: ${AAC_SOURCE_DIR}")

# find source files
file(GLOB SOURCES *.cpp sources/*.cpp)
# foreach(source IN LISTS ${SOURCES})
#     message(" +  - ${source}")
    
# endforeach()


target_sources(${LIBRARY_NAME} PRIVATE ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC headers/)
target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -pedantic)


set(TEST_FILE test)
set(TEST_DIR "testdir")

add_executable(${TEST_FILE} "${TEST_DIR}/main.cpp")
target_link_libraries(${TEST_FILE} PRIVATE ${LIBRARY_NAME})


set_target_properties(${TEST_FILE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
