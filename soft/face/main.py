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


# самопальные модули
from dsp import *
from localconfig import *
import telemetry
import log
import link
import proto
import route
import servotuner



flags = {"lock" : Lock(), # примитив синхронизации флагов
         "compass_flag" : 0, # если 1 -- крутить в одну сторону, если минус 1 -- крутить в другую
         "help_flag" : False,# если взведен -- показывать экран помощи
         "map_flag" : False,# если взведен -- показывать на экране маршрут
         "date_set_flag" : False,# если взведен -- записать системное время в канээску и сбросить флаг
         "servo_tune_flag" : False,# если взведен -- показывать экран настройки серв
         "altimeter_zero_adj_flag" : False,# если взведен -- вызвать функцию установки нуля
         "connection_interrup_flag" : False, # если взведен -- вывести на экран бирку с предупреждением
         "logreplay_flag" : False, # если взведен -- вывести на экран значок play
         }


q_log  = Queue(1) # записывальщика лога
q_tlm  = Queue(1) # для телеметрии
q_drw  = Queue(1) # для пакетов ручного управления
q_down = Queue(8) # для пакетов с самолета
q_up   = Queue(8) # для пакетов на самолет
q_servo= Queue(1) # для калбировочных коэффициетов серв

# события для блокирования до тех пор, пока событие в состоянии clear
e_pause = Event() # лок для постановки процесса на паузу
e_pause.clear()

e_kill = Event() # предложение умереть добровольно
e_kill.clear()

e_drvsync = Event() # для синхронизации (и выборочного отключения) сообщений от ручного управления
e_drvsync.clear()






def main(q_tlm, q_up, q_servo, config):

    # game init code
    os.environ['SDL_VIDEO_WINDOW_POS'] = "%d,%d" % (1,1)
    pygame.init()

    #window = pygame.display.set_mode((screenH, screenV), DOUBLEBUF | FULLSCREEN | HWSURFACE)
    window = pygame.display.set_mode((screenH, screenV), DOUBLEBUF | HWSURFACE)
    pygame.display.set_caption('MOSK - Mobile Operational System Kamikaze')
    screen = pygame.display.get_surface()

    #инициализируем джойстик и объявим функцию получения данных с него.
    #Если джойстика не найдено - функция будет присылать нули
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
            #drv_string = MANUALDRIVING + WRITE + ail + ele + thr + rud # для самолета
            drv_string = MANUALDRIVING + WRITE + rud + ail + thr + ele  # для машинки
            return drv_string
    except:
        def get_drv():
            drv_string = MANUALDRIVING + WRITE + '\x00' + '\x00' + '\x80' + '\x80'
            return drv_string

    # инициализация телеметрии
    tlm = telemetry.Telemetry(config)
    tlm_data = []
    i = 0
    while i < 128:
        tlm_data.append(0)
        i += 1

    # главный цикл
    while True:
        flags["lock"].acquire() # чтобы флаги не испортить

        # обработчик джойстика
        if q_up.empty():
            q_up.put_nowait(get_drv())

        # обработчик клавиш
        events = pygame.event.get()
        for event in events:
            if event.type == QUIT:
                return

            # события нажатия клавиш
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    flags["compass_flag"] = 1
                elif event.key == pygame.K_DOWN:
                    flags["compass_flag"] = -1
                elif event.key == pygame.K_t: # установим на кунээске текущее системное время
                    date_str = DATE + WRITE + pack('>L', int(round(time.time())))
                    q_up.put_nowait(date_str)
                elif event.key == pygame.K_F1: # выбросим экран помощи
                    flags["help_flag"] = not flags["help_flag"]
                elif event.key == pygame.K_m: # выбросим экран маршрут
                    flags["map_flag"] = not flags["map_flag"]
                elif event.key == pygame.K_b: # установим альтиметр в ноль
                    flags["altimeter_zero_adj_flag"] = True
                elif event.key == pygame.K_s: # настройка серв
                    p_servotuner = Process(target=servotuner.ServoTuner,
                                           args=(q_up, q_servo))
                    p_servotuner.start()
                elif event.key == pygame.K_p: # закинем точки маршрута в самолет
                    p_upload = Process(target=Route.upload, args=(q_up, ))
                    p_upload.start()
            #события отпускания клавиш
            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_DOWN or event.key == pygame.K_UP:
                    flags["compass_flag"] = 0

        flags["lock"].release()

        #возьмем из очереди данные для телеметрии
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









# запускатор процессов
if __name__ == '__main__':
    freeze_support()

    # command line parser
    parser = argparse.ArgumentParser(
            formatter_class=argparse.RawDescriptionHelpFormatter,
            # Usage text 
            description=(''' This is stub for command prompt help. '''))
    parser.add_argument('input_file',
            metavar='filename',
            nargs='?', # аргумент необязателен
            type=file,
            help='path to telemetry log file')
    args = parser.parse_args()

    # загрузим конфиг. Позднее мы его передадим каждому нуждающемуся процессу.
    config = ConfigParser.SafeConfigParser()
    config.read('default.cfg')

    # главная программная вилка.
    # Определяет, читаем мы телеметрию из лога, или из устройства
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
    time.sleep(1) # ждем, пока все процессы подхватятся
    print "--- clear global pause"
    e_pause.set() # снимаем с паузы порожденные процессы

    p_main.join() # ждем завершения главного процесса
    e_kill.set()  # предлагаем всем остальным выйти

    time.sleep(0.5)
    # http://metazin.wordpress.com/2008/08/09/how-to-kill-a-process-in-windows-using-python/
    os.system("taskkill /im python.exe /f")
    p_protomanager.join()
    p_link.join()
    p_logwriter.join()






