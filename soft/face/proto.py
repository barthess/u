#!/usr/bin/python
# -*- coding: cp1251 -*-

from struct import *
from binascii import hexlify

from localconfig import *

from multiprocessing import Queue, Event
from Queue import Empty, Full # для отлова исключений

# b signed char integer     1   
# B unsigned char integer   1 
# h short integer           2   
# H unsigned short integer  2   
# i int integer             4   
# I unsigned int integer    4   
# q long long integer       8
# Q unsigned long long integer 8


def manager(q_down, q_log, q_tlm, q_servo, e_pause, e_kill):

    """
    Сообщения из канээски (down). Их надо посортировать и распихать по соответствующим адресатам
    """

    line = None
    msgid = None

    # вспомогательные функции{{{
    def logitem_handler(q_log, q_tlm, line):
        logitem = unpack('2i 2I 10H 8h 6B 1b 1x', line)
        #print hexlify(line)
        # пихаем в очередь телеметрометра
        try:    q_tlm.put_nowait(logitem)
        except Full: pass
        # пихаем в очередь логгера
        try:    q_log.put_nowait(logitem)
        except Full: pass
    #}}}

    # ждем, пока нас снимут с паузы
    print "--- manager ready"
    e_pause.wait()
    print "--- manager run"

    while True:
        if e_kill.is_set():
            print "=== Manager. Kill signal received. Exiting"
            return

        line = q_down.get()
        msgid = line[0]
        line = line[1:]   # откусываем нахуй поле ID

        if msgid == TEST:
            print "TEST", line
        elif msgid == RAWDATA:
            print "RAWDATA", line
        elif msgid == LOGITEM:
            logitem_handler(q_log, q_tlm, line)
        elif msgid == SETTINGS_SERVO:
            #print "SETTINGS_SERVO----", hexlify(line)
            try:    q_servo.put_nowait(line)
            except Full: pass
        else:
            print "fuck", line





