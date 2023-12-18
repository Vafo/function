set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if( NOT TARGET function_impl )

    add_library(function_impl INTERFACE)

    target_include_directories(function_impl INTERFACE .)

    # target_link_libraries(function_impl compiler_flags)
    
endif()
