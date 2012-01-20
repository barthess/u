#!/usr/bin/python
# -*- coding: cp1251 -*-

import time
import datetime
from struct import *
from multiprocessing import Queue
from multiprocessing import Event
from Queue import Empty, Full # ��� ������ ����������

import serial
from binascii import hexlify
from xbee import ZigBee

from localconfig import *




def linkxbee(q_down, q_up, e_pause, e_kill, config):
    """
    ��������� ����������.
    �������� ����� � xbee, ��� �� ������� � ����� ������
    ����� �� ����� ������������ ���������� ������

    """
    # ������ �������� �� �������
    baudrate = config.getint('Link', 'baudrate')
    port     = config.getint('Link', 'port')

    # 2 ����-���� ����� ���������� ��� ������� ������ � xbee �� 115200
    ser = serial.Serial(port, baudrate, stopbits=2)

    xbee = ZigBee(ser, escaped=True)
    device={"GND":'\x00\x13\xA2\x00\x40\x5D\xF9\xEA',
            "PNS":'\x00\x13\xA2\x00\x40\x5D\xF9\xE9'}

    xbee_response = None # ��������� � ������ �����
    msg_up = None # ������, ������� ���� ��������� � ����� ��� ��������

    # ����, ���� ��� ������ � �����
    print "---- link ready"
    e_pause.wait()
    print "---- link run"

    while True:
        if e_kill.is_set():
            print "=== Link. Kill signal received. Exiting"
            return

        # ������ �� ������
        try:
            xbee_response = xbee.wait_read_frame()
        except:
            print "xbee not respond"

        # ������ �������� �� ���������� ������ � ������� ������������� �����������
        if (xbee_response != None) and (xbee_response['id'] == 'rx'):
            try:
                q_down.put_nowait(xbee_response['rf_data'])
            except Full:
                print "Input packet lost"

        # ��� �� ����� �� ������� ��������� ��� ��������
        try:
            msg_up = q_up.get_nowait()
        except Empty:
            pass
        if msg_up != None: # ������ � �����
            xbee.send("tx",
                      frame_id='\x00',
                      dest_addr_long=device["PNS"],
                      broadcast_radius = '\x01',
                      dest_addr='\xFF\xFE',
                      data=msg_up)
        msg_up = None



def linkrs232():
    """ ����� �� ������� ��� ��������� � xbee """
    return


