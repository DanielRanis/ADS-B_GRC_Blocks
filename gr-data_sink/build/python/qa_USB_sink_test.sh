#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/python
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/python:$PATH
export LD_LIBRARY_PATH=/home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/build/swig:$PYTHONPATH
/usr/bin/python2 /home/Daniel/Schreibtisch/GRC_modules/gr-data_sink/python/qa_USB_sink.py 
