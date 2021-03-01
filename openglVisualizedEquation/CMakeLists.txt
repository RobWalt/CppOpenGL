cmake_minimum_required(VERSION 3.12)

project(openglBoilerplate VERSION 1.0.0 LANGUAGES CXX C)

# Global CMake variables are set here
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Configuration files
configure_file("${PROJECT_SOURCE_DIR}/include/project_variables.h.in" 
	"${PROJECT_BINARY_DIR}/project_variables.h" @ONLY)

# Project/Library names
# external
set(GLFW_LIBRARY glfw_lib)
set(GLAD_LIBRARY glad_lib)
# self made
set(MAIN main)
set(UTILITY_LIB utility)
set(GLHELPER_LIB glhelper)
set(LIBRARY_PHYSICS physics)
set(LIBRARY_COLORS colors)

find_package(OpenGL REQUIRED)

add_subdirectory("${PROJECT_SOURCE_DIR}/external/")

# These are the libraries

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glad_lib
	glfw_lib
)

# utility_lib
add_subdirectory("${PROJECT_SOURCE_DIR}/src/")

# Add executables
add_subdirectory("${PROJECT_SOURCE_DIR}/app/")
