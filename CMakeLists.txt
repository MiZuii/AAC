cmake_minimum_required(VERSION 3.16.3)
project(AAC LANGUAGES CXX)

set(LIBRARY_NAME "AAClib")
set(AAC_VERSION 1.0)

# include headers
include_directories(headers/)

# AAC library target
add_library(${LIBRARY_NAME} STATIC)


message(" + Project dir: ${AAC_SOURCE_DIR}")

# find source files
file(GLOB SOURCES *.cpp sources/*.cpp)
message(" + Searching for source files:")
foreach(source IN LISTS SOURCES)
    message(" +  - found: ${source}")
    
endforeach()


target_sources(${LIBRARY_NAME} PRIVATE ${SOURCES})
target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -pedantic)


set(TEST_FILE test)
set(TEST_DIR "testdir")

add_executable(${TEST_FILE} "${TEST_DIR}/main.cpp")
target_link_libraries(${TEST_FILE} PRIVATE ${LIBRARY_NAME})


set_target_properties(${TEST_FILE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# export dependencies into .vscode if work is done in vscode
if (DEFINED ENV{VSCODE_CWD})
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                    ${CMAKE_BINARY_DIR}/compile_commands.json
                    ${AAC_SOURCE_DIR}/.vscode/compile_commands.json)
endif()
