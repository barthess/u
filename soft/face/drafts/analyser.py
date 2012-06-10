#!/usr/bin/python
# -*- coding: cp1251 -*-

import serial
import string
import sys
from decimal import *
getcontext().prec = 64

ser = serial.Serial(0, 115200)
#ser = serial.Serial(16, 115200)

# TODO: изменить символ конца строки на '\r\n'

iteration = 16
stat = 16

zero_scale = Decimal('10000.0')

zero_X = Decimal('0.0')
zero_X_max = Decimal('1900.0') / zero_scale
zero_X_min = Decimal('1800.0') / zero_scale

zero_Y = Decimal('0.0')
zero_Y_max = Decimal('1900.0') / zero_scale
zero_Y_min = Decimal('1800.0') / zero_scale

zero_Z = Decimal('0.0')
zero_Z_max = Decimal('1900.0') / zero_scale
zero_Z_min = Decimal('1800.0') / zero_scale

zero_ref = 1491

#TODO: заменить позже во всей программе одиночные
# значения на списки
samples_count = 5 # количество точек интегрирования
val_count = 1 + 3 + 1 + 1 + 1 # опорное + 3 гироскопа + джойстик + батарейка + опорное

X = 0.0
Xf = [0,0,0,0,1850.0,1491]
Y = 0.0
Yf = [0,0,0,0,1850.0,1491]
Z = 0.0
Zf = [0,0,0,0,1850.0,1491]

bat = 0.0

i = 0;
j = 0;



""" Вычисляет интеграл по формуле Буля
Для упрощения примем t = 1. К реальному
времени приведёмся в самом конце

Принимает:
    f - список значений функции в пяти точках
Возвращает:
    интеграл на этих пяти точках """
def boole(f, correction):
    #I = 0.0
    a = 0
    b = 4
    I = (float(b - a) / 90) * (7*f[0] + 32*f[1] + 12*f[2] + 32*f[3] + 7*f[4])
    if correction & (I > 0):
        I = I * float(1571)/float(1578)
    return Decimal(str(I))

""" Полученный массив бинарных данных распихивает по спискам """
def get_samples():
    i = 1
    # последняя точка старого списка 
    # должна стать первой точкой нового
    Xf[0] = Xf[samples_count - 1]
    Yf[0] = Yf[samples_count - 1]
    Zf[0] = Zf[samples_count - 1]

    while i < samples_count:
        line = ser.read(val_count * 2 + 2)

        if len(line) == val_count * 2 + 2:

            old_ref = Xf[5]
            new_ref = ord(line[13])*256 + ord(line[12])
            delta_ref = new_ref - old_ref
            ajust = float(delta_ref) / zero_ref
            Xf[5] = new_ref

            Xf[i] = float(ord(line[7])*256 + ord(line[6]))# - ajust
            Yf[i] = float(ord(line[5])*256 + ord(line[4]))# - ajust
            Zf[i] = float(ord(line[3])*256 + ord(line[2]))# - ajust

            i += 1




line = ser.readline() # чтобы мусор попал именно сюда
line = ser.readline() # чтобы мусор попал именно сюда


