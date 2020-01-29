/* -*- c++ -*- */

#define CODING_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "coding_swig_doc.i"

%{
#include "coding/PPM_coding.h"
%}


%include "coding/PPM_coding.h"
GR_SWIG_BLOCK_MAGIC2(coding, PPM_coding);
