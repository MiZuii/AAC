cmake_minimum_required(VERSION 3.16.3)
project(AAC LANGUAGES CXX)

set(LIBRARY_NAME "AAClib")
set(AAC_VERSION 1.0)

# for verbose make output
# set(CMAKE_VERBOSE_MAKEFILE TRUE)

# include headers globaly
include_directories(headers/)

# Find Doxygen
find_program(DOXYGEN NAMES doxygen)

# Check if Doxygen is found
if (DOXYGEN)
    message(" + Doxygen found")

    # configure doxygen
    set(DOXYGEN_FILES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
else ()
    message(" + Doxygen not found. Documentation will not be generated.")
endif ()


# ------------------ AAC library target
add_library(${LIBRARY_NAME} STATIC)


message(" + Project dir: ${AAC_SOURCE_DIR}")

# find source files
file(GLOB SOURCES *.cpp sources/*.cpp sources/*.tpp)
file(GLOB HEADERS *.h headers/*.h)
file(GLOB STBI_DIR headers/stb_image.h)
set(HEADERS_FILTERED ${HEADERS})
list(REMOVE_ITEM HEADERS_FILTERED ${STBI_DIR})

# prep them for doxygen
string(REPLACE ";" " " DOXYGEN_DIRS_STR "${SOURCES} ${HEADERS_FILTERED}")  
set(DOXYGEN_INPUT ${DOXYGEN_DIRS_STR})

message(" + Project headers and source files:")

foreach(source IN LISTS SOURCES)
    message(" +  - ${source}")
    
endforeach()

foreach(header IN LISTS HEADERS_FILTERED)
    message(" +  - ${header}")
    
endforeach()

target_sources(${LIBRARY_NAME} PRIVATE ${SOURCES})
target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -pedantic)

# -------------- test target
set(TEST_FILE test)
set(TEST_DIR "testdir")

add_executable(${TEST_FILE} "${TEST_DIR}/main.cpp")
target_link_libraries(${TEST_FILE} PRIVATE ${LIBRARY_NAME})

set_target_properties(${TEST_FILE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")


if (DOXYGEN)
    # Configure doxfile
    configure_file(${DOXYGEN_FILES_DIRECTORY}/Doxyfile.in ${DOXYGEN_FILES_DIRECTORY}/Doxyfile @ONLY)

    # Add target to generate Doxygen documentation
    add_custom_target(doc
        COMMAND ${DOXYGEN} ${DOXYGEN_FILES_DIRECTORY}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen)

    # Add target to make pdf manual
    add_custom_target(man
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/latex)

    message(" + Doxygen targets configured")
    
endif ()
