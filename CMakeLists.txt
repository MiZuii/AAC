cmake_minimum_required(VERSION 3.16.3)
project(AAC LANGUAGES CXX)
message(" + Project dir: ${AAC_SOURCE_DIR}")

# ensuring googletest
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -pedantic")

set(AAC_LIBRARY "aac")
set(AAC_VERSION 0.1)

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
#                                 SUBMODULES                                 #
# -------------------------------------------------------------------------- #

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    message(" + Git submodules up to date")
endif()

# -------------------------------------------------------------------------- #
#                             SOURCE FILES SETUP                             #
# -------------------------------------------------------------------------- #
file(GLOB MAIN_README README.md)
file(GLOB_RECURSE LIBRARY_SOURCES sources/*.cpp sources/*.tpp )
file(GLOB STBI_LIBRARY headers/stb_image.h)
file(GLOB EXAMPLE_PROGRAMS examples/*.cpp)
file(GLOB ADDITIONAL_LATEX_FILES doxygen/*.sty)
file(GLOB AAC_LIB_HEADER include/aac.h)
file(GLOB INCLUDE_DIR_HEADERS include/*.h)
set(AAC_INCLUDE_DIR include/)


# doxygen variables prep
string(REPLACE ";" " " DOXYGEN_DIRS_STR "${LIBRARY_SOURCES} ${MAIN_README} ${AAC_LIB_HEADER}")
set(DOXYGEN_INPUT ${DOXYGEN_DIRS_STR})
string(REPLACE ";" " " DOXYGEN_STYLES_STR "${DOCUMENTATION_STYLESHEET}")
set(LATEX_EXTRA_STYLESHEET ${DOXYGEN_STYLES_STR})
string(REPLACE ";" " " LATEX_EXT_FILES "${ADDITIONAL_LATEX_FILES}")
set(LATEX_EXTRA_FILES ${LATEX_EXT_FILES})


# -------------------------------------------------------------------------- #
#                            LIBRARY TARGET SETUP                            #
# -------------------------------------------------------------------------- #

# include globaly
include_directories(headers/)
include_directories(${AAC_INCLUDE_DIR})
include(GNUInstallDirs)

add_library(${AAC_LIBRARY} SHARED)
target_sources(${AAC_LIBRARY} PRIVATE ${LIBRARY_SOURCES})

set_target_properties(${AAC_LIBRARY} PROPERTIES 
    VERSION ${AAC_VERSION}
    PUBLIC_HEADER ${AAC_LIB_HEADER}
)

install(TARGETS ${AAC_LIBRARY}
    LIBRARY DESTINATION ${AAC_INCLUDE_DIR}
    PUBLIC_HEADER DESTINATION ${AAC_INCLUDE_DIR}
)

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

# -------------------------------------------------------------------------- #
#                                    TESTS                                   #
# -------------------------------------------------------------------------- #

enable_testing()
include(GoogleTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
