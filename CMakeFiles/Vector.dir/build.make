# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/lukasz_k/Dokumenty/vector_implementation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lukasz_k/Dokumenty/vector_implementation

# Include any dependencies generated for this target.
include CMakeFiles/Vector.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Vector.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Vector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Vector.dir/flags.make

CMakeFiles/Vector.dir/main.cpp.o: CMakeFiles/Vector.dir/flags.make
CMakeFiles/Vector.dir/main.cpp.o: main.cpp
CMakeFiles/Vector.dir/main.cpp.o: CMakeFiles/Vector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lukasz_k/Dokumenty/vector_implementation/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Vector.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Vector.dir/main.cpp.o -MF CMakeFiles/Vector.dir/main.cpp.o.d -o CMakeFiles/Vector.dir/main.cpp.o -c /home/lukasz_k/Dokumenty/vector_implementation/main.cpp

CMakeFiles/Vector.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vector.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lukasz_k/Dokumenty/vector_implementation/main.cpp > CMakeFiles/Vector.dir/main.cpp.i

CMakeFiles/Vector.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vector.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lukasz_k/Dokumenty/vector_implementation/main.cpp -o CMakeFiles/Vector.dir/main.cpp.s

# Object files for target Vector
Vector_OBJECTS = \
"CMakeFiles/Vector.dir/main.cpp.o"

# External object files for target Vector
Vector_EXTERNAL_OBJECTS =

Vector: CMakeFiles/Vector.dir/main.cpp.o
Vector: CMakeFiles/Vector.dir/build.make
Vector: libVector-lib.a
Vector: CMakeFiles/Vector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lukasz_k/Dokumenty/vector_implementation/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Vector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Vector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Vector.dir/build: Vector
.PHONY : CMakeFiles/Vector.dir/build

CMakeFiles/Vector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Vector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Vector.dir/clean

CMakeFiles/Vector.dir/depend:
	cd /home/lukasz_k/Dokumenty/vector_implementation && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lukasz_k/Dokumenty/vector_implementation /home/lukasz_k/Dokumenty/vector_implementation /home/lukasz_k/Dokumenty/vector_implementation /home/lukasz_k/Dokumenty/vector_implementation /home/lukasz_k/Dokumenty/vector_implementation/CMakeFiles/Vector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Vector.dir/depend

