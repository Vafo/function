set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(function_test function_test.cpp)

target_include_directories(function_test PUBLIC .)

target_link_libraries(function_test function_impl compiler_flags)
# Catch2
target_link_libraries(function_test Catch2::Catch2WithMain)

# Output to build dir
set_target_properties(function_test 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)