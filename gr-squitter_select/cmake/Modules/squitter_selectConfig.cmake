INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_SQUITTER_SELECT squitter_select)

FIND_PATH(
    SQUITTER_SELECT_INCLUDE_DIRS
    NAMES squitter_select/api.h
    HINTS $ENV{SQUITTER_SELECT_DIR}/include
        ${PC_SQUITTER_SELECT_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    SQUITTER_SELECT_LIBRARIES
    NAMES gnuradio-squitter_select
    HINTS $ENV{SQUITTER_SELECT_DIR}/lib
        ${PC_SQUITTER_SELECT_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SQUITTER_SELECT DEFAULT_MSG SQUITTER_SELECT_LIBRARIES SQUITTER_SELECT_INCLUDE_DIRS)
MARK_AS_ADVANCED(SQUITTER_SELECT_LIBRARIES SQUITTER_SELECT_INCLUDE_DIRS)

