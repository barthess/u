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

maxp = 104000 # begin of table
minp = 65000  # maximum height
step = 32 # (Pa) must be power of 2

def height(p):
    """
    p - pressure in Pa
    return millimeters above see level (can be negative) """
    p0 = 101325.0 # pressure at see level (Pa)
    h = 44330.0 * (1.0 - pow(p/p0, 1/5.255)) # height in meters
    return int(round(h * 1000))


print "// Automatically generated file. Do not edit it manually.\n"
print "#ifndef BMP085_TABLE_H_"
print "#define BMP085_TABLE_H_"
print "#define BMP085_STEP", step, "// pressure step (Pa)"
print "#define BMP085_MIN_PRES", minp, "// (Pa)"
print "#define BMP085_MAX_PRES", maxp, "// (Pa)"
print "// table of heights in millimeters relative to see level"
print "static const int32_t ptable[]={"


h = 0
i = 0
p = maxp
while p > minp:
    h = height(p) #
    p -= step
    i += 1
    print "   ",h, ", //", p, "(Pa)"
print "};"
print "//", i,"points in table using", i * 4, "bytes of flash"


print """
/**
 * calculation height from pressure using precalculated table and linear interpolation
 * return height in millimeters.
 */
static int32_t press_to_height_tab(uint32_t pval){
  uint32_t i, dp;

  if(pval > BMP085_MAX_PRES)
    return ptable[0];
  if(pval < (BMP085_MIN_PRES - BMP085_STEP))
    return ptable[(sizeof(ptable) / sizeof(ptable[0])) - 1];

  i  = (BMP085_MAX_PRES - pval) / BMP085_STEP;
  dp = (BMP085_MAX_PRES - pval) % BMP085_STEP;

  return(ptable[i] + (((ptable[i+1] - ptable[i]) * dp) / BMP085_STEP));
}"""

print "#endif /* BMP085_TABLE_H_ */"


