cmake_minimum_required(VERSION 3.16.3)

project(EXAMPLES)
add_custom_target(examples)

foreach( example_program IN LISTS EXAMPLE_PROGRAMS )
    get_filename_component(TMP_EXAMPLE ${example_program} NAME_WE)
    # message(" + - Configured example ${TMP_EXAMPLE}")
    add_executable(${TMP_EXAMPLE} ${example_program})
    target_link_libraries(${TMP_EXAMPLE} PRIVATE ${AAC_LIBRARY})
    set_target_properties(${TMP_EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
    add_dependencies(examples ${TMP_EXAMPLE})
endforeach()

message(" + Configured example programs")
