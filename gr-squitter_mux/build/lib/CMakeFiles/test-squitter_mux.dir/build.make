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
CMAKE_SOURCE_DIR = /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/test-squitter_mux.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/test-squitter_mux.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/test-squitter_mux.dir/flags.make

lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o: lib/CMakeFiles/test-squitter_mux.dir/flags.make
lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o: ../lib/test_squitter_mux.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib && /usr/lib64/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o -c /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/lib/test_squitter_mux.cc

lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.i"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/lib/test_squitter_mux.cc > CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.i

lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.s"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/lib/test_squitter_mux.cc -o CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.s

lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o.requires:

.PHONY : lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o.requires

lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o.provides: lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-squitter_mux.dir/build.make lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o.provides

lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o.provides.build: lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o


lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o: lib/CMakeFiles/test-squitter_mux.dir/flags.make
lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o: ../lib/qa_squitter_mux.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib && /usr/lib64/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o -c /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/lib/qa_squitter_mux.cc

lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.i"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/lib/qa_squitter_mux.cc > CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.i

lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.s"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/lib/qa_squitter_mux.cc -o CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.s

lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o.requires:

.PHONY : lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o.requires

lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o.provides: lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-squitter_mux.dir/build.make lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o.provides

lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o.provides.build: lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o


# Object files for target test-squitter_mux
test__squitter_mux_OBJECTS = \
"CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o" \
"CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o"

# External object files for target test-squitter_mux
test__squitter_mux_EXTERNAL_OBJECTS =

lib/test-squitter_mux: lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o
lib/test-squitter_mux: lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o
lib/test-squitter_mux: lib/CMakeFiles/test-squitter_mux.dir/build.make
lib/test-squitter_mux: /lib64/libgnuradio-runtime.so
lib/test-squitter_mux: /lib64/libgnuradio-pmt.so
lib/test-squitter_mux: /usr/lib64/libboost_filesystem.so
lib/test-squitter_mux: /usr/lib64/libboost_system.so
lib/test-squitter_mux: /usr/lib64/libcppunit.so
lib/test-squitter_mux: lib/libgnuradio-squitter_mux.so
lib/test-squitter_mux: /lib64/libgnuradio-runtime.so
lib/test-squitter_mux: /lib64/libgnuradio-pmt.so
lib/test-squitter_mux: /usr/lib64/libboost_filesystem.so
lib/test-squitter_mux: /usr/lib64/libboost_system.so
lib/test-squitter_mux: lib/CMakeFiles/test-squitter_mux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test-squitter_mux"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-squitter_mux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/test-squitter_mux.dir/build: lib/test-squitter_mux

.PHONY : lib/CMakeFiles/test-squitter_mux.dir/build

lib/CMakeFiles/test-squitter_mux.dir/requires: lib/CMakeFiles/test-squitter_mux.dir/test_squitter_mux.cc.o.requires
lib/CMakeFiles/test-squitter_mux.dir/requires: lib/CMakeFiles/test-squitter_mux.dir/qa_squitter_mux.cc.o.requires

.PHONY : lib/CMakeFiles/test-squitter_mux.dir/requires

lib/CMakeFiles/test-squitter_mux.dir/clean:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/test-squitter_mux.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/test-squitter_mux.dir/clean

lib/CMakeFiles/test-squitter_mux.dir/depend:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/lib /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib /home/Daniel/Schreibtisch/GRC_modules/gr-squitter_mux/build/lib/CMakeFiles/test-squitter_mux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/test-squitter_mux.dir/depend

