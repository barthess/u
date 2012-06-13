#!/usr/bin/python
# -*- coding: cp1251 -*-

import ConfigParser
config = ConfigParser.SafeConfigParser()
config.read('default.cfg')
CAPACITANCE = config.getfloat('Power', 'capacitance') # емкость батареи

# переключалка качества рендеринга
#HIQUALITY = False
HIQUALITY = config.getboolean('Screen', 'hiquality') # емкость батареи

# геометрия дисплея
screenH = 1024
screenV = 768
#screenH = 320
#screenV = 240
#screenH = 1280
#screenV = 960
centerH = (screenH / 2)
centerV = (screenV / 2)



# идентификаторы пакетов
TEST           = '\x00'
MANUALDRIVING  = '\x01' # Пакет с данными ручного управления
TELEMETRY      = '\x02'
RAWDATA        = '\x03' # Структура данных для отладки
LOGITEM        = '\x04'
ROUTEPOINT     = '\x05'
CONTROL        = '\x06' # Переключение режимов на лету либо иного непотребства
SETTINGS_SERVO = '\x07' # Настройки серв
SETTINGS_OTHER = '\x08' # Настройки остальной хрени
DATE           = '\x09' # Установка времени

# направление передачи
READ  = '\x00'
WRITE = '\x01'


# читабельные обозначения цветов
BLACK   = (0,0,0)
WHITE   = (255,255,255)
RED     = (255, 0, 0)
GREEN   = (0, 255, 0)
BLUE    = (0, 0, 255)
YELLOW  = (255, 255, 0)

NORMAL  = GREEN
WARNING = YELLOW
DANGER  = RED

### списки диапазонов и цветов ###
# напряжение в вольтах
VCOLORLIST = [    WARNING,    NORMAL]
VVALUELIST = [5.5,        5.8,       7.5] # для свинцово-кислотной 6 банок
VSTEP  = 0.1
# ток в амперах
CCOLORLIST = [    NORMAL,     WARNING]
CVALUELIST = [0.0,       35.0,        45.0] # для LiPo
CSTEP  = 0.1
# топливо в амперчасах. Удобно задать в долях емкости.
FCOLORLIST = [                  NORMAL,                 WARNING]
FVALUELIST = [0.0 * CAPACITANCE,      0.5 * CAPACITANCE,       0.75 * CAPACITANCE]
FSTEP  = 0.05
#air speed
ASCOLORLIST = [   WARNING,   NORMAL,   WARNING]
ASVALUELIST = [10,        15,        25,      28]
ASSTEP      = 1
# variometer
VARIOCOLORLIST = [   WARNING,   NORMAL,  WARNING]
VARIOVALUELIST = [-10,       -5,       5,       10]
VARIOSTEP      = 1


# определения шрифтов
import pygame
pygame.init()
bigFont   = pygame.font.SysFont("Courier New", 40, True)
mediumFont   = pygame.font.SysFont("Courier New", 20, True)
smallFont = pygame.font.SysFont("Courier New", 11, True)







