cmake_minimum_required(VERSION 3.0.0)
project(HW CXX)

add_executable(dz HW.cxx)
set_target_properties(dz PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                    "${CMAKE_BINARY_DIR}/bin")
