#!/usr/bin/python
# -*- coding: cp1251 -*-
#


import pygame
from math import *
from datetime import datetime

from localconfig import *
from dsp import *
from route import Polyline

import dials


class Telemetry():
    def __init__(self, config):
        self._rectlist = []
        ##### инициализация наших приборов приборной доски
        # Альтиметр
        self.altimeter = dials.Altimeter(100)
        # вариометр
        self.variometer = dials.Variometer(504, 12, WHITE, mediumFont, True, -6, 6)
        #воздушный спидометр
        self.speedometer = dials.Speedometer(280, 8, WHITE, mediumFont, False, 0, 40)
        #энергомер
        self.pmeter = dials.Powermeter(config)
        # авиагоризонт
        self.gyrohoryzonI = dials.GyroHorizon(int(0.25 * screenV))
        self.gyrohoryzonA = dials.GyroHorizon(int(0.20 * screenV))
        self.gyrohoryzonG = dials.GyroHorizon(int(0.20 * screenV))
        #self._gyro = Gyroscope()
        # начальный угол компаса
        self.compass_dest = 0.0
        # сам компас
        self.gps_compass = dials.Compass(100, "big")
        # объект, отображающий маршрут
        self._polyline = Polyline()
        # помощь по F1
        self.helpscreen = dials.HelpScreen()
        self.i = 0

        self.Gx = 0.0
        self.Gy = 0.0
        self.Gz = 0.0



    def __normalize(self, a):
        """normalize data to avoid math errors"""
        if (a > 2**14):
            return float(2*14)
        elif(a < -(2**14)):
            return float(-(2**14))
        else:
            return float(a)


    def __blittlm(self, bgsurf, fgsurf, coord):
        """
        Функция блитает одну поверхность на другую и добавляет
        вёрнутый прямоугольник в список для обновления экрана

        bgsurf -- подложка, скорее всего экран
        fgsurf -- поверхность, которую надо нарисовать на подложке
        coord -- координаты
        rectlist -- список прямоугольников для оптимизированного обновления экрана
        """
        self._rectlist.append(bgsurf.blit(fgsurf, coord))



    def draw(self, tlm_data, screen, flags):
        """Рисовалка телеметрии

        Принимает список чисел и распихивает их в
        объекты в качестве аргументов

        """
        __rectlist2 = []

        s = None # переменная для временного хранения поверхности
        """ описание структуры сырых данных """ #{{{
        i = 0
        tlm_gps_lat     = tlm_data[i]; i+=1
        tlm_gps_long    = tlm_data[i]; i+=1
        tlm_gps_time    = tlm_data[i]; i+=1

        tlm_rtcsec      = tlm_data[i]; i+=1
        tlm_rtcmsec     = tlm_data[i]; i+=1

        tlm_aileron     = tlm_data[i]; i+=1
        tlm_elevator    = tlm_data[i]; i+=1
        tlm_throttle    = tlm_data[i]; i+=1
        tlm_rudder      = tlm_data[i]; i+=1

        tlm_sonar       = tlm_data[i]; i+=1
        tlm_current     = tlm_data[i]; i+=1

        tlm_gyrofi_x    = tlm_data[i]; i+=1
        tlm_gyrofi_y    = tlm_data[i]; i+=1
        tlm_gyrofi_z    = tlm_data[i]; i+=1

        tlm_accel_x     = tlm_data[i]; i+=1
        tlm_accel_y     = tlm_data[i]; i+=1
        tlm_accel_z     = tlm_data[i]; i+=1

        tlm_imu_x       = tlm_data[i]; i+=1
        tlm_imu_y       = tlm_data[i]; i+=1
        tlm_imu_z       = tlm_data[i]; i+=1

        tlm_baro_height = tlm_data[i]; i+=1
        tlm_gps_alt     = tlm_data[i]; i+=1

        tlm_voltage     = tlm_data[i]; i+=1
        tlm_airspeed    = tlm_data[i]; i+=1
        tlm_enginerpm   = tlm_data[i]; i+=1

        tlm_gps_speed   = tlm_data[i]; i+=1
        tlm_gps_course  = tlm_data[i]; i+=1
        tlm_cpuload     = tlm_data[i]; i+=1

        tlm_tmp75       = tlm_data[i]; i+=1
        #}}}

        pns_time = float(tlm_rtcsec) + float(tlm_rtcmsec) / 1000

        """ крен-тангаж"""#{{{
        """ данные для калибровки акселерометра:
        762.6     16388.9  -313.2  -- x down
        -508.2    -16122.7 -281.1  -- x up

        16204.1   622.5    -328.0  -- z down
        -16400.0  483      -430    -- z up

        -100      -20      -16805  -- y down
        234.9     458.9    16188.5 -- y up

        Если смотреть на самолет сверху:
        x -- направлена по ходу движения
        y -- вверх
        z -- в сторону правого крыла
        вращение считается положительным, если происходит по часовой стрелке,
        когда взгляд направлен в направлении оси (правило буравчика)"""

        #TODO: сделать компенсацию неортогональности (_cal_Accelerometer_AN3192.pdf)
        Ax = tlm_accel_x / 1000.0
        Ay = tlm_accel_y / 1000.0
        Az = tlm_accel_z / 1000.0

        # получим обороты
        self.Gx = tlm_gyrofi_x / 65536.0
        self.Gy = tlm_gyrofi_y / 65536.0
        self.Gz = tlm_gyrofi_z / 65536.0

        #print self.Gy
        # получим радианы
        self.Gx = 2 * pi * self.Gx
        # 0.5 нужно для того, чтобы сделать диапазон (-pi,pi) вместо (0,2*pi)
        if self.Gy < 0.5:
            self.Gy = 2 * pi * self.Gy
        else:
            self.Gy = 2 * pi * abs(self.Gy - 0.5) - pi

        self.Gz = 2 * pi * self.Gz

        Ix = tlm_imu_x / 10000.0
        Iy = tlm_imu_y / 10000.0
        Iz = tlm_imu_z / 10000.0

        st = "Ix  " + str(Ix)
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (300,screenV-50))
        st = "Iy  " + str(Iy)
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (400,screenV-50))
        st = "Iz  " + str(Iz)
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (500,screenV-50))

        st = "Gx  " + str(round(self.Gx, 4))
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (300,screenV-60))
        st = "Gy  " + str(round(self.Gy, 4))
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (400,screenV-60))
        st = "Gz  " + str(round(self.Gz, 4))
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (500,screenV-60))

        st = "Ax  " + str(Ax)
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (300,screenV-70))
        st = "Ay  " + str(Ay)
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (400,screenV-70))
        st = "Az  " + str(Az)
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (500,screenV-70))

        #print  "(Gx)\t", Gx, "(Gy)\t", Gy, "(Gz)\t", Gz, "(Ax)\t", Ax, "(Ay)\t", Ay, "(Az)\t", Az

        # крен, тангаж в радианах
        # пикирование - отрицательный тангаж, кабрирование - положительный
        # крен в лево - отрицательный, крен в право - положительный

        roll  = atan2(Iy, Iz)
        pitch = atan2(Ix, Iz)
        s = self.gyrohoryzonI.get(roll, pitch)
        self.__blittlm(screen, s, (0.30 * centerH, 0.25 * centerV))

        roll  = atan2(Ay, Az)
        pitch = atan2(Ax, Az)
        s = self.gyrohoryzonA.get(roll, pitch)
        self.__blittlm(screen, s, (1.1 * centerH, 0.2 * centerV))

        roll  = self.Gx
        pitch = self.Gy
        s = self.gyrohoryzonG.get(roll, pitch)
        self.__blittlm(screen, s, (0.85 * centerH, 0.85 * centerV))

        #}}}
        """ высота """#{{{
        # установка нуля
        if flags["altimeter_zero_adj_flag"]:
            self.altimeter.zero_adjust()
            flags["altimeter_zero_adj_flag"] = False

        # высота ультразвуковая
        alt_sonar = float(tlm_sonar) / 100 # получим метры 

        # барометрическая высота
        p0 = 101325.0 # давление на уровне моря (Па)
        height = float(tlm_baro_height) / 10
        pressure = pow(((44330 - height) / 44330), 5.255) * p0

        # высотомер на экран
        s = self.altimeter.get(height, alt_sonar)
        self.__blittlm(screen, s, (700,500))

        # вариометр на экран
        c = (screenH - 150, 100)
        rect = self.variometer.put(screen, c, height)
        __rectlist2.append(rect)


        #дебаговую инфу на экран
        st = "pressure  = " + str(floor(pressure)) + " Pa"
        s = smallFont.render(st, 0, (WHITE))
        self.__blittlm(screen, s, (centerV,screenV-20))

        p_weather = 0.01*pressure / ((288-0.0065*220)/288)**5.256
        st = "p_weather = " + str(round(p_weather,1)) + " hPa"
        s = smallFont.render(st, 0, (WHITE))
        self.__blittlm(screen, s, (centerV,screenV-30))

        st = "above_sea = " + str(round(height, 1)) + " m"
        s = smallFont.render(st, 0, (WHITE))
        self.__blittlm(screen, s, (centerV,screenV-40))
        #}}}
        """ воздушная скорость """#{{{
        speed = (tlm_airspeed >> 3) + (tlm_airspeed % 8) / 8.0
        # чтобы индикатор на низких скоростях не дрыгался - будем его там игнорировать
        if (speed < 4):
            speed = 0

        rect = self.speedometer.put(screen, (0, 70), speed)
        __rectlist2.append(rect)
        #}}}
        """ Отображает положения рулей """ #{{{
        self.__blittlm(screen, smallFont.render("elevator = " + str(tlm_elevator), 0, (WHITE)), (0,screenV - 20))
        self.__blittlm(screen, smallFont.render("rudder   = " + str(tlm_rudder),   0, (WHITE)), (0,screenV - 30))
        self.__blittlm(screen, smallFont.render("aileron  = " + str(tlm_aileron),  0, (WHITE)), (0,screenV - 40))


        s = smallFont.render("throttle = " + str(tlm_throttle), 0, (WHITE))
        self.__blittlm(screen, s, (0,screenV - 50))

        #}}}
        """ Power """ #{{{
        voltage = float(tlm_voltage) / 10
        current = float(tlm_current) / 1000

        rect = self.pmeter.put(screen, (3*screenH/4, 0), voltage, current, pns_time)
        #print __rectlist2
        #for i in rect:
        #    print i
        __rectlist2.append(rect)
        #print __rectlist2
        #}}}
        """ Рисует температурные индикаторы """#{{{
        t_tmp75 = float(tlm_tmp75)
        st = "t. tmp75  = " + str(round(t_tmp75,1)) + " °C"
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (1.6 * centerH,screenV-30))
        #}}}
        """ GPS """ #{{{
        # широта
        gps_lat = float(tlm_gps_lat) / 100000
        st = "GPS lat    = " + str(round(gps_lat,5)) + " °"
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (10,10))
        # долгота
        gps_long = float(tlm_gps_long) / 100000
        st = "GPS long   = " + str(round(gps_long,5)) + " °"
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (10,20))
        # высота по GPS
        gps_alt = tlm_gps_alt
        st = "GPS height = " + str(round(gps_alt,1)) + " m"
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (10,30))
        # скорость по GPS
        gps_speed = float(tlm_gps_speed)
        st = "GPS speed  = " + str(round(gps_speed, 1)) + " m/s"
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (10,40))
        # курс по GPS
        gps_course = (float(tlm_gps_course) / 256) * 360 # перевод из условных единиц в градусы
        st = "GPS course = " + str(round(gps_course,1)) + " °"
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (10,50))
        # время по GPS
        gps_time = float(tlm_gps_time)
        st = "GPS time   = " + str(gps_time) + " "
        self.__blittlm(screen, smallFont.render(st, 0, (GREEN)), (10,60))
        # компас
        self.compass_dest += flags["compass_flag"]
        gps_compass_surf = self.gps_compass.get(gps_course, self.compass_dest)
        self.__blittlm(screen, gps_compass_surf, (10,470))
        # сброс координат в рисовальщик маршрута
        Polyline.addpoint(self._polyline, gps_lat, gps_long)
        #}}}
        """ Time """ #{{{
        st = str(datetime.fromtimestamp(tlm_rtcsec)) + "." + str(tlm_rtcmsec/100)
        self.__blittlm(screen, mediumFont.render(st, HIQUALITY, (WHITE)), (centerH - 200,10))
        #}}}
        """ Tachometer """ #{{{
        st = "tacho = " + str(tlm_enginerpm * 60) + " RPM"
        self.__blittlm(screen, mediumFont.render(st, HIQUALITY, (GREEN), BLACK), (centerH - 130,50))
        #}}}

        """ Other """ #{{{
        if flags["logreplay_flag"] == True:
            self.__blittlm(screen, mediumFont.render("REPLAY!", HIQUALITY, (RED)), (centerH - 230,10))

        if flags["help_flag"] == True:
            #screen.blit(self.helpscreen.get(), (0,0))
            rect = self.helpscreen.put(screen, (0,0))
            __rectlist2.append(rect)

        if flags["map_flag"] == True:
            screen.blit(Polyline.draw(self._polyline), (0,0))

        self.i += 1
        if flags["connection_interrupt_flag"]:
            color = (255, 255 * (self.i % 2), 255 * (self.i % 2))
            cint_surf = bigFont.render("!!! CONNECTION INTERRUPTED !!!", HIQUALITY, color)
            self.__blittlm(screen, cint_surf, (150,10))

        # всякий отладочный вывод
        #print tlm_enginerpm * 60
        #print tlm_sattime
        #}}}
        # мышиный курсор
        pygame.draw.circle(screen, RED, (pygame.mouse.get_pos()), 15, 1)

        # обновим дисплей
        #pygame.display.update(__rectlist2)
        #for i in __rectlist2:
        #    screen.fill(BLACK, i)
        __rectlist2 = []

        pygame.display.flip()
        screen.fill((BLACK))

