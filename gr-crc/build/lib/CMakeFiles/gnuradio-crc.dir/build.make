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
CMAKE_SOURCE_DIR = /home/Daniel/Schreibtisch/GRC_modules/gr-crc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/gnuradio-crc.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/gnuradio-crc.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/gnuradio-crc.dir/flags.make

lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o: lib/CMakeFiles/gnuradio-crc.dir/flags.make
lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o: ../lib/CRC24_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib && /usr/lib64/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o -c /home/Daniel/Schreibtisch/GRC_modules/gr-crc/lib/CRC24_impl.cc

lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.i"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Daniel/Schreibtisch/GRC_modules/gr-crc/lib/CRC24_impl.cc > CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.i

lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.s"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib && /usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Daniel/Schreibtisch/GRC_modules/gr-crc/lib/CRC24_impl.cc -o CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.s

lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o.requires:

.PHONY : lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o.requires

lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o.provides: lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/gnuradio-crc.dir/build.make lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o.provides.build
.PHONY : lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o.provides

lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o.provides.build: lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o


# Object files for target gnuradio-crc
gnuradio__crc_OBJECTS = \
"CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o"

# External object files for target gnuradio-crc
gnuradio__crc_EXTERNAL_OBJECTS =

lib/libgnuradio-crc.so: lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o
lib/libgnuradio-crc.so: lib/CMakeFiles/gnuradio-crc.dir/build.make
lib/libgnuradio-crc.so: /usr/lib64/libboost_filesystem.so
lib/libgnuradio-crc.so: /usr/lib64/libboost_system.so
lib/libgnuradio-crc.so: /lib64/libgnuradio-runtime.so
lib/libgnuradio-crc.so: /lib64/libgnuradio-pmt.so
lib/libgnuradio-crc.so: lib/CMakeFiles/gnuradio-crc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libgnuradio-crc.so"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gnuradio-crc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/gnuradio-crc.dir/build: lib/libgnuradio-crc.so

.PHONY : lib/CMakeFiles/gnuradio-crc.dir/build

lib/CMakeFiles/gnuradio-crc.dir/requires: lib/CMakeFiles/gnuradio-crc.dir/CRC24_impl.cc.o.requires

.PHONY : lib/CMakeFiles/gnuradio-crc.dir/requires

lib/CMakeFiles/gnuradio-crc.dir/clean:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/gnuradio-crc.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/gnuradio-crc.dir/clean

lib/CMakeFiles/gnuradio-crc.dir/depend:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Daniel/Schreibtisch/GRC_modules/gr-crc /home/Daniel/Schreibtisch/GRC_modules/gr-crc/lib /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib/CMakeFiles/gnuradio-crc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/gnuradio-crc.dir/depend