while j < iteration:
    print '\n','--------------',j,' iteration ----------------','\n'
    Z = 0
    X = 0
    Y = 0
    while i < stat:#stat * (j*0.2 + 1):
        get_samples()

        zero_X = zero_X_min + ((zero_X_max - zero_X_min) / 2)
        X += boole(Xf, 1)/zero_scale - (samples_count - 1) * zero_X

        zero_Y = zero_Y_min + ((zero_Y_max - zero_Y_min) / 2)
        Y += boole(Yf, 1)/zero_scale - (samples_count - 1) * zero_Y

        zero_Z = zero_Z_min + ((zero_Z_max - zero_Z_min) / 2)
        Z += boole(Zf, 1)/zero_scale - (samples_count - 1) * zero_Z

        print 'Z:',Z, ', zero_Z:', zero_Z, '\t','Y:',Y, ', zero_Y:', zero_Y, '\t','X:',X, ', zero_X:', zero_X
        #print 'Zf', Zf,'Yf', Yf,'Xf', Xf
        #break

        i += 1

    if Z < 0: # уменьшаем максимум
        zero_Z_max = zero_Z + Decimal('0.3')*(zero_Z - zero_Z_min)
    elif Z > 0:
        zero_Z_min = zero_Z - Decimal('0.3')*(zero_Z_max - zero_Z)
    #print zero_Z_max, zero_Z_min

    if Y < 0: # уменьшаем максимум
        zero_Y_max = zero_Y + Decimal('0.3')*(zero_Y - zero_Y_min)
    elif Y > 0:
        zero_Y_min = zero_Y - Decimal('0.3')*(zero_Y_max - zero_Y)
    #print zero_Y_max, zero_Y_min

    if X < 0: # уменьшаем максимум
        zero_X_max = zero_X + Decimal('0.3')*(zero_X - zero_X_min)
    elif X > 0:
        zero_X_min = zero_X - Decimal('0.3')*(zero_X_max - zero_X)
    #print zero_X_max, zero_X_min

    i = 0
    j += 1

# теперь надо подогнать последние разряды нулей
#0.184521003442
#0.000000000001
#j = 0
#i = 0
#while j < iteration / 2:
#    print '\n','--------------',j,' tuning ----------------','\n'
#    Z = 0
#    X = 0
#    Y = 0
#    #print 'zero_Z:', zero_Z, '\t','zero_Y:', zero_Y,'\t', 'zero_X:', zero_X
#    while i < stat * 16:
#        get_samples()
#        X += boole(Xf)/zero_scale - (samples_count - 1) * zero_X
#        Y += boole(Yf)/zero_scale - (samples_count - 1) * zero_Y
#        Z += boole(Zf)/zero_scale - (samples_count - 1) * zero_Z
#
#        print 'Z:',Z, ', zero_Z:', zero_Z, '\t','Y:',Y, ', zero_Y:', zero_Y, '\t','X:',X, ', zero_X:', zero_X
#        #print 'Zf', Zf,'Yf', Yf,'Xf', Xf
#        #break
#
#        i += 1
#
#    if Z < 0: # уменьшаем максимум
#        zero_Z -= 0.000000000001
#    elif Z > 0:
#        zero_Z += 0.000000000001
#
#    if Y < 0: # уменьшаем максимум
#        zero_Y -= 0.000000000001
#    elif Y > 0:
#        zero_Y += 0.000000000001
#
#    if X < 0: # уменьшаем максимум
#        zero_X -= 0.000000000001
#    elif X > 0:
#        zero_X += 0.000000000001
#
#    i = 0
#    j += 1





#zero_Z = 1870.25
#zero_X = 1870.25
#zero_Y = 1870.25
Z_S0 = Decimal('3.752') / (Decimal('1495') / zero_Z)
Y_S0 = Decimal('3.752') / (Decimal('1495') / zero_Y)
X_S0 = Decimal('3.752') / (Decimal('1495') / zero_X)
Z = 0
X = 0
Y = 0

print '\n','-------------- angles in degrees ----------------','\n'

i = 0
while 1:

    get_samples()
    Z += ((boole(Zf, 1)/zero_scale - (samples_count - 1) * zero_Z) * Decimal('0.0022')) / Z_S0
    X += ((boole(Xf, 1)/zero_scale - (samples_count - 1) * zero_X) * Decimal('0.0022')) / X_S0
    Y += ((boole(Yf, 1)/zero_scale - (samples_count - 1) * zero_Y) * Decimal('0.0022')) / Y_S0

    bat = float(ord(line[11])*256 + ord(line[10])) / 376.3333

    #print round(((boole(Zf)/zero_scale - (samples_count - 1) * zero_Z)) / Z_S0, 4)
    print 'Z =',round((-1*Z),4),'\t','Y =',round((-1*Y),4),'\t','X =',round((-1*X),4),'\t','bat =', round(bat,4), 'V'










