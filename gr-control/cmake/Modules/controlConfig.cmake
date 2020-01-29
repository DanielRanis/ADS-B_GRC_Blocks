INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CONTROL control)

FIND_PATH(
    CONTROL_INCLUDE_DIRS
    NAMES control/api.h
    HINTS $ENV{CONTROL_DIR}/include
        ${PC_CONTROL_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CONTROL_LIBRARIES
    NAMES gnuradio-control
    HINTS $ENV{CONTROL_DIR}/lib
        ${PC_CONTROL_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CONTROL DEFAULT_MSG CONTROL_LIBRARIES CONTROL_INCLUDE_DIRS)
MARK_AS_ADVANCED(CONTROL_LIBRARIES CONTROL_INCLUDE_DIRS)

