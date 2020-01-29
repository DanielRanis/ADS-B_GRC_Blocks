INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CODING coding)

FIND_PATH(
    CODING_INCLUDE_DIRS
    NAMES coding/api.h
    HINTS $ENV{CODING_DIR}/include
        ${PC_CODING_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CODING_LIBRARIES
    NAMES gnuradio-coding
    HINTS $ENV{CODING_DIR}/lib
        ${PC_CODING_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CODING DEFAULT_MSG CODING_LIBRARIES CODING_INCLUDE_DIRS)
MARK_AS_ADVANCED(CODING_LIBRARIES CODING_INCLUDE_DIRS)

