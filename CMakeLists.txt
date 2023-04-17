cmake_minimum_required(VERSION 3.25)
add_subdirectory(homework1)
add_subdirectory(homework2)
add_subdirectory(homework3)

include(CTest)
add_test(NAME return_0 COMMAND dz)
