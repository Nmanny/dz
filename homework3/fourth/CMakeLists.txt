cmake_minimum_required(VERSION 3.25)
project(03-4-sdl)

add_executable(engine-03-4 engine.cxx engine.hxx)
target_compile_features(engine-03-4 PUBLIC cxx_std_20)

set_target_properties(engine-03-4 PROPERTIES ENABLE_EXPORTS ON)

find_package(SDL3 REQUIRED)

target_link_libraries(engine-03-4 PRIVATE SDL3::SDL3-shared)

add_library(game-03-4 SHARED game.cxx)

target_compile_features(game-03-4 PUBLIC cxx_std_20)
target_link_libraries(game-03-4 PRIVATE engine-03-4)
