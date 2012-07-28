#!/usr/bin/python
# -*- coding: utf-8 -*-

start = -10
stop  = 40
step  = 1

c1 = -9;
c2 = 408;
c3 = 7587;
c4 = 60011;

t = start

print "uint16_t zerocomp_table[] = {"
while t <= stop:
    print " ", (c1*t*t*t + c2*t*t + c3*t + c4) / 1000, ", //", t, "celsius"
    t += 1
print "};"
