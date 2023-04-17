cmake_minimum_required(VERSION 3.16)
project(03-2-sdl)

add_executable(03-2-sdl engine.cxx engine.hxx game.cxx)
target_compile_features(03-2-sdl PUBLIC cxx_std_20)

find_package(SDL3 REQUIRED)

target_link_libraries(03-2-sdl PRIVATE SDL3::SDL3-shared)
