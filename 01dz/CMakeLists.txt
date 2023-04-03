cmake_minimum_required(VERSION 3.0.0)
project(HW CXX)

add_executable(dz HW.cxx)

include(CTest)
enable_testing()
add_test(NAME test COMMAND dz)
