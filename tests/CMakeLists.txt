project(tests)

# Setup google test
add_subdirectory(googletest)

# Gather all test suites
file(GLOB_RECURSE TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)


# Create global test runner
add_executable(${PROJECT_NAME} test_runner.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gmock gtest_main ${AAC_LIBRARY})

# Compile test headers
foreach(TEST_HEADER ${TEST_HEADERS})
    get_filename_component(TEST_HEADER_DIR ${TEST_HEADER} DIRECTORY)
    target_precompile_headers(${PROJECT_NAME} PRIVATE ${TEST_HEADER})
    add_subdirectory(${TEST_HEADER_DIR})
endforeach()

add_custom_target(run_${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
