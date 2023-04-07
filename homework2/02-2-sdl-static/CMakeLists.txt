cmake_minimum_required(VERSION 3.25)
project(sdl_static_lib)

set(CMAKE_PREFIX_PATH "/usr")
add_executable(sdl_static main.cxx)
target_compile_features(sdl_static PUBLIC cxx_std_20)

find_package(SDL3 QUIET)

if(SDL3_FOUND)
    target_link_libraries(sdl_static PRIVATE SDL3::SDL3-static)
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(sdl_static PRIVATE ${SDL2_STATIC_LIBRARIES})
endif()
set_target_properties(sdl_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                            "${CMAKE_BINARY_DIR}/bin")
