#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/Daniel/Schreibtisch/GRC_modules/gr-xml_decoder/python
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/Daniel/Schreibtisch/GRC_modules/gr-xml_decoder/build/python:$PATH
export LD_LIBRARY_PATH=/home/Daniel/Schreibtisch/GRC_modules/gr-xml_decoder/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/Daniel/Schreibtisch/GRC_modules/gr-xml_decoder/build/swig:$PYTHONPATH
/usr/bin/python2 /home/Daniel/Schreibtisch/GRC_modules/gr-xml_decoder/python/qa_packaging.py 
