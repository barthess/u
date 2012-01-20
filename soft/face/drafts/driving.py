#! /usr/bin/python
# -*- coding: cp1251 -*-
import serial
from xbee import ZigBee

import time
from binascii import hexlify
import struct

import pygame, sys,os
from pygame.locals import *



#ser = serial.Serial(0, 57600)
ser = serial.Serial(21, 57600)
xbee = ZigBee(ser, escaped=True)

# MAC, number written on the back of the XBee module
device={
	"GND":'\x00\x13\xA2\x00\x40\x5D\xF9\xEA',
	"PNS":'\x00\x13\xA2\x00\x40\x5D\xF9\xE9'
}

# string containing driving parameters
drv_string = '\x01'


pygame.init()

window = pygame.display.set_mode((765, 765))
pygame.display.set_caption('Monkey Fever')
screen = pygame.display.get_surface()

j = pygame.joystick.Joystick(0)
j.init()

pygame.display.flip()





def input(events):
    global drv_string

    for event in events:
        if event.type == QUIT:
            sys.exit(0)
        else:
            ail = (j.get_axis(0) + 1.0) * (float(0xFF) / 2)
            ail = int(round(ail,0))

            ele = (j.get_axis(1) + 1.0) * (float(0xFF) / 2)
            ele = int(round(ele,0))

            thr = (j.get_axis(2) + 1.0) * (float(0xFF) / 2)
            thr = int(round(thr,0))

            rud = (j.get_axis(3) + 1.0) * (float(0xFF) / 2)
            rud = int(round(rud,0))

            print "ail=", ail, "ele=", ele, "thr=", thr, "rud=", rud
            ail = struct.pack('B',ail)
            ele = struct.pack('B',ele)
            thr = struct.pack('B',thr)
            rud = struct.pack('B',rud)

            drv_string = '\x01' + ail + ele + thr + rud




while True:
    try:
        response = xbee.wait_read_frame()
        input(pygame.event.get())
        try:
            #print response
            print hexlify(response['rf_data'])
        except:
            continue
        xbee.send("tx", frame_id='\x00', dest_addr_long=device["PNS"], dest_addr='\xFF\xFE', data=drv_string)
        print hexlify(drv_string)
    except KeyboardInterrupt:
        break

ser.close()
