# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Daniel/Schreibtisch/GRC_modules/gr-coding

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/test-coding.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/test-coding.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/test-coding.dir/flags.make

lib/CMakeFiles/test-coding.dir/test_coding.cc.o: lib/CMakeFiles/test-coding.dir/flags.make
lib/CMakeFiles/test-coding.dir/test_coding.cc.o: ../lib/test_coding.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/test-coding.dir/test_coding.cc.o"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib && /usr/lib64/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-coding.dir/test_coding.cc.o -c /home/Daniel/Schreibtisch/GRC_modules/gr-coding/lib/test_coding.cc

lib/CMakeFiles/test-coding.dir/test_coding.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-coding.dir/test_coding.cc.i"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Daniel/Schreibtisch/GRC_modules/gr-coding/lib/test_coding.cc > CMakeFiles/test-coding.dir/test_coding.cc.i

lib/CMakeFiles/test-coding.dir/test_coding.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-coding.dir/test_coding.cc.s"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Daniel/Schreibtisch/GRC_modules/gr-coding/lib/test_coding.cc -o CMakeFiles/test-coding.dir/test_coding.cc.s

lib/CMakeFiles/test-coding.dir/test_coding.cc.o.requires:

.PHONY : lib/CMakeFiles/test-coding.dir/test_coding.cc.o.requires

lib/CMakeFiles/test-coding.dir/test_coding.cc.o.provides: lib/CMakeFiles/test-coding.dir/test_coding.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-coding.dir/build.make lib/CMakeFiles/test-coding.dir/test_coding.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-coding.dir/test_coding.cc.o.provides

lib/CMakeFiles/test-coding.dir/test_coding.cc.o.provides.build: lib/CMakeFiles/test-coding.dir/test_coding.cc.o


lib/CMakeFiles/test-coding.dir/qa_coding.cc.o: lib/CMakeFiles/test-coding.dir/flags.make
lib/CMakeFiles/test-coding.dir/qa_coding.cc.o: ../lib/qa_coding.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/test-coding.dir/qa_coding.cc.o"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib && /usr/lib64/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-coding.dir/qa_coding.cc.o -c /home/Daniel/Schreibtisch/GRC_modules/gr-coding/lib/qa_coding.cc

lib/CMakeFiles/test-coding.dir/qa_coding.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-coding.dir/qa_coding.cc.i"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Daniel/Schreibtisch/GRC_modules/gr-coding/lib/qa_coding.cc > CMakeFiles/test-coding.dir/qa_coding.cc.i

lib/CMakeFiles/test-coding.dir/qa_coding.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-coding.dir/qa_coding.cc.s"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Daniel/Schreibtisch/GRC_modules/gr-coding/lib/qa_coding.cc -o CMakeFiles/test-coding.dir/qa_coding.cc.s

lib/CMakeFiles/test-coding.dir/qa_coding.cc.o.requires:

.PHONY : lib/CMakeFiles/test-coding.dir/qa_coding.cc.o.requires

lib/CMakeFiles/test-coding.dir/qa_coding.cc.o.provides: lib/CMakeFiles/test-coding.dir/qa_coding.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-coding.dir/build.make lib/CMakeFiles/test-coding.dir/qa_coding.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-coding.dir/qa_coding.cc.o.provides

lib/CMakeFiles/test-coding.dir/qa_coding.cc.o.provides.build: lib/CMakeFiles/test-coding.dir/qa_coding.cc.o


# Object files for target test-coding
test__coding_OBJECTS = \
"CMakeFiles/test-coding.dir/test_coding.cc.o" \
"CMakeFiles/test-coding.dir/qa_coding.cc.o"

# External object files for target test-coding
test__coding_EXTERNAL_OBJECTS =

lib/test-coding: lib/CMakeFiles/test-coding.dir/test_coding.cc.o
lib/test-coding: lib/CMakeFiles/test-coding.dir/qa_coding.cc.o
lib/test-coding: lib/CMakeFiles/test-coding.dir/build.make
lib/test-coding: /lib64/libgnuradio-runtime.so
lib/test-coding: /lib64/libgnuradio-pmt.so
lib/test-coding: /usr/lib64/libboost_filesystem.so
lib/test-coding: /usr/lib64/libboost_system.so
lib/test-coding: /usr/lib64/libcppunit.so
lib/test-coding: lib/libgnuradio-coding.so
lib/test-coding: /lib64/libgnuradio-runtime.so
lib/test-coding: /lib64/libgnuradio-pmt.so
lib/test-coding: /usr/lib64/libboost_filesystem.so
lib/test-coding: /usr/lib64/libboost_system.so
lib/test-coding: lib/CMakeFiles/test-coding.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test-coding"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-coding.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/test-coding.dir/build: lib/test-coding

.PHONY : lib/CMakeFiles/test-coding.dir/build

lib/CMakeFiles/test-coding.dir/requires: lib/CMakeFiles/test-coding.dir/test_coding.cc.o.requires
lib/CMakeFiles/test-coding.dir/requires: lib/CMakeFiles/test-coding.dir/qa_coding.cc.o.requires

.PHONY : lib/CMakeFiles/test-coding.dir/requires

lib/CMakeFiles/test-coding.dir/clean:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/test-coding.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/test-coding.dir/clean

lib/CMakeFiles/test-coding.dir/depend:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Daniel/Schreibtisch/GRC_modules/gr-coding /home/Daniel/Schreibtisch/GRC_modules/gr-coding/lib /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib /home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib/CMakeFiles/test-coding.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/test-coding.dir/depend

