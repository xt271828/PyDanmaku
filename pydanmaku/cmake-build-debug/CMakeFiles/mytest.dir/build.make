# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/hanss/.local/clion-2018.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/hanss/.local/clion-2018.2.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hanss/Documents/PycharmProjects/PyDanmaku/cdan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hanss/Documents/PycharmProjects/PyDanmaku/cdan/cmake-build-debug

# Utility rule file for mytest.

# Include the progress variables for this target.
include CMakeFiles/mytest.dir/progress.make

CMakeFiles/mytest:
	make run CLION_EXE_DIR=/home/hanss/Documents/PycharmProjects/PyDanmaku/cdan/cmake-build-debug

mytest: CMakeFiles/mytest
mytest: CMakeFiles/mytest.dir/build.make

.PHONY : mytest

# Rule to build all files generated by this target.
CMakeFiles/mytest.dir/build: mytest

.PHONY : CMakeFiles/mytest.dir/build

CMakeFiles/mytest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mytest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mytest.dir/clean

CMakeFiles/mytest.dir/depend:
	cd /home/hanss/Documents/PycharmProjects/PyDanmaku/cdan/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hanss/Documents/PycharmProjects/PyDanmaku/cdan /home/hanss/Documents/PycharmProjects/PyDanmaku/cdan /home/hanss/Documents/PycharmProjects/PyDanmaku/cdan/cmake-build-debug /home/hanss/Documents/PycharmProjects/PyDanmaku/cdan/cmake-build-debug /home/hanss/Documents/PycharmProjects/PyDanmaku/cdan/cmake-build-debug/CMakeFiles/mytest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mytest.dir/depend

