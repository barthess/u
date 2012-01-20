#!/usr/bin/python
# -*- coding: cp1251 -*-
#

import time
import sys
import os
from math import *

import pygame
from pygame.locals import *

# самопальные модули
from localconfig import *
import dsp


def plc(surf, st, color, font, coord, background = None): #{{{
    """ Помещает надпись на переданную поверхность так,
    чтобы ее центр совпадал с переданными координатами.
    Расшифровка -- place label centered

    Принимает:
        surf -- поверхность на которую надо поместить
        st -- содержимое
        color -- цвет надписи
        font -- шрифт
        coord -- координаты относительно переданной поверхности

    """
    if HIQUALITY:
        antialiased = True
        # получим метрики всех букв строки, чтобы определить
        # по ним суммарную высоту надписи.
        # Font.size не очень годится, т.к. считает все буквы одинаковой
        # (максимальной) высоты
        metrics = font.metrics(st)
        minylist = []
        maxylist = []
        for m in metrics:
            minylist.append(m[2])
            maxylist.append(m[3])
        minylist.sort()
        maxylist.sort()

        ascent  = font.get_ascent()
        descent = font.get_descent()
        maxy = maxylist[len(maxylist) - 1]
        miny = minylist[0]
        adjust = ((ascent - maxy) - (miny - descent)) / 2.0
        adjust = int(round(adjust, 0))
    else:
        antialiased = False
        adjust = -1


    if background != None:
        st_surf = font.render(st, antialiased, color, background)
    else:
        st_surf = font.render(st, antialiased, color)
    st_rect = st_surf.get_rect()
    dx = st_rect.center[0]
    dy = st_rect.center[1] + adjust
    surf.blit(st_surf, (coord[0] - dx, coord[1] - dy))
#}}}
def pol2ort(l, fi, center):#{{{
    """
    перевод из полярной системы координат в прямоугольную
    l -- длина
    fi -- угол в РАДИАНАХ
    center -- прямоугольные координаты центра полярной системы относительно поверхности
    """
    x = l * cos(fi) + center[0]
    y = center[1] - l * sin(fi)
    return (x,y)
#}}}


