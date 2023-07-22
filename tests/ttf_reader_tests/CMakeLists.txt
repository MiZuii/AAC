project(ttf_reader_tests)

# Find test cases
file(GLOB TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# Find tested resources
file(GLOB TEST_RESOURCES test_resource_*)

# Create local test runner
include_directories(${AAC_HEADERS_DIR} .)
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp ${LIBRARY_SOURCES_C})
target_link_libraries(${PROJECT_NAME} gtest gmock gtest_main ${AAC_LIBRARY})
# target_precompile_headers(${PROJECT_NAME} PRIVATE ${TEST_HEADERS})

# compile resources definitions
foreach(TEST_RESOURCE ${TEST_RESOURCES})
    get_filename_component(TEST_RESOURCE_DEF_RAW ${TEST_RESOURCE} NAME_WE)
    string(TOUPPER ${TEST_RESOURCE_DEF_RAW} TEST_RESOURCE_DEF)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D${TEST_RESOURCE_DEF}=${TEST_RESOURCE})
endforeach()

# Create run_tests utility
add_custom_target(run_${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)