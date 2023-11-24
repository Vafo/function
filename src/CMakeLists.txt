set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(function_impl function.cpp)

target_include_directories(function_impl PUBLIC .)

target_link_libraries(function_impl compiler_flags)