class GyroHorizon:#{{{

    planecolor  = GREEN
    groundcolor = (150,100,0)
    skycolor    = (0,0,100)
    markscolor  = WHITE


    def __init__(self, r):
        # откроем файл с картинкой самолёта для авиагоризонта
        self.planepic = pygame.image.load("horizon_plane.png")

        # сначала заготовим поверхность под наш прибор
        ribbonsurf = pygame.Surface((2*r, 8*r))
        #черный у нас будет прозрачным
        ribbonsurf.set_colorkey(BLACK)
        #заполним земляным цветом
        ribbonsurf.fill(self.groundcolor)

        #поверх нарисуем прямоугольник небесного цвета
        plist = [(0,2*r), (0,4*r), (2*r,4*r), (2*r,2*r)]
        pygame.draw.polygon(ribbonsurf, self.skycolor, plist, 0)

        #нарисуем риски тангажа
        #мелкие риски
        i = 0
        markcnt = 48
        marklen = r / 20.0
        steppix  = 8.0*r / markcnt
        while i < markcnt:
            b = (r - marklen, i * steppix)
            e = (r + marklen, i * steppix)
            if i != 24:
                pygame.draw.line(ribbonsurf, self.markscolor, b, e, 2)
            i += 1

        #большие риски с цифрой
        i = -24
        step = r / 3.0
        marklen = 40
        while i <= 24:
            b = (r - marklen, (i + 12) * step)
            e = (r + marklen, (i + 12) * step)
            if i != 0:
                pygame.draw.line(ribbonsurf, self.markscolor, b, e, 2)
                st = str(30 * abs(i))
                plc(ribbonsurf, st, self.markscolor, mediumFont, (r, (i + 12)*step), BLACK)
            i += 1

        # сделаем имитацию кругового движения, для этого продублируем
        # размеченные куски
        # земли
        s = ribbonsurf.subsurface(0, 4*r, 2*r, 2*r) # земля
        ribbonsurf.fill(BLACK, (0, 0, 2*r, 2*r))
        ribbonsurf.blit(s.copy(), (0,0))

        # и неба
        s = ribbonsurf.subsurface(0, 2*r, 2*r, 2*r) # небо
        ribbonsurf.fill(BLACK, (0, 6*r, 2*r, 2*r))
        ribbonsurf.blit(s.copy(), (0, 6*r))

        # разделительную линию
        pygame.draw.line(ribbonsurf, self.markscolor, (0,4*r), (2*r,4*r), 1)

        #заготовим маску для обкусывания круговой области
        masksurf = pygame.Surface((2*r, 2*r))
        masksurf.set_colorkey(WHITE)
        masksurf.fill(BLACK)
        pygame.draw.circle(masksurf, (WHITE), (r,r), r, 0)

        self.ribbonsurf = ribbonsurf
        self.masksurf = masksurf
        self.r = r


    def get(self, roll, pitch):
        r = self.r

        # откусим кусок "летны" соответствующий углу тангажа
        a = 2*r * degrees(pitch) / 180.0
        #print a,r, self.ribbonsurf.get_rect()
        s = self.ribbonsurf.subsurface(0, 3*r + a, 2*r, 2*r)
        dialsurf = s.copy()
        #dialsurf = self.ribbonsurf.copy()
        #pygame.draw.line(dialsurf, RED, (0, 3*r+a), (2*r, 3*r+a), 2)

        # схематичное изображение самолета
        w = self.planepic.get_width()
        scale = (2*r / float(w)) * 0.9
        planesurf = pygame.transform.rotozoom(self.planepic, -roll * (180/pi), scale)
        planerect = planesurf.get_rect()
        x = r - planerect.center[0]
        y = r - planerect.center[1]
        dialsurf.blit(planesurf, (x,y))
        # накладываем круговую маску
        dialsurf.blit(self.masksurf, (0,0))
        #прилепим на круг окаймляющее кольцо
        pygame.draw.circle(dialsurf, WHITE, (r,r), r, 2)

        # риски крена
        i = -6
        fi_0 = 3*pi/2
        while i <= 6:
            fi = fi_0 + i*pi/12
            b = pol2ort(0.9 * r, fi, (r,r))
            e = pol2ort(r, fi, (r,r))
            if i != 0:
                pygame.draw.line(dialsurf, self.markscolor, b, e, 2)
            i += 1
        #цифры крена
        i = -2
        step = pi/6
        fi_0 = 3*pi/2
        while i <= 2:
            fi = fi_0 + i*step
            if i != 0:
                st = str(90 - 30 * abs(i))
                c = pol2ort(0.83 * r, fi, (r,r))
                plc(dialsurf, st, self.markscolor, mediumFont, c)
            i += 1

        return (dialsurf)
#}}}
class Colorist:#{{{
    def __init__(self, vallist, colorlist, step):
        """ принимает
        -- список точек перегиба
        -- список цветов (их должно быть на один меньше, чем точек)
        -- шаг"""

        self.vallist = vallist
        self.step = step

        def gencolorarray(color, l, step):
            """ Вспомогательная функция
            принимает цвет, длину, шаг
            возвращает список """
            i = 0.0
            cl = []
            while i < l:
                cl.append(color)
                i += step
            return cl

        n = 0
        cl = []
        for i in colorlist:
            cl += (gencolorarray(i, vallist[n+1] - vallist[n], step))
            n += 1

        self.cl = cl # сохраним в глобальную переменную класса


    def get(self, currentvalue):
        """ функция возвращает цвет индикатора. Если значение
        вылезло за пределы (не важно, в какую сторону) -- возвращает
        красный цвет"""

        i = int(round(((currentvalue - self.vallist[0]) / self.step), 0))
        if i < 0:
            return RED
        try:
            return self.cl[i]
        except IndexError:
            return RED
