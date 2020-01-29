INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_XML_DECODER xml_decoder)

FIND_PATH(
    XML_DECODER_INCLUDE_DIRS
    NAMES xml_decoder/api.h
    HINTS $ENV{XML_DECODER_DIR}/include
        ${PC_XML_DECODER_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    XML_DECODER_LIBRARIES
    NAMES gnuradio-xml_decoder
    HINTS $ENV{XML_DECODER_DIR}/lib
        ${PC_XML_DECODER_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(XML_DECODER DEFAULT_MSG XML_DECODER_LIBRARIES XML_DECODER_INCLUDE_DIRS)
MARK_AS_ADVANCED(XML_DECODER_LIBRARIES XML_DECODER_INCLUDE_DIRS)

