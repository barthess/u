#!/usr/bin/python
# -*- coding: cp1251 -*-

from multiprocessing import Queue
from datetime import datetime
import csv
import time
import struct
import os
from binascii import hexlify


# logging facilities
def record(q_log, e_pause, e_kill):
    """ q_log -- очередь сообщений """

    # инициализация записывальшика лога
    st = str(datetime.now())
    clear_datetime = ''
    i = 0
    # заменим двоеточия на точки
    while i < 19:
        if st[i] == ':' :
            clear_datetime += '.'
        else: clear_datetime += st[i]
        i += 1
    # откроем на запись файл
    csvwriter = csv.writer(open(clear_datetime + '.csv', 'wb'), delimiter=';')

    print "--- logwriter ready"
    e_pause.wait()
    print "--- logwriter run"

    while True:
        if e_kill.is_set():
            print "=== LogWriter. Kill signal received. Exiting"
            return

        try:
            msg = q_log.get(True, 1)
            rdl = list(msg)
            rdl.insert(0, str(time.time()))
            csvwriter.writerow(rdl)
        except:
            pass






def playraw(filename, q_tlm, e_pause, e_kill, ):
    """ смотрелка телеметрии
    """
    blocksize = 64 # такими блоками лежат данные в файле
    filesize = os.path.getsize(filename)

    f = open(filename, 'rb')
    row = struct.unpack('2i 2I 8H 8h 7B 1b 8x', f.read(blocksize))
    f.seek(blocksize, 1)

    time_n = float(row[3]) + float(row[4]) / 1000
    time_p = float(row[3]) + float(row[4]) / 1000

    # ждем, пока нас снимут с паузы
    print "--- play ready"
    e_pause.wait()
    print "--- play run"

    while f.tell() < filesize:
        if e_kill.is_set():
            print "=== Play. Kill signal received. Exiting"
            return

        time_p = time_n
        time_n = float(row[3]) + float(row[4]) / 1000
        time.sleep(time_n - time_p)

        row = struct.unpack('2i 2I 8H 8h 7B 1b 8x', f.read(blocksize))
        f.seek(blocksize, 1)
        print row

        q_tlm.put(row)




def play(filename, q_tlm, e_pause, e_kill, ):
    """ смотрелка телеметрии
    Парсит файл лога и передает его в функцию рисования телеметрии.
    Так же отслеживает нажатие клавиш выхода из программы.

    logReader -- объект, представляющий читаемый csv-файл
    """

    logReader = csv.reader(open(filename, 'rb'), delimiter=';')
    rowint = [] # row for integers
    row = logReader.next()
    time_n = float(row[0])
    time_p = float(row[0])
    # ждем, пока нас снимут с паузы
    print "--- play ready"
    e_pause.wait()
    print "--- play run"

    for row in logReader:
        if e_kill.is_set():
            print "=== Play. Kill signal received. Exiting"
            return

        time_p = time_n
        time_n = float(row[0])
        time.sleep(time_n - time_p)

        row = row[1:] # откусываем поле локального времени

        # конвертаем строки в числа
        i = 0
        for st in row:
            rowint.insert(i, int(st))
            i += 1

        q_tlm.put(rowint)
        rowint = [] # очищаем буфер, чтобы он не рос бесконечно


