project(tests)

# Setup google test
add_subdirectory(googletest)

# Gather all test suites
file(GLOB_RECURSE TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)


# Create global test runner
add_executable(${PROJECT_NAME} test_runner.cpp)
gtest_discover_tests(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gmock gtest_main ${AAC_LIBRARY})

# Find tested resources
file(GLOB_RECURSE TEST_RESOURCES test_resource_*)

# Compile resources
foreach(TEST_RESOURCE ${TEST_RESOURCES})
    get_filename_component(TEST_RESOURCE_DEF_RAW ${TEST_RESOURCE} NAME_WE)
    string(TOUPPER ${TEST_RESOURCE_DEF_RAW} TEST_RESOURCE_DEF)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D${TEST_RESOURCE_DEF}=${TEST_RESOURCE})
endforeach()

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
