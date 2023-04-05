cmake_minimum_required(VERSION 3.25)
project(sdl_static_lib)

set(CMAKE_PREFIX_PATH "/usr")
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
add_executable(sdl_static main.cxx)
target_link_libraries(sdl_static PRIVATE ${SDL2_STATIC_LIBRARIES} SDL2_ttf)
set_target_properties(sdl_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                            "${CMAKE_BINARY_DIR}/bin")
