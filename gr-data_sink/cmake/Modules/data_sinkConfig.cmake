INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DATA_SINK data_sink)

FIND_PATH(
    DATA_SINK_INCLUDE_DIRS
    NAMES data_sink/api.h
    HINTS $ENV{DATA_SINK_DIR}/include
        ${PC_DATA_SINK_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DATA_SINK_LIBRARIES
    NAMES gnuradio-data_sink
    HINTS $ENV{DATA_SINK_DIR}/lib
        ${PC_DATA_SINK_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DATA_SINK DEFAULT_MSG DATA_SINK_LIBRARIES DATA_SINK_INCLUDE_DIRS)
MARK_AS_ADVANCED(DATA_SINK_LIBRARIES DATA_SINK_INCLUDE_DIRS)

