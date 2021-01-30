cmake_minimum_required(VERSION 3.12)

set(PROJECT "CppOpenGL")

project("${PROJECT}_Project" VERSION 1.2.3 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Project/Library Names
set(LIBRARY_NAME            "${PROJECT}_MyLib")
set(LIBRARY_LOG             "${PROJECT}_loguru")
set(LIBRARY_BENCH           "${PROJECT}_celero")
set(LIBRARY_GLFW            "${PROJECT}_glfw")
set(LIBRARY_GLM             "${PROJECT}_glm")
set(LIBRARY_GLAD            "${PROJECT}_glad")
set(LIBRARY_GTEST           "${PROJECT}_gtest")
set(MAIN                    "${PROJECT}_Executable")
set(TEST_MAIN               "${PROJECT}_unit_tests")

set(LIBRARY_VERTEXSHADER    "${PROJECT}_vertexshader")
set(LIBRARY_PHYSICS    "${PROJECT}_physics")

set(MAIN_LIBS ${LIBRARY_NAME} ${LIBRARY_VERTEXSHADER} ${LIBRARY_PHYSICS})
set(TEST_LIBS ${LIBRARY_NAME} ${LIBRARY_GTEST})
# Options
option(ENABLE_WARNINGS  "Allow target_set_warnings to add warnings."    ON)
option(USE_GCOV         "Create a GCov-enabled build."                  OFF)
option(USE_BENCHMARKS   "Create a Benchmark-enabled build"              OFF)

# Configuration Files
configure_file("${PROJECT_SOURCE_DIR}/include/ProjectConfig.h.in"
               "${PROJECT_BINARY_DIR}/ProjectConfig.h" @ONLY)

# Include own cmake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(Documentation)
include(CTest)
include(ConfigSafeGuards)
include(Warnings)
if(USE_GCOV)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        include(CodeCoverage)
    else()
        message("You must use a GNU or Clang Compiler for CodeCoverage!")
    endif()
endif()


# SYSTEM PACKAGES
# ============ OPENGL =============
# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    message("OPENGL was found!")
endif()

# GLFW & GLM & GLAD are added via external
set(OPENGL_LIBS OpenGL::OpenGL ${LIBRARY_GLAD} ${LIBRARY_GLFW} ${LIBRARY_GLM})
set(MAIN_LIBS ${MAIN_LIBS} ${OPENGL_LIBS})
# ============ OPENGL =============

# Add conan packages
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()
#message("CONAN LIBS: ${CONAN_LIBS}")

# Add externals
add_subdirectory(external)

# Add libraries
add_subdirectory(src)

# Add executables
add_subdirectory(app)

# Add tests
add_subdirectory(tests)

# Add benchmarks
add_subdirectory(benchmarks)
