/* -*- c++ -*- */

#define SQUITTER_SELECT_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "squitter_select_swig_doc.i"

%{
#include "squitter_select/squitter_mux.h"
%}


%include "squitter_select/squitter_mux.h"
GR_SWIG_BLOCK_MAGIC2(squitter_select, squitter_mux);
