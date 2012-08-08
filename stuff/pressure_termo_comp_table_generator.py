#!/usr/bin/python
# -*- coding: utf-8 -*-
import math

start = -10
stop  = 40
step  = 0.1

c1 = -9.006 / 1000.0;
c2 = 0.408;
c3 = 7.587;
c4 = 60.011;

t = start

print "uint16_t zerocomp_table[] = {"
while t <= stop:
    print " ", int(round(c1*t*t*t + c2*t*t + c3*t + c4)), ", //", t, "celsius"
    t += step
print "};"
