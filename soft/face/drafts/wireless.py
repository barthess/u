#!/usr/bin/python
# -*- coding: cp1251 -*-

"""
Continuously read the serial port and process IO data received from a remote XBee.
"""

import serial
from xbee import ZigBee
from binascii import hexlify

ser = serial.Serial(21, 57600)

xbee = ZigBee(ser, escaped=True)

# MAC, number written on the back of the XBee module
device={
	"GND":'\x00\x13\xA2\x00\x40\x5D\xF9\xEA',
	"PNS":'\x00\x13\xA2\x00\x40\x5D\xF9\xE9'
}



# Continuously read and print packets
while True:
    try:
        response = xbee.wait_read_frame()
        try:
            #print response
            print hexlify(response['rf_data'])
        except:
            continue
        xbee.send("tx", frame_id='\x00', dest_addr_long=device["PNS"], dest_addr='\xFF\xFE', data='\x01\x55\x55\x55\x55')
    except KeyboardInterrupt:
        break

ser.close()

