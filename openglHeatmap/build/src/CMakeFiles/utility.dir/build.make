# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sol/cpp_basics/CppOpenGL/openglHeatmap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build

# Include any dependencies generated for this target.
include src/CMakeFiles/utility.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/utility.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/utility.dir/flags.make

src/CMakeFiles/utility.dir/utilities.cpp.o: src/CMakeFiles/utility.dir/flags.make
src/CMakeFiles/utility.dir/utilities.cpp.o: ../src/utilities.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sol/cpp_basics/CppOpenGL/openglHeatmap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/utility.dir/utilities.cpp.o"
	cd /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/utilities.cpp.o -c /home/sol/cpp_basics/CppOpenGL/openglHeatmap/src/utilities.cpp

src/CMakeFiles/utility.dir/utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/utilities.cpp.i"
	cd /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sol/cpp_basics/CppOpenGL/openglHeatmap/src/utilities.cpp > CMakeFiles/utility.dir/utilities.cpp.i

src/CMakeFiles/utility.dir/utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/utilities.cpp.s"
	cd /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sol/cpp_basics/CppOpenGL/openglHeatmap/src/utilities.cpp -o CMakeFiles/utility.dir/utilities.cpp.s

utility: src/CMakeFiles/utility.dir/utilities.cpp.o
utility: src/CMakeFiles/utility.dir/build.make

.PHONY : utility

# Rule to build all files generated by this target.
src/CMakeFiles/utility.dir/build: utility

.PHONY : src/CMakeFiles/utility.dir/build

src/CMakeFiles/utility.dir/clean:
	cd /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build/src && $(CMAKE_COMMAND) -P CMakeFiles/utility.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/utility.dir/clean

src/CMakeFiles/utility.dir/depend:
	cd /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sol/cpp_basics/CppOpenGL/openglHeatmap /home/sol/cpp_basics/CppOpenGL/openglHeatmap/src /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build/src /home/sol/cpp_basics/CppOpenGL/openglHeatmap/build/src/CMakeFiles/utility.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/utility.dir/depend

