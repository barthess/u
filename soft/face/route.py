#!/usr/bin/python
# -*- coding: cp1251 -*-

from multiprocessing import Queue
import csv
from struct import *
from binascii import hexlify

from localconfig import *

def upload(q_up):
    """
    загружалка маршрута
    """
    filename = './test/routes.csv'
    f = open(filename, 'rb')
    routesreader = csv.reader(f, delimiter=';')


    for row in routesreader:
        # конвертаем строки в числа. Плавучку округляем до 5 знаков и
        # переводим в фиксированную точку -- это
        # внутренний формат автопелота.
        # TODO в идеале проверку на слишком большую дальность
        lat = float(row[0])
        if lat > 90 or lat < -90:
            raise ValueError('Latitude must be in range from -90 to 90')
        lat = int(round(lat, 5) * (10**5))

        lon = float(row[1])
        if lon > 180 or lon < -180:
            raise ValueError('Longitude must be in range from -180 to 180')
        lon = int(round(lon, 5) * (10**5))

        alt = int(row[2])
        if alt > 3200 or alt < -200:
            raise ValueError('Altitude must be in range from -200 to 3200')

        spd = int(row[3])
        if spd > 40 or spd < 0:
            raise ValueError('Speed must be in range from 15 to 40')

        pointdata = pack('>llhb', lat, lon, alt, spd)
        pointdata = ROUTEPOINT + WRITE + pointdata
        print "route point uploaded:", lat, lon, alt, spd
        #print hexlify(pointdata)
        q_up.put(pointdata)

    f.close()



class Polyline: #{{{
    """ Рисует ломаную маршрута поверх требуемого фона. """

    # поверхность для рисования
    surf = None
    # для каменной горки
    map00 = (27.42556, 53.91334) # левый верхний угол карты
    map11 = (27.43155, 53.91086) # правый нижний угол карты

    # для матуги
    #map00 = (27.65561, 53.84450) # левый верхний угол карты
    #map11 = (27.66960, 53.83870) # правый нижний угол карты

    # начальная и конечная точка для отрисовки маршрута
    route_b = (0,0)
    route_e = (0,0)

    ready = False

    def __init__(self):
        mapbitmap = pygame.image.load("kg00.png")
        H = mapbitmap.get_width()
        V = mapbitmap.get_height()
        self.surf = pygame.Surface((screenH, screenV))
        self.surf.blit(mapbitmap, (0,0))
        self.xveight = (self.map11[0] - self.map00[0]) / H # вес одного пикселя
        self.yveight = (self.map00[1] - self.map11[1]) / V # вес одного пикселя


    def addpoint(self, gps_lat, gps_long):
        x = int(round(((self.map11[0] - gps_long) / self.xveight), 0))
        y = int(round(((self.map00[1] - gps_lat)  / self.yveight), 0))
        self.route_b = self.route_e
        self.route_e = (x, y)
        if self.route_e != self.route_b:
            pygame.draw.aaline(self.surf, RED, self.route_b, self.route_e, 1)


    def draw(self):
        return self.surf
#}}}
