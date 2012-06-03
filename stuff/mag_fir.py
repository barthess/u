#!/usr/bin/python
# -*- coding: utf-8 -*-


import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
import time

import fir
from scipy.signal import lfilter

ser = serial.Serial("/dev/ttyS0", 115200)


STEP = 1 # шаг по оси Х
SCOPE_LEN = 200 # количество точек на экране

fig = plt.figure()
ax = fig.add_subplot(111)
# origin, = ax.plot([], [], ',', lw=1, antialiased=False)
origin, = ax.plot([], [], lw=1)
filtered, = ax.plot([], [], lw=4, color='red')
ax.set_xlim(0, SCOPE_LEN)
ax.set_ylim(-1800, -1950)

taps = fir.get_taps()
print taps

def animate(i):
    origin.set_data(i)
    filtered.set_data(i[0], lfilter(taps, 1.0, i[1]))
    xmin, xmax = ax.get_xlim()
    # ax.set_xlim( (xmin + STEP, xmax + STEP) )
    return origin, filtered

def gen():
    i = 0
    X = []
    mag = []
    while True:
        yield X, mag
        if i >= SCOPE_LEN:
            mag.pop(0)
        else:
            X.append(i)
        mag.append(int(ser.readline()))
        i += STEP

# Init only required for blitting to give a clean slate.
def init():
    origin.set_data(0, 0)
    filtered.set_data(0, 0)
    # xmin, xmax = ax.get_xlim()
    # ax.set_xlim( (xmin + STEP, xmax + STEP) )
    return origin, filtered
    # origin.set_ydata(np.ma.array(L, mask=True))

# ani = animation.FuncAnimation(fig, animate, gen, interval=50, blit=False)
ani = animation.FuncAnimation(fig, animate, gen, interval=5, init_func=init, blit=True)
# ani = animation.FuncAnimation(fig, animate, gen, interval=25, blit=True)
plt.show()




