# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /opt/clion-2019.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /www/classes/433/work/project/led-cube

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /www/classes/433/work/project/led-cube/cmake-build-debug

# Include any dependencies generated for this target.
include applications/slice/CMakeFiles/slice.dir/depend.make

# Include the progress variables for this target.
include applications/slice/CMakeFiles/slice.dir/progress.make

# Include the compile flags for this target's objects.
include applications/slice/CMakeFiles/slice.dir/flags.make

applications/slice/CMakeFiles/slice.dir/main.cpp.o: applications/slice/CMakeFiles/slice.dir/flags.make
applications/slice/CMakeFiles/slice.dir/main.cpp.o: ../applications/slice/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/www/classes/433/work/project/led-cube/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object applications/slice/CMakeFiles/slice.dir/main.cpp.o"
	cd /www/classes/433/work/project/led-cube/cmake-build-debug/applications/slice && arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/slice.dir/main.cpp.o -c /www/classes/433/work/project/led-cube/applications/slice/main.cpp

applications/slice/CMakeFiles/slice.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slice.dir/main.cpp.i"
	cd /www/classes/433/work/project/led-cube/cmake-build-debug/applications/slice && arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /www/classes/433/work/project/led-cube/applications/slice/main.cpp > CMakeFiles/slice.dir/main.cpp.i

applications/slice/CMakeFiles/slice.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slice.dir/main.cpp.s"
	cd /www/classes/433/work/project/led-cube/cmake-build-debug/applications/slice && arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /www/classes/433/work/project/led-cube/applications/slice/main.cpp -o CMakeFiles/slice.dir/main.cpp.s

# Object files for target slice
slice_OBJECTS = \
"CMakeFiles/slice.dir/main.cpp.o"

# External object files for target slice
slice_EXTERNAL_OBJECTS =

bin/applications/slice/slice: applications/slice/CMakeFiles/slice.dir/main.cpp.o
bin/applications/slice/slice: applications/slice/CMakeFiles/slice.dir/build.make
bin/applications/slice/slice: applications/slice/CMakeFiles/slice.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/www/classes/433/work/project/led-cube/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/applications/slice/slice"
	cd /www/classes/433/work/project/led-cube/cmake-build-debug/applications/slice && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/slice.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
applications/slice/CMakeFiles/slice.dir/build: bin/applications/slice/slice

.PHONY : applications/slice/CMakeFiles/slice.dir/build

applications/slice/CMakeFiles/slice.dir/clean:
	cd /www/classes/433/work/project/led-cube/cmake-build-debug/applications/slice && $(CMAKE_COMMAND) -P CMakeFiles/slice.dir/cmake_clean.cmake
.PHONY : applications/slice/CMakeFiles/slice.dir/clean

applications/slice/CMakeFiles/slice.dir/depend:
	cd /www/classes/433/work/project/led-cube/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /www/classes/433/work/project/led-cube /www/classes/433/work/project/led-cube/applications/slice /www/classes/433/work/project/led-cube/cmake-build-debug /www/classes/433/work/project/led-cube/cmake-build-debug/applications/slice /www/classes/433/work/project/led-cube/cmake-build-debug/applications/slice/CMakeFiles/slice.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : applications/slice/CMakeFiles/slice.dir/depend
