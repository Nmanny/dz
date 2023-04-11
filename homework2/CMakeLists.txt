cmake_minimum_required(VERSION 3.25)
add_subdirectory(sdl-dynamic)
add_subdirectory(sdl-static)

include(CTest)
add_test(NAME return_0 COMMAND dz)
