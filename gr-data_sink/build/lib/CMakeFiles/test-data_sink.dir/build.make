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
CMAKE_SOURCE_DIR = /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/test-data_sink.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/test-data_sink.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/test-data_sink.dir/flags.make

lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o: lib/CMakeFiles/test-data_sink.dir/flags.make
lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o: ../lib/test_data_sink.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib && /usr/lib64/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-data_sink.dir/test_data_sink.cc.o -c /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/lib/test_data_sink.cc

lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-data_sink.dir/test_data_sink.cc.i"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/lib/test_data_sink.cc > CMakeFiles/test-data_sink.dir/test_data_sink.cc.i

lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-data_sink.dir/test_data_sink.cc.s"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/lib/test_data_sink.cc -o CMakeFiles/test-data_sink.dir/test_data_sink.cc.s

lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o.requires:

.PHONY : lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o.requires

lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o.provides: lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-data_sink.dir/build.make lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o.provides

lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o.provides.build: lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o


lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o: lib/CMakeFiles/test-data_sink.dir/flags.make
lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o: ../lib/qa_data_sink.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib && /usr/lib64/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o -c /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/lib/qa_data_sink.cc

lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-data_sink.dir/qa_data_sink.cc.i"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/lib/qa_data_sink.cc > CMakeFiles/test-data_sink.dir/qa_data_sink.cc.i

lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-data_sink.dir/qa_data_sink.cc.s"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/lib/qa_data_sink.cc -o CMakeFiles/test-data_sink.dir/qa_data_sink.cc.s

lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o.requires:

.PHONY : lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o.requires

lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o.provides: lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-data_sink.dir/build.make lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o.provides

lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o.provides.build: lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o


# Object files for target test-data_sink
test__data_sink_OBJECTS = \
"CMakeFiles/test-data_sink.dir/test_data_sink.cc.o" \
"CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o"

# External object files for target test-data_sink
test__data_sink_EXTERNAL_OBJECTS =

lib/test-data_sink: lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o
lib/test-data_sink: lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o
lib/test-data_sink: lib/CMakeFiles/test-data_sink.dir/build.make
lib/test-data_sink: /lib64/libgnuradio-runtime.so
lib/test-data_sink: /lib64/libgnuradio-pmt.so
lib/test-data_sink: /usr/lib64/libboost_filesystem.so
lib/test-data_sink: /usr/lib64/libboost_system.so
lib/test-data_sink: /usr/lib64/libcppunit.so
lib/test-data_sink: lib/libgnuradio-data_sink.so
lib/test-data_sink: /lib64/libgnuradio-runtime.so
lib/test-data_sink: /lib64/libgnuradio-pmt.so
lib/test-data_sink: /usr/lib64/libboost_filesystem.so
lib/test-data_sink: /usr/lib64/libboost_system.so
lib/test-data_sink: lib/CMakeFiles/test-data_sink.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test-data_sink"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-data_sink.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/test-data_sink.dir/build: lib/test-data_sink

.PHONY : lib/CMakeFiles/test-data_sink.dir/build

lib/CMakeFiles/test-data_sink.dir/requires: lib/CMakeFiles/test-data_sink.dir/test_data_sink.cc.o.requires
lib/CMakeFiles/test-data_sink.dir/requires: lib/CMakeFiles/test-data_sink.dir/qa_data_sink.cc.o.requires

.PHONY : lib/CMakeFiles/test-data_sink.dir/requires

lib/CMakeFiles/test-data_sink.dir/clean:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/test-data_sink.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/test-data_sink.dir/clean

lib/CMakeFiles/test-data_sink.dir/depend:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/lib /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib/CMakeFiles/test-data_sink.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/test-data_sink.dir/depend

