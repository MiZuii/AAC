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
    set(DOXYGEN_GENERATE_MAN YES)
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
file(GLOB ADDITIONAL_LATEX_FILES doxygen/*.sty)

set(HEADERS_FILTERED ${LIBRARY_HEADERS})
list(REMOVE_ITEM HEADERS_FILTERED ${STBI_LIBRARY})

# doxygen variables prep
string(REPLACE ";" " " DOXYGEN_DIRS_STR "${LIBRARY_SOURCES} ${HEADERS_FILTERED} ${MAIN_README}")
set(DOXYGEN_INPUT ${DOXYGEN_DIRS_STR})
string(REPLACE ";" " " DOXYGEN_STYLES_STR "${DOCUMENTATION_STYLESHEET}")
set(LATEX_EXTRA_STYLESHEET ${DOXYGEN_STYLES_STR})
string(REPLACE ";" " " LATEX_EXT_FILES "${ADDITIONAL_LATEX_FILES}")
set(LATEX_EXTRA_FILES ${LATEX_EXT_FILES})


message(" + Project headers and source files:")
foreach(source IN LISTS LIBRARY_SOURCES)
    message(" +  - ${source}")
endforeach()

foreach(header IN LISTS HEADERS_FILTERED)
    message(" +  - ${header}")
endforeach()

message(" + Additional latex files found:")
foreach(latex_file IN LISTS ADDITIONAL_LATEX_FILES)
    message(" +  - ${latex_file}")
endforeach()

message(" + Example programs found:")
foreach(example_program IN LISTS EXAMPLE_PROGRAMS)
    message(" +  - ${example_program}")
endforeach()

# -------------------------------------------------------------------------- #
#                            LIBRARY TARGET SETUP                            #
# -------------------------------------------------------------------------- #

# include globaly
include_directories(headers/)

add_library(${LIBRARY_NAME} STATIC)

target_sources(${LIBRARY_NAME} PRIVATE ${LIBRARY_SOURCES})
target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -pedantic)

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
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/latex)

    # Add target to generate Doxygen documentation
    add_custom_target(doc
        COMMAND ${DOXYGEN} ${DOXYGEN_FILES_DIRECTORY}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/latex)

    message(" + Doxygen targets configured")
    
endif ()

# -------------------------------------------------------------------------- #
#                         DOCUMENTATION CLEAN COMMAND                        #
# -------------------------------------------------------------------------- #

add_custom_target(clean_doc 
    COMMAND rm -rf doc/html/* doc/latex/*
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )


