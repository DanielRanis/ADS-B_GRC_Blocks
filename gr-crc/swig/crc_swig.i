/* -*- c++ -*- */

#define CRC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "crc_swig_doc.i"

%{
#include "crc/CRC24.h"
%}


%include "crc/CRC24.h"
GR_SWIG_BLOCK_MAGIC2(crc, CRC24);
