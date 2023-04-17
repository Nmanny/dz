cmake_minimum_required(VERSION 3.25)
project(03-1-sdl)

add_executable(03-1-sdl main.cxx)
target_compile_features(03-1-sdl PUBLIC cxx_std_20)

find_package(SDL3 REQUIRED)

target_link_libraries(03-1-sdl PRIVATE SDL3::SDL3-static)
