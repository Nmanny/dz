cmake_minimum_required(VERSION 3.25)
project(sdl_dynamic_lib)

add_executable(sdl_dynamic main.cxx)
target_compile_features(sdl_dynamic PUBLIC cxx_std_20)

find_package(SDL3 QUIET)

if(SDL3_FOUND)
    target_link_libraries(sdl_dynamic PRIVATE SDL3::SDL3-shared)
else()
    find_package(SDL2 REQUIRED)
    if(APPLE)
        include_directories(${SDL2_INCLUDE_DIRS})
        target_link_libraries(sdl_static ${SDL2_LIBRARIES})
    else()
        target_link_libraries(sdl_dynamic PRIVATE SDL2::SDL2 SDL2::SDL2main)
    endif()
endif()

set_target_properties(sdl_dynamic PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                             "${CMAKE_BINARY_DIR}/bin")
