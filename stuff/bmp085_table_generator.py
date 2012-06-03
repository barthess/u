#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
Generates values for table function
calculating height based on current atmospheric
pressure.

Usage:
    generator.py > output_file.h
"""

from math import *

h = 0
i = 0
p0 = 101325.0 # pressure at see level (Pa)
pressure = 104000 # begin of table
step = 256 # (Pa)

while h < 3200: # this value allows to not overflow int16_t
    h = 44330 * (1 - pow(pressure/p0, 1/5.255)) # height in meters
    h_dm = int(round(h * 10,0)) # height in decimeters
    print h_dm,',','//', pressure
    pressure -= step
    i += 1
print i,"points in table"
