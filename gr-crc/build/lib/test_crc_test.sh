#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/Daniel/Schreibtisch/GRC_modules/gr-crc/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib:$PATH
export LD_LIBRARY_PATH=/home/Daniel/Schreibtisch/GRC_modules/gr-crc/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-crc 
