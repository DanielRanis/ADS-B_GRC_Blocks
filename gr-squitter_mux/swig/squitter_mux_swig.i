/* -*- c++ -*- */

#define SQUITTER_MUX_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "squitter_mux_swig_doc.i"

%{
#include "squitter_mux/squitter_output.h"
%}


%include "squitter_mux/squitter_output.h"
GR_SWIG_BLOCK_MAGIC2(squitter_mux, squitter_output);
