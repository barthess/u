#!/usr/bin/python
# -*- coding: cp1251 -*-
#

import sys
import os
import time
import argparse
import ConfigParser
from struct import pack
from multiprocessing import Process, Queue, Lock, Event, freeze_support
from Queue import Empty, Full

import pygame
from pygame.locals import *


# ����������� ������
from dsp import *
from localconfig import *
import telemetry
import log
import link
import proto
import route
import servotuner



flags = {"lock" : Lock(), # �������� ������������� ������
         "compass_flag" : 0, # ���� 1 -- ������� � ���� �������, ���� ����� 1 -- ������� � ������
         "help_flag" : False,# ���� ������� -- ���������� ����� ������
         "map_flag" : False,# ���� ������� -- ���������� �� ������ �������
         "date_set_flag" : False,# ���� ������� -- �������� ��������� ����� � �������� � �������� ����
         "servo_tune_flag" : False,# ���� ������� -- ���������� ����� ��������� ����
         "altimeter_zero_adj_flag" : False,# ���� ������� -- ������� ������� ��������� ����
         "connection_interrup_flag" : False, # ���� ������� -- ������� �� ����� ����� � ���������������
         "logreplay_flag" : False, # ���� ������� -- ������� �� ����� ������ play
         }


q_log  = Queue(1) # �������������� ����
q_tlm  = Queue(1) # ��� ����������
q_drw  = Queue(1) # ��� ������� ������� ����������
q_down = Queue(8) # ��� ������� � ��������
q_up   = Queue(8) # ��� ������� �� �������
q_servo= Queue(1) # ��� ������������� ������������ ����

# ������� ��� ������������ �� ��� ���, ���� ������� � ��������� clear
e_pause = Event() # ��� ��� ���������� �������� �� �����
e_pause.clear()

e_kill = Event() # ����������� ������� �����������
e_kill.clear()

e_drvsync = Event() # ��� ������������� (� ����������� ����������) ��������� �� ������� ����������
e_drvsync.clear()






def main(q_tlm, q_up, q_servo, config):

    # game init code
    os.environ['SDL_VIDEO_WINDOW_POS'] = "%d,%d" % (1,1)
    pygame.init()

    #window = pygame.display.set_mode((screenH, screenV), DOUBLEBUF | FULLSCREEN | HWSURFACE)
    window = pygame.display.set_mode((screenH, screenV), DOUBLEBUF | HWSURFACE)
    pygame.display.set_caption('MOSK - Mobile Operational System Kamikaze')
    screen = pygame.display.get_surface()

    #�������������� �������� � ������� ������� ��������� ������ � ����.
    #���� ��������� �� ������� - ������� ����� ��������� ����
    try:
        j = pygame.joystick.Joystick(0)
        j.init()
        def get_drv():
            ail = (j.get_axis(0) + 1.0) * (float(0xFF) / 2)
            ail = int(round(ail,0))
            ele = (j.get_axis(1) + 1.0) * (float(0xFF) / 2)
            ele = int(round(ele,0))
            thr = (j.get_axis(2) + 1.0) * (float(0xFF) / 2)
            thr = int(round(thr,0))
            rud = (j.get_axis(3) + 1.0) * (float(0xFF) / 2)
            rud = int(round(rud,0))
            print "ail=", ail, "ele=", ele, "thr=", thr, "rud=", rud
            ail = pack('B',ail)
            ele = pack('B',ele)
            thr = pack('B',thr)
            rud = pack('B',rud)
            #drv_string = MANUALDRIVING + WRITE + ail + ele + thr + rud # ��� ��������
            drv_string = MANUALDRIVING + WRITE + rud + ail + thr + ele  # ��� �������
            return drv_string
    except:
        def get_drv():
            drv_string = MANUALDRIVING + WRITE + '\x00' + '\x00' + '\x80' + '\x80'
            return drv_string

    # ������������� ����������
    tlm = telemetry.Telemetry(config)
    tlm_data = []
    i = 0
    while i < 128:
        tlm_data.append(0)
        i += 1

    # ������� ����
    while True:
        flags["lock"].acquire() # ����� ����� �� ���������

        # ���������� ���������
        if q_up.empty():
            q_up.put_nowait(get_drv())

        # ���������� ������
        events = pygame.event.get()
        for event in events:
            if event.type == QUIT:
                return

            # ������� ������� ������
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    flags["compass_flag"] = 1
                elif event.key == pygame.K_DOWN:
                    flags["compass_flag"] = -1
                elif event.key == pygame.K_t: # ��������� �� �������� ������� ��������� �����
                    date_str = DATE + WRITE + pack('>L', int(round(time.time())))
                    q_up.put_nowait(date_str)
                elif event.key == pygame.K_F1: # �������� ����� ������
                    flags["help_flag"] = not flags["help_flag"]
                elif event.key == pygame.K_m: # �������� ����� �������
                    flags["map_flag"] = not flags["map_flag"]
                elif event.key == pygame.K_b: # ��������� ��������� � ����
                    flags["altimeter_zero_adj_flag"] = True
                elif event.key == pygame.K_s: # ��������� ����
                    p_servotuner = Process(target=servotuner.ServoTuner,
                                           args=(q_up, q_servo))
                    p_servotuner.start()
                elif event.key == pygame.K_p: # ������� ����� �������� � �������
                    p_upload = Process(target=Route.upload, args=(q_up, ))
                    p_upload.start()
            #������� ���������� ������
            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_DOWN or event.key == pygame.K_UP:
                    flags["compass_flag"] = 0

        flags["lock"].release()

        #������� �� ������� ������ ��� ����������
        try:
            tlm_data = q_tlm.get(True, 1)
            flags["lock"].acquire()
            flags["connection_interrupt_flag"] = False
            flags["lock"].release()
        except Empty:
            print "connection interrupted"
            flags["lock"].acquire()
            flags["connection_interrupt_flag"] = True
            flags["lock"].release()

        tlm.draw(tlm_data, screen, flags)