#}}}
class Compass: #{{{
    """ Класс для рисования компасов """

    def __init__(self, radius, simbolsize):
        """
        Принимает:
            radius -- радиус пятака
            simbolsize -- строка, обозначающая размер надписи
        """
        self.radius = radius
        self.simbolsize = simbolsize

        # заготовим квадратную поверхность для пятака
        dialsurf = pygame.Surface((2 * radius, 2 * radius))
        # черный у нас будет прозрачным
        dialsurf.set_colorkey(BLACK)
        # круг
        self.center = (radius, radius)
        self.dialsurf = dialsurf


    def __coursedetector(self, surf, course, dest, center):
        """ Курсоуказатель 
        Принимает:
            surf -- поверхность, на которую надо нарисовать
            dest -- направление указателя
            center-- центр вращения указателя
            """
        lr = self.radius - 22.0
        # стрелка в форме самолёта
        fi = course + 0.5 * pi - dest
        # фюзеляж
        endcoord = pol2ort(0.8 * lr, fi, center)
        pygame.draw.line(surf, WHITE, center, endcoord,  3)
        # хвостовая балка
        endcoord = pol2ort(0.6 * lr, fi - pi, center)
        pygame.draw.line(surf, WHITE, center, endcoord,  3)
        # хвостовое оперение
        tail = pol2ort(0.2 * lr, fi - 1.2*pi, endcoord)
        pygame.draw.line(surf, WHITE, endcoord, tail,  3)
        tail = pol2ort(0.2 * lr, fi - 0.8*pi, endcoord)
        pygame.draw.line(surf, WHITE, endcoord, tail,  3)
        # крылы
        endcoord = pol2ort(0.6 * lr, fi - 1.3*pi, center)
        pygame.draw.line(surf, WHITE, center, endcoord,  3)
        endcoord = pol2ort(0.6 * lr, fi - 0.7*pi, center)
        pygame.draw.line(surf, WHITE, center, endcoord,  3)


    def get(self, course, destination):
        """
        Рисует круг компаса согласно заданным параметрам

        Принимает:
            course -- текущий курс
            destination -- направление курсоуказателя
        Возвращает:
            поверхность с компасом
        """
        self.dialsurf.fill(BLACK)
        pygame.draw.circle(self.dialsurf, WHITE, self.center, self.radius, 2)

        course_d = course
        course = 2 * pi * float(course) / 360
        dest_d = destination
        dest = 2 * pi * float(destination) / 360

        # буквы
        if self.simbolsize == "big":
            lr = self.radius - 22.0 # letters r
            font = bigFont
        else:
            lr = self.radius - 12.0 # letters r
            font = mediumFont
        c = pol2ort(lr, course + 0.5 * pi, self.center)
        plc(self.dialsurf, "N", RED, font, c)
        c = pol2ort(lr, course + 0, self.center)
        plc(self.dialsurf, "E", WHITE, font, c)
        c = pol2ort(lr, course - 0.5 * pi, self.center)
        plc(self.dialsurf, "S", WHITE, font, c)
        c = pol2ort(lr, course - pi, self.center)
        plc(self.dialsurf, "W", WHITE, font, c)

        # курсоуказатель
        self.__coursedetector(self.dialsurf, course, dest, self.center)

        # надпись для установленного курса
        xy = (0, 1.9 * self.radius)
        self.dialsurf.blit(smallFont.render(str(dest_d) + "°", 0, WHITE), xy)

        # риски
        mr = self.radius - 9.0 # marks r
        r  = self.radius
        i = 0
        while (i < 360):
            if (i != 90 and i != 180 and i != 270 and i != 0):
                c = 2 * pi * float(i) / 360 + course
                b_x = self.center[0] + mr * cos(c - 0.5 * pi)
                b_y = self.center[1] - mr * sin(c - 0.5 * pi)
                e_x = self.center[0] + r  * cos(c - 0.5 * pi)
                e_y = self.center[1] - r  * sin(c - 0.5 * pi)
                pygame.draw.line(self.dialsurf, WHITE, (b_x, b_y), (e_x, e_y),  2)
            i += 15

        #сделаем новую поверхность, на которую прилепим треугольник курса, а потом пятак
        indicator_h = 30
        compass_surf = pygame.Surface((2 * self.radius, 2 * self.radius + indicator_h))
        compass_surf.set_colorkey(BLACK)
        compass_surf.fill(BLACK)

        # треугольник курса 
        pointlist = [(r-10,indicator_h-10), (r+10,indicator_h-10), (r, indicator_h)]
        pygame.draw.polygon(compass_surf, RED, pointlist, 0)
        # надпись с градусами
        xy = (r, 11)
        st = str(round(course_d, 1)) + "°"
        compass_surf.blit(mediumFont.render(st, HIQUALITY, (GREEN)), (r-25,0))
        # отрендеренный пятак с курсоуказателем
        compass_surf.blit(self.dialsurf, (0, 0 + indicator_h))

        return compass_surf
