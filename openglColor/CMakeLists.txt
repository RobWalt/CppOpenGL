cmake_minimum_required(VERSION 3.12)

project(openglColor VERSION 1.0.0 LANGUAGES CXX C)

# Global variables
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # saves compile_commands.json for ycm
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Variables used in C++ code
configure_file("${PROJECT_SOURCE_DIR}/include/variables.h.in"
	       "${PROJECT_BINARY_DIR}/variables.h" @ONLY)	

# Names

set(MAIN main)
set(SHADER_LIBRARY shader)
set(COLOR_LIBRARY color)
set(UTILITIES_LIBRARY utilities)

# GLFW

find_package(glfw3 3.3 REQUIRED)

# GLAD

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PRIVATE ${PROJECT_SOURCE_DIR}/external/glad/include/)
target_link_libraries(glad PRIVATE ${CMAKE_DL_LIBS})

# stb_image.h

# Libraries used by this project

set(OPENGL_LIBRARIES glad glfw)
set(OPENGL_INCLUDE ${PROJECT_SOURCE_DIR}/external/glad/include/)

# Add project libraries

add_subdirectory("${PROJECT_SOURCE_DIR}/src/")

# Add executables

add_subdirectory("${PROJECT_SOURCE_DIR}/app/")