# ���������� ���������
if __name__ == '__main__':
    freeze_support()

    # command line parser
    parser = argparse.ArgumentParser(
            formatter_class=argparse.RawDescriptionHelpFormatter,
            # Usage text 
            description=(''' This is stub for command prompt help. '''))
    parser.add_argument('input_file',
            metavar='filename',
            nargs='?', # �������� ������������
            type=file,
            help='path to telemetry log file')
    args = parser.parse_args()

    # �������� ������. ������� �� ��� ��������� ������� ������������ ��������.
    config = ConfigParser.SafeConfigParser()
    config.read('default.cfg')

    # ������� ����������� �����.
    # ����������, ������ �� ���������� �� ����, ��� �� ����������
    e_pause.clear()
    e_kill.clear()

    p_main = Process(target=main, args=(q_tlm, q_up, q_servo, config, ))

    if args.input_file != None:
        if args.input_file.name[-3:] != 'raw':
            p_logreader = Process(target=log.play,
                                  args=(args.input_file.name, q_tlm,
                                        e_pause, e_kill, ))
        else:
            p_logreader = Process(target=log.playraw,
                                  args=(args.input_file.name, q_tlm,
                                        e_pause, e_kill, ))
        p_logreader.start()
    else:
        p_link = Process(target=link.linkxbee,
                         args=(q_down, q_up, e_pause,
                               e_kill, config, ))
        p_link.start()
        p_logwriter = Process(target=log.record,
                              args=(q_log, e_pause, e_kill, ))
        p_logwriter.start()
        p_protomanager = Process(target=proto.manager,
                                 args=(q_down, q_log,
                                       q_tlm, q_servo,
                                       e_pause, e_kill, ))
        p_protomanager.start()


    p_main.start()
    time.sleep(1) # ����, ���� ��� �������� �����������
    print "--- clear global pause"
    e_pause.set() # ������� � ����� ����������� ��������

    p_main.join() # ���� ���������� �������� ��������
    e_kill.set()  # ���������� ���� ��������� �����

    time.sleep(0.5)
    # http://metazin.wordpress.com/2008/08/09/how-to-kill-a-process-in-windows-using-python/
    os.system("taskkill /im python.exe /f")
    p_protomanager.join()
    p_link.join()
    p_logwriter.join()