#}}}
class Scale:#{{{
    """ Линейная шкала с плавающим индикатором """
    _scale_surf = None
    _grid_surf = None
    _grid_height = 0
    _indicator_surf = None
    _mirror = None
    _pixel_val = 0.0
    _zero_h = 0 # вертикальные координаты начала шкалы

    # ширина столбика цифр
    _label_width = 0
    #ширина рисок
    _marks_width = 0


    def __init__(self, height, step_count, color, font, mirror, b, e, colorist):
        """
        height -- высота линейки. WARNING - результирующая
            высота шкалы будет больше за счет букв
        step_count -- количество делений
        color -- цвет рисок и букв
        font -- шрифт, которым надо сделать надписи
        mirror -- надо ли отзеркалить шкалу по горизонтали
        b -- начальное значение шкалы
        colorist -- объект выбирающий цвет индикатора
        """
        self._mirror = mirror
        # вес одного пикселя
        self._grid_height = height
        self._pixel_val = float(height) / (e - b)

        # длину рисок сделаем равной ширине 4 символов
        self._grid_surf = self.__scalegrid(height, step_count, color, font, mirror, b, e)

        rect = self._grid_surf.get_rect()
        # вертикальные координаты начала шкалы
        self._zero_h = float(e) * height / (e - b) + (rect.height - height) / 2

        self._scale_surf = pygame.Surface((150, rect.height))

        self._scale_surf.set_colorkey(BLACK)
        self._scale_surf.fill((BLACK))

        self.colorist = colorist

    def __scalegrid(self, height, step_count, color, font, mirror, b, e):
        """
        Функция рисования вертикальных нумерованных шкал

        Принимает:
            height -- ширина и высота линейки. WARNING - результирующая
                высота шкалы будет больше за счет букв
            step_count -- количество делений
            color -- цвет рисок и букв
            font -- шрифт, которым надо сделать надписи
            mirror -- надо ли отзеркалить шкалу по горизонтали
            b -- начальное значение шкалы
            e -- конечное значение шкалы
        Возвращает:
            поверхность
        """
        # цена деления
        if (e - b) % step_count == 0:# делится на цело
            div_val = (e - b) / step_count
        else:
            div_val = (e - b) / float(step_count)
            div_val = round(div_val,1)

        # количество пикселей на одно деление
        pixel_step = height / float(step_count)

        # расстояние между рисками и буквами
        kern = 5
        # длина рисок
        if len(str(b)) - len(str(e)) > 0:
            label_width = font.size(str(b))[0] + kern
        else:
            label_width = font.size(str(e))[0] + kern

        self._label_width = label_width
        self._marks_width = 20
        marks_width = self._marks_width

        # сгенерим поверхность, добавим к высоте немного, чтобы влезли буквы
        scale_surf = pygame.Surface((label_width + marks_width, height + 2 * pixel_step))
        #черный у нас будет прозрачным
        scale_surf.set_colorkey(BLACK)
        #заполним земляным цветом
        scale_surf.fill(BLACK)

        r = scale_surf.get_rect()
        if mirror == True:
            i = 0
            while i <= step_count:
                y = height - (i * pixel_step) + pixel_step
                b_ = (r.width - label_width - marks_width, y)
                e_ = (r.width - label_width, y)
                pygame.draw.line(scale_surf, color, b_, e_, 2)

                st = str(b + i * div_val)
                xy = (r.width - label_width / 2, y)
                plc(scale_surf, st, color, font, xy, background = None)
                i += 1
        else:
            i = 0
            while i <= step_count:
                y = height - (i * pixel_step) + pixel_step
                b_ = (label_width, y)
                e_ = (label_width + marks_width, y)
                pygame.draw.line(scale_surf, color, b_, e_, 2)

                st = str(b + i * div_val)
                xy = (label_width / 2, y)
                plc(scale_surf, st, color, font, xy, background = None)
                i += 1
        return scale_surf


    def __floater(self, surf, coord, l, h, color, st):
        """
        подвижный индикатор
        surf -- поверхность, на которой надо нарисовать
        coord -- координаты "носика"
        l -- ширину прямоугольной зоны (может быть отрицательной,
            тогда индикатор отзеркален горизонтально)
        h -- высоту прямоугольной зоны (желательно четную)
        color -- цвет
        st -- строку, отображаему в прямоугольной зоне
        """

        if (l < 0):# для отлова ситуации с отрицательной длинной
            n = -1
            text_coord = (coord[0] - 6 + l, coord[1] - 10)
        else:
            n = 1
            text_coord = (coord[0] + 0.5*h, coord[1] - 10)

        b = (coord[0],coord[1])
        e = (coord[0]+0.5*h*n, coord[1]-0.5*h)
        pygame.draw.line(surf, color, b, e,  2)
        b = e
        e = (e[0] + l, e[1])
        pygame.draw.line(surf, color, b, e,  2)
        b = e
        e = (e[0], e[1] + h)
        pygame.draw.line(surf, color, b, e,  2)
        b = e
        e = (e[0] - l, e[1])
        pygame.draw.line(surf, color, b, e,  2)
        b = e
        e = (coord[0],coord[1])
        pygame.draw.line(surf, color, b, e,  2)

        surf.blit(mediumFont.render(st, HIQUALITY, (color)), text_coord)

        width = l + h/2
        height = h
        return (width, height)


    def get(self, val):
        """
        Принимаемы параметры:
            val -- значение, которое надо отобразить на шкале
        """
        self._scale_surf.fill((BLACK))

        mirror = self._mirror
        grid_surf = self._grid_surf
        scale_surf = self._scale_surf

        label_width = self._label_width
        marks_width = self._marks_width


        if mirror:
            x = scale_surf.get_width() - grid_surf.get_width()
            scale_surf.blit(self._grid_surf, (x,0))
        else:
            scale_surf.blit(self._grid_surf, (0,0))

        l = 50
        h = 30
        r = scale_surf.get_rect()
        if mirror:
            l = -l
            xy = ((r.width - label_width - marks_width - 3),(self._zero_h - val * self._pixel_val))
        else:
            xy = ((label_width + marks_width + 2),(self._zero_h - val * self._pixel_val))

        color = self.colorist.get(val)
        self.__floater(scale_surf, xy, l, h, color, str(round(val,1)))
        return scale_surf



