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

# Utility rule file for crc_swig_swig_doc.

# Include the progress variables for this target.
include swig/CMakeFiles/crc_swig_swig_doc.dir/progress.make

swig/CMakeFiles/crc_swig_swig_doc: swig/crc_swig_doc.i


swig/crc_swig_doc.i: swig/crc_swig_doc_swig_docs/xml/index.xml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating python docstrings for crc_swig_doc"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/docs/doxygen && /usr/bin/python2 -B /home/Daniel/Schreibtisch/GRC_modules/gr-crc/docs/doxygen/swig_doc.py /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/swig/crc_swig_doc_swig_docs/xml /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/swig/crc_swig_doc.i

swig/crc_swig_doc_swig_docs/xml/index.xml: swig/_crc_swig_doc_tag
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating doxygen xml for crc_swig_doc docs"
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/swig && ./_crc_swig_doc_tag
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/swig && /usr/bin/doxygen /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/swig/crc_swig_doc_swig_docs/Doxyfile

crc_swig_swig_doc: swig/CMakeFiles/crc_swig_swig_doc
crc_swig_swig_doc: swig/crc_swig_doc.i
crc_swig_swig_doc: swig/crc_swig_doc_swig_docs/xml/index.xml
crc_swig_swig_doc: swig/CMakeFiles/crc_swig_swig_doc.dir/build.make

.PHONY : crc_swig_swig_doc

# Rule to build all files generated by this target.
swig/CMakeFiles/crc_swig_swig_doc.dir/build: crc_swig_swig_doc

.PHONY : swig/CMakeFiles/crc_swig_swig_doc.dir/build

swig/CMakeFiles/crc_swig_swig_doc.dir/clean:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/swig && $(CMAKE_COMMAND) -P CMakeFiles/crc_swig_swig_doc.dir/cmake_clean.cmake
.PHONY : swig/CMakeFiles/crc_swig_swig_doc.dir/clean

swig/CMakeFiles/crc_swig_swig_doc.dir/depend:
	cd /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Daniel/Schreibtisch/GRC_modules/gr-crc /home/Daniel/Schreibtisch/GRC_modules/gr-crc/swig /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/swig /home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/swig/CMakeFiles/crc_swig_swig_doc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : swig/CMakeFiles/crc_swig_swig_doc.dir/depend

