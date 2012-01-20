#!/usr/bin/python
# -*- coding: cp1251 -*-

import ConfigParser
config = ConfigParser.SafeConfigParser()
config.read('default.cfg')
CAPACITANCE = config.getfloat('Power', 'capacitance') # ������� �������

# ������������ �������� ����������
#HIQUALITY = False
HIQUALITY = config.getboolean('Screen', 'hiquality') # ������� �������

# ��������� �������
screenH = 1024
screenV = 768
#screenH = 320
#screenV = 240
#screenH = 1280
#screenV = 960
centerH = (screenH / 2)
centerV = (screenV / 2)



# �������������� �������
TEST           = '\x00'
MANUALDRIVING  = '\x01' # ����� � ������� ������� ����������
TELEMETRY      = '\x02'
RAWDATA        = '\x03' # ��������� ������ ��� �������
LOGITEM        = '\x04'
ROUTEPOINT     = '\x05'
CONTROL        = '\x06' # ������������ ������� �� ���� ���� ����� ������������
SETTINGS_SERVO = '\x07' # ��������� ����
SETTINGS_OTHER = '\x08' # ��������� ��������� �����
DATE           = '\x09' # ��������� �������

# ����������� ��������
READ  = '\x00'
WRITE = '\x01'


# ����������� ����������� ������
BLACK   = (0,0,0)
WHITE   = (255,255,255)
RED     = (255, 0, 0)
GREEN   = (0, 255, 0)
BLUE    = (0, 0, 255)
YELLOW  = (255, 255, 0)

NORMAL  = GREEN
WARNING = YELLOW
DANGER  = RED

### ������ ���������� � ������ ###
# ���������� � �������
VCOLORLIST = [    WARNING,    NORMAL]
VVALUELIST = [5.5,        5.8,       7.5] # ��� ��������-��������� 6 �����
VSTEP  = 0.1
# ��� � �������
CCOLORLIST = [    NORMAL,     WARNING]
CVALUELIST = [0.0,       35.0,        45.0] # ��� LiPo
CSTEP  = 0.1
# ������� � ����������. ������ ������ � ����� �������.
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


# ����������� �������
import pygame
pygame.init()
bigFont   = pygame.font.SysFont("Courier New", 40, True)
mediumFont   = pygame.font.SysFont("Courier New", 20, True)
smallFont = pygame.font.SysFont("Courier New", 11, True)







