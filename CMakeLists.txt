cmake_minimum_required(VERSION 3.16.3)
project(AAC LANGUAGES CXX)
message(" + Project dir: ${AAC_SOURCE_DIR}")

set(LIBRARY_NAME "AAClib")
set(AAC_VERSION 1.0)

# for verbose make output
# set(CMAKE_VERBOSE_MAKEFILE TRUE)

# -------------------------------------------------------------------------- #
#                           DOXYGEN INITIAL CONFIG                           #
# -------------------------------------------------------------------------- #

find_program(DOXYGEN NAMES doxygen)

if (DOXYGEN)
    message(" + Doxygen found")

    set(DOXYGEN_FILES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
else ()
    message(" + Doxygen not found")
endif ()


# -------------------------------------------------------------------------- #
#                             SOURCE FILES SETUP                             #
# -------------------------------------------------------------------------- #
file(GLOB MAIN_README README.md)
file(GLOB LIBRARY_SOURCES *.cpp sources/*.cpp sources/*.tpp)
file(GLOB LIBRARY_HEADERS *.h headers/*.h)
file(GLOB STBI_LIBRARY headers/stb_image.h)
file(GLOB EXAMPLE_PROGRAMS examples/*.cpp)

set(HEADERS_FILTERED ${LIBRARY_HEADERS})
list(REMOVE_ITEM HEADERS_FILTERED ${STBI_LIBRARY})

# doxygen prep
string(REPLACE ";" " " DOXYGEN_DIRS_STR "${LIBRARY_SOURCES} ${HEADERS_FILTERED} ${MAIN_README}")
set(DOXYGEN_INPUT ${DOXYGEN_DIRS_STR})

message(" + Project headers and source files:")
foreach(source IN LISTS LIBRARY_SOURCES)
    message(" +  - ${source}")
endforeach()

foreach(header IN LISTS HEADERS_FILTERED)
    message(" +  - ${header}")
endforeach()

# -------------------------------------------------------------------------- #
#                            LIBRARY TARGET SETUP                            #
# -------------------------------------------------------------------------- #

# include globaly
include_directories(headers/)

add_library(${LIBRARY_NAME} STATIC)

target_sources(${LIBRARY_NAME} PRIVATE ${LIBRARY_SOURCES})
target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -pedantic)


# -------------------------------------------------------------------------- */
#                                 TEST TARGET                                */
# -------------------------------------------------------------------------- */

set(TEST_FILE test)
set(TEST_DIR "testdir")

add_executable(${TEST_FILE} "${TEST_DIR}/main.cpp")
target_link_libraries(${TEST_FILE} PRIVATE ${LIBRARY_NAME})

set_target_properties(${TEST_FILE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")


# -------------------------------------------------------------------------- #
#                               EXAMPLES TARGET                              #
# -------------------------------------------------------------------------- #

add_subdirectory(examples EXCLUDE_FROM_ALL)

# -------------------------------------------------------------------------- #
#                           SETUP DOXYGEN UTILITIES                          #
# -------------------------------------------------------------------------- #

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
