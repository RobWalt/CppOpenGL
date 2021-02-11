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
CMAKE_SOURCE_DIR = /home/sol/cpp_basics/openglColor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sol/cpp_basics/openglColor/build

# Include any dependencies generated for this target.
include app/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include app/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include app/CMakeFiles/main.dir/flags.make

app/CMakeFiles/main.dir/main.cpp.o: app/CMakeFiles/main.dir/flags.make
app/CMakeFiles/main.dir/main.cpp.o: ../app/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sol/cpp_basics/openglColor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object app/CMakeFiles/main.dir/main.cpp.o"
	cd /home/sol/cpp_basics/openglColor/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /home/sol/cpp_basics/openglColor/app/main.cpp

app/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd /home/sol/cpp_basics/openglColor/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sol/cpp_basics/openglColor/app/main.cpp > CMakeFiles/main.dir/main.cpp.i

app/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd /home/sol/cpp_basics/openglColor/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sol/cpp_basics/openglColor/app/main.cpp -o CMakeFiles/main.dir/main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

app/main: app/CMakeFiles/main.dir/main.cpp.o
app/main: app/CMakeFiles/main.dir/build.make
app/main: libglad.a
app/main: src/libshader.a
app/main: src/libcolor.a
app/main: libglad.a
app/main: /usr/lib/libglfw.so.3.3
app/main: app/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sol/cpp_basics/openglColor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	cd /home/sol/cpp_basics/openglColor/build/app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app/CMakeFiles/main.dir/build: app/main

.PHONY : app/CMakeFiles/main.dir/build

app/CMakeFiles/main.dir/clean:
	cd /home/sol/cpp_basics/openglColor/build/app && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/main.dir/clean

app/CMakeFiles/main.dir/depend:
	cd /home/sol/cpp_basics/openglColor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sol/cpp_basics/openglColor /home/sol/cpp_basics/openglColor/app /home/sol/cpp_basics/openglColor/build /home/sol/cpp_basics/openglColor/build/app /home/sol/cpp_basics/openglColor/build/app/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app/CMakeFiles/main.dir/depend

