/* -*- c++ -*- */

#define CONTROL_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "control_swig_doc.i"

%{
#include "control/modecontrol.h"
%}


%include "control/modecontrol.h"
GR_SWIG_BLOCK_MAGIC2(control, modecontrol);