#}}}
class Altimeter:#{{{
    """Класс реализует круглый стрелочный альтиметр"""
    _center = (0,0)# координаты центра
    _br = 0.0 # длинна большой стрелки
    _mr = 0.0 # длинна средней стрелки
    _sr = 0.0 # длинна маленькой стрелки

    # переменные для установки нулей
    _altbaroground = None
    _altbarocbuf = dsp.RingBuffer(32)

    def __init__(self, r):
        """
        r -- радиус """

        self._center = (r, r)
        self._br = 0.5 * r
        self._mr = 0.6 * r
        self._sr = 0.95 * r

        # сначала заготовим поверхность под пятак
        self.dial_surf = pygame.Surface((2*r, 2*r))
        #под конечный прибор со стрелками
        self.dial_surf.fill(BLACK)
        #черный у нас будет прозрачным
        self.dial_surf.set_colorkey(BLACK)

        _center = self._center
        #Главный пятак, и центральный гвоздик
        pygame.draw.circle(self.dial_surf, WHITE, _center, r, 2)
        pygame.draw.circle(self.dial_surf, WHITE, _center, 8, 4)
        # мелкие риски
        step = 2 * pi / 50
        i = 0
        while i <= 49:
            b = pol2ort(0.93*r, -step * i + pi/2, _center)
            e = pol2ort(r, -step * i + pi/2, _center)
            pygame.draw.aaline(self.dial_surf, WHITE, b, e, 1)
            i += 1
        # цифры
        step = 2 * pi / 10.0
        i = 0
        while i <= 9:
            #крупные риски напротив цифр
            b = pol2ort(0.9*r, -step * i + pi/2, _center)
            e = pol2ort(r, -step * i + pi/2, _center)
            pygame.draw.line(self.dial_surf, GREEN, b, e, 3)

            st = str(i)
            c = pol2ort(0.75*r, -step * i + pi/2, _center)
            plc(self.dial_surf, st, WHITE, bigFont, c)
            i += 1

        # скопируем в область видимости класса отрендеренную поверхность
        #self.dial_surf = dial_surf



    def zero_adjust(self):
        """Cбрасывает ранее полученные значения в нули"""
        self._altbaroground = None


    def get(self, alt_baro, alt_sonar):
        """Рисует стрелки и цикверки
        Принимает:
            alt_baro -- высота по барометру в метрах
            alt_sonar -- высота по сонару в метрах
        Возвращает:
            поверхность с нарисованным прибором"""

        # Глобальные переменные класса
        _br = self._br
        _mr = self._mr
        _sr = self._sr
        _center = self._center

        if self._altbaroground == None:
            self._altbaroground = self._altbarocbuf.get_avg()
        self._altbarocbuf.append(alt_baro)

        # выберем, по какому прибору будем ориентироваться
        if (alt_sonar > 6) or (alt_baro - self._altbaroground - alt_sonar) > 1.5:
            h = (alt_baro - self._altbaroground)
            letter = "B"
        else:
            h = alt_sonar
            letter = "S"
        if h > 6:
            color = GREEN
        else:
            color = RED

        # переведем в угол поворота
        hm = h # сохраним высоту в метрах
        h = h * 2 * pi / 10

        # нарисуем на пятаке стрелки и цифры
        alt_surf = pygame.Surface.copy(self.dial_surf)

        # большая стрелка
        bx = _center[0] + _br * cos(-h/1000 + pi/2)
        by = _center[1] - _br * sin(-h/1000 + pi/2)
        pygame.draw.line(alt_surf, WHITE, (bx, by), _center,  6)
        # средняя стрелка
        bx = _center[0] + _mr * cos(-h/100 + pi/2)
        by = _center[1] - _mr * sin(-h/100 + pi/2)
        pygame.draw.line(alt_surf, WHITE, (bx, by), _center,  3)
        # маленькая стрелка
        bx = _center[0] + _sr * cos(-h/10 + pi/2)
        by = _center[1] - _sr * sin(-h/10 + pi/2)
        pygame.draw.aaline(alt_surf, color, (bx, by), _center,  1)

        st = str(round((hm),2))
        xy = (_center[0] - 0.4 * _br, _center[1] + 0.4 * _br)
        alt_surf.blit(mediumFont.render(st, HIQUALITY, color, (0,0,0,0)), xy)

        st = str(round((alt_baro - self._altbaroground),1))
        xy = (0, _center[1] * 1.9)
        alt_surf.blit(smallFont.render("b: " + st, HIQUALITY, WHITE), xy)

        st = str(round(alt_sonar,1))
        xy = (_center[1] * 1.4, _center[1] * 1.9)
        alt_surf.blit(smallFont.render("s: " + st, HIQUALITY, WHITE), xy)
        xy = (_center[1] * 1.7, _center[1] * 1.7)
        alt_surf.blit(mediumFont.render(letter, HIQUALITY, WHITE), xy)

        return alt_surf
