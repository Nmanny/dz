cmake_minimum_required(VERSION 3.25)
project(sdl_dynamic_lib)

include(FetchContent)
fetchcontent_declare(SDL3 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git)
fetchcontent_makeavailable(SDL3)

add_executable(sdl_dynamic main.cxx)
target_compile_features(sdl_dynamic PUBLIC cxx_std_20)

# find_package(SDL3 REQUIRED)

target_link_libraries(sdl_dynamic PRIVATE SDL3::SDL3-shared)
set_target_properties(sdl_dynamic PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                             "${CMAKE_BINARY_DIR}/bin")
