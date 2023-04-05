cmake_minimum_required(VERSION 3.25)
project(sdl_shared_lib)

set(CMAKE_PREFIX_PATH "/usr")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(sdl_shared main.cxx)
target_link_libraries(sdl_shared ${SDL2_LIBRARIES})
set_target_properties(sdl_shared PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                            "${CMAKE_BINARY_DIR}/bin")
