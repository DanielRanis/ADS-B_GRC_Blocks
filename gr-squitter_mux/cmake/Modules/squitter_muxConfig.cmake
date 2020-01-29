INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_SQUITTER_MUX squitter_mux)

FIND_PATH(
    SQUITTER_MUX_INCLUDE_DIRS
    NAMES squitter_mux/api.h
    HINTS $ENV{SQUITTER_MUX_DIR}/include
        ${PC_SQUITTER_MUX_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    SQUITTER_MUX_LIBRARIES
    NAMES gnuradio-squitter_mux
    HINTS $ENV{SQUITTER_MUX_DIR}/lib
        ${PC_SQUITTER_MUX_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SQUITTER_MUX DEFAULT_MSG SQUITTER_MUX_LIBRARIES SQUITTER_MUX_INCLUDE_DIRS)
MARK_AS_ADVANCED(SQUITTER_MUX_LIBRARIES SQUITTER_MUX_INCLUDE_DIRS)

