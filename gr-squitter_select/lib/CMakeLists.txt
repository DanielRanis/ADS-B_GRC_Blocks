# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND squitter_select_sources
    squitter_mux_impl.cc
)

set(squitter_select_sources "${squitter_select_sources}" PARENT_SCOPE)
if(NOT squitter_select_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT squitter_select_sources)

add_library(gnuradio-squitter_select SHARED ${squitter_select_sources})
target_link_libraries(gnuradio-squitter_select ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-squitter_select PROPERTIES DEFINE_SYMBOL "gnuradio_squitter_select_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-squitter_select PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-squitter_select
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_squitter_select_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_squitter_select.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_squitter_select.cc
)

add_executable(test-squitter_select ${test_squitter_select_sources})

target_link_libraries(
  test-squitter_select
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-squitter_select
)

GR_ADD_TEST(test_squitter_select test-squitter_select)
