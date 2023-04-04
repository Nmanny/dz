cmake_minimum_required(VERSION 3.23)

#project(012dz)

add_library(hw_static STATIC HW.cxx)

add_library(hw_shared SHARED HW.cxx)

add_executable(hello_static hello.cxx)
target_link_libraries(hello_static hw_static)
set_target_properties(hello_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                              "${CMAKE_BINARY_DIR}/bin")

add_executable(hello_dynamic hello.cxx)
target_link_libraries(hello_dynamic hw_shared)
set_target_properties(hello_dynamic PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                               "${CMAKE_BINARY_DIR}/bin")

set_target_properties(hw_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
                                           "${CMAKE_BINARY_DIR}/bin/lib")

set_target_properties(hw_shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                           "${CMAKE_BINARY_DIR}/bin/lib")

