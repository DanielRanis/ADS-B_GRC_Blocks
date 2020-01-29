#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/Daniel/Schreibtisch/GRC_modules/gr-coding/python
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/python:$PATH
export LD_LIBRARY_PATH=/home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/Daniel/Schreibtisch/GRC_modules/gr-coding/build/swig:$PYTHONPATH
/usr/bin/python2 /home/Daniel/Schreibtisch/GRC_modules/gr-coding/python/qa_PPM_coding.py 
