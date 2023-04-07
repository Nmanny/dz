cmake_minimum_required(VERSION 3.25)
# add_subdirectory(02-1-sdl-dynamic)
add_subdirectory(02-2-sdl-static)

include(CTest)
add_test(NAME return_0 COMMAND dz)
