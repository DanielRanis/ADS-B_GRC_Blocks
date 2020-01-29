/* -*- c++ -*- */

#define DATA_SINK_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "data_sink_swig_doc.i"

%{
#include "data_sink/USB_sink.h"
%}


%include "data_sink/USB_sink.h"
GR_SWIG_BLOCK_MAGIC2(data_sink, USB_sink);
