cmake_minimum_required(VERSION 3.25)
add_subdirectory(first)
add_subdirectory(fourth)
add_subdirectory(second)
add_subdirectory(third)

include(CTest)
add_test(NAME return_0 COMMAND dz)
