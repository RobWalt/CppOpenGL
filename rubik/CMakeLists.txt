cmake_minimum_required(VERSION 3.12.0)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

project(SDLRubiksCube)

add_executable(Rubik src/main.cpp)

target_link_libraries(Rubik SDL2main SDL2 GL)