#}}}
class Variometer: #{{{
    def __init__(self, height, step_count, color, font, mirror, b, e):
        self.colorist = Colorist(VARIOVALUELIST, VARIOCOLORLIST, VARIOSTEP)
        #кольцевой буфер
        self.rbuf = dsp.RingBuffer(128)
        # объекта шкала
        self.variometerscale = Scale(height, step_count, color, font, mirror, b, e, self.colorist)
        #временные интервалы
        self.time_p = time.time()
        time.sleep(0.04)
        self.time_n = time.time()
        #значения давления
        self.alt_p = 0
        self.alt_n = 0.1

    def put(self, parent, coord, alt):
        """ Принимает текущую высоту по барометру """

        dt = self.time_n - self.time_p
        self.time_p = self.time_n
        self.time_n = time.time()

        da = self.alt_n - self.alt_p
        self.alt_p = self.alt_n
        self.alt_n = alt

        if dt == 0:
            dt = 0.01
        self.rbuf.append(da/dt)

        rect = parent.blit(self.variometerscale.get(self.rbuf.get_avg()), coord)
        rect.width = rect.width - 50
        return rect
    #}}}
class Powermeter: #{{{
    def __init__(self, config):
        """ Принимает конфиг, из которого берет константы """

         # для динамического переключения цветов
        self.v_colorist = Colorist(VVALUELIST, VCOLORLIST, VSTEP) # напряга
        self.c_colorist = Colorist(CVALUELIST, CCOLORLIST, CSTEP) # ток
        self.f_colorist = Colorist(FVALUELIST, FCOLORLIST, FSTEP) # солярка в баке

        self.capcitance = config.getfloat('Power', 'capacitance') # емкость батарейки

        self.crbuf = dsp.RingBuffer(4) # для сглаживания тока
        self.vrbuf = dsp.RingBuffer(4) # для сглаживания напряги
        self.trbuf = dsp.RingBuffer(64) # для сглаживания оставшегося времени в воздухе

        self.font = mediumFont
        #временные интервалы
        self.time_p = time.time()
        time.sleep(0.04)
        self.time_n = time.time()
        # флаг предназначен для для отлова ситуации, когда первая временнАя
        # точка недостоверна
        self.time_good = False
        #счетчик амперчасов
        self.energy = 0.0

        self.surf = pygame.Surface((screenH / 4, 100))
        self.surf.set_colorkey(BLACK)


    def put(self, parent, coord, voltage, current, pns_time):
        rect = None # прямоугольник рендеринга

        self.crbuf.append(current)
        self.vrbuf.append(voltage)

        self.time_p = self.time_n
        self.time_n = pns_time
        if self.time_good == False:
            self.time_good = True
            return self.surf.get_rect()


        # бортовое напряжение
        v_color = self.v_colorist.get(self.vrbuf.get_avg()) # символизирующий цвет
        st = "voltage = " + str(round(self.vrbuf.get_avg(), 1)) + " V"
        c = (coord[0], coord[1] + 0)
        rect = parent.blit(self.font.render(st, HIQUALITY, (v_color), BLACK), c)

        # потребляемый ток
        c_color = self.c_colorist.get(self.crbuf.get_avg())
        st = "current = " + str(round(self.crbuf.get_avg(), 1)) + " A"
        c = (coord[0], coord[1] + 20)
        rect = rect.union(parent.blit(self.font.render(st, HIQUALITY, (c_color), BLACK), c))

        # потребляемая мощность
        st = "power   = " + str(round(self.crbuf.get_avg() * self.vrbuf.get_avg(), 1)) + " W"
        c = (coord[0], coord[1] + 40)
        rect = rect.union(parent.blit(self.font.render(st, HIQUALITY, (GREEN), BLACK), c))

        # потребленная энергия с начала работы
        f_color = self.f_colorist.get(self.energy)
        self.energy += (self.time_n - self.time_p) * current / 3600.0
        st = "fuel    = " + str(round(self.energy, 2)) + " Ah"
        c = (coord[0], coord[1] + 60)
        rect = rect.union(parent.blit(self.font.render(st, HIQUALITY, (f_color), BLACK), c))

        ahspeed = current / 3600.0 # скорость потребления амперчасов в секунду
        self.trbuf.append(ahspeed)
        try:
            t = int((self.capcitance - self.energy) / self.trbuf.get_avg()) # оставшееся время в секундах
        except ZeroDivisionError:
            t = 0
        if t < 0 :
            t = 0
        st = "countdown = " + str(t / 60) + ":" + str(t % 60)
        c = (coord[0], coord[1] + 80)
        rect = rect.union(parent.blit(self.font.render(st, HIQUALITY, (f_color), BLACK), c))

        rect.width = rect.width * 1.2
        return rect
