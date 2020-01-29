/* -*- c++ -*- */

#define XML_DECODER_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "xml_decoder_swig_doc.i"

%{
#include "xml_decoder/packaging.h"
%}


%include "xml_decoder/packaging.h"
GR_SWIG_BLOCK_MAGIC2(xml_decoder, packaging);
