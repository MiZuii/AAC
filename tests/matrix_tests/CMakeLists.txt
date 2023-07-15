project(matrix_tests)

# Find test cases
file(GLOB TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# Create local test runner
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} gtest gmock gtest_main ${AAC_LIBRARY})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${TEST_HEADERS})

# Create run_tests utility
add_custom_target(run_${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)