#}}}
class HelpScreen:#{{{
    def __init__(self):
        help_txt = [
                "F1 -- this help",
                "t -- set current system time",
                "s -- tune servos",
                "b -- adjust barometric altimeter",
                "p -- upload/download route points",
                "m -- show map",
                "UpArrow, DownArrow -- set course",
                "",
                "",
                "",
                "",
                "",
                "----------------------------------------",
                "TODO: route point confirmation and verification",
                "TODO: router loader GUI",
                "TODO: space bar to switch manual driving",
                "TODO: time adjusting",
                ]

        helpsurf = pygame.Surface((screenH, screenV))
        helpsurf.fill((BLACK))

        v_pos =  0 #vertical position of 1st string
        h_pos = 10 #horizontal pos. of the 1st string

        for i in help_txt:
            string_surf = mediumFont.render(i, 1, (GREEN))
            v_pos += 1 * string_surf.get_height()
            helpsurf.blit(string_surf, (h_pos, v_pos))
        self.helpsurf = helpsurf

    def put(self, parent, coord):
        rect = parent.blit(self.helpsurf, coord)
        return rect
#}}}
class Speedometer:#{{{
    """ Класс реализует спидометр на основе класса Scale """
    def __init__(self, height, step_count, color, font, mirror, b, e):
        self.colorist = Colorist(ASVALUELIST, ASCOLORLIST, ASSTEP)
        self.speedometerscale = Scale(height, step_count, color, font, mirror, b, e, self.colorist)

    def put(self, parent, coord, speed):
        """ Принимает:
            speed -- скорость
            parent -- поверхность для рисования
            coord -- координаты
        Возвращает прямоугольник
        """
        rect = parent.blit(self.speedometerscale.get(speed), coord)
        scalewidth = 50
        rect.width = rect.width - scalewidth - 20
        rect.left  = rect.left  + scalewidth
        return rect
#}}}




