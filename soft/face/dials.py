#!/usr/bin/python
# -*- coding: cp1251 -*-
#

import time
import sys
import os
from math import *

import pygame
from pygame.locals import *

# ����������� ������
from localconfig import *
import dsp


def plc(surf, st, color, font, coord, background = None): #{{{
    """ �������� ������� �� ���������� ����������� ���,
    ����� �� ����� �������� � ����������� ������������.
    ����������� -- place label centered

    ���������:
        surf -- ����������� �� ������� ���� ���������
        st -- ����������
        color -- ���� �������
        font -- �����
        coord -- ���������� ������������ ���������� �����������

    """
    if HIQUALITY:
        antialiased = True
        # ������� ������� ���� ���� ������, ����� ����������
        # �� ��� ��������� ������ �������.
        # Font.size �� ����� �������, �.�. ������� ��� ����� ����������
        # (������������) ������
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
    ������� �� �������� ������� ��������� � �������������
    l -- �����
    fi -- ���� � ��������
    center -- ������������� ���������� ������ �������� ������� ������������ �����������
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
        # ������� ���� � ��������� ������� ��� �������������
        self.planepic = pygame.image.load("horizon_plane.png")

        # ������� ��������� ����������� ��� ��� ������
        ribbonsurf = pygame.Surface((2*r, 8*r))
        #������ � ��� ����� ����������
        ribbonsurf.set_colorkey(BLACK)
        #�������� �������� ������
        ribbonsurf.fill(self.groundcolor)

        #������ �������� ������������� ��������� �����
        plist = [(0,2*r), (0,4*r), (2*r,4*r), (2*r,2*r)]
        pygame.draw.polygon(ribbonsurf, self.skycolor, plist, 0)

        #�������� ����� �������
        #������ �����
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

        #������� ����� � ������
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

        # ������� �������� ��������� ��������, ��� ����� ������������
        # ����������� �����
        # �����
        s = ribbonsurf.subsurface(0, 4*r, 2*r, 2*r) # �����
        ribbonsurf.fill(BLACK, (0, 0, 2*r, 2*r))
        ribbonsurf.blit(s.copy(), (0,0))

        # � ����
        s = ribbonsurf.subsurface(0, 2*r, 2*r, 2*r) # ����
        ribbonsurf.fill(BLACK, (0, 6*r, 2*r, 2*r))
        ribbonsurf.blit(s.copy(), (0, 6*r))

        # �������������� �����
        pygame.draw.line(ribbonsurf, self.markscolor, (0,4*r), (2*r,4*r), 1)

        #��������� ����� ��� ����������� �������� �������
        masksurf = pygame.Surface((2*r, 2*r))
        masksurf.set_colorkey(WHITE)
        masksurf.fill(BLACK)
        pygame.draw.circle(masksurf, (WHITE), (r,r), r, 0)

        self.ribbonsurf = ribbonsurf
        self.masksurf = masksurf
        self.r = r


    def get(self, roll, pitch):
        r = self.r

        # ������� ����� "�����" ��������������� ���� �������
        a = 2*r * degrees(pitch) / 180.0
        #print a,r, self.ribbonsurf.get_rect()
        s = self.ribbonsurf.subsurface(0, 3*r + a, 2*r, 2*r)
        dialsurf = s.copy()
        #dialsurf = self.ribbonsurf.copy()
        #pygame.draw.line(dialsurf, RED, (0, 3*r+a), (2*r, 3*r+a), 2)

        # ����������� ����������� ��������
        w = self.planepic.get_width()
        scale = (2*r / float(w)) * 0.9
        planesurf = pygame.transform.rotozoom(self.planepic, -roll * (180/pi), scale)
        planerect = planesurf.get_rect()
        x = r - planerect.center[0]
        y = r - planerect.center[1]
        dialsurf.blit(planesurf, (x,y))
        # ����������� �������� �����
        dialsurf.blit(self.masksurf, (0,0))
        #�������� �� ���� ����������� ������
        pygame.draw.circle(dialsurf, WHITE, (r,r), r, 2)

        # ����� �����
        i = -6
        fi_0 = 3*pi/2
        while i <= 6:
            fi = fi_0 + i*pi/12
            b = pol2ort(0.9 * r, fi, (r,r))
            e = pol2ort(r, fi, (r,r))
            if i != 0:
                pygame.draw.line(dialsurf, self.markscolor, b, e, 2)
            i += 1
        #����� �����
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
        """ ���������
        -- ������ ����� ��������
        -- ������ ������ (�� ������ ���� �� ���� ������, ��� �����)
        -- ���"""

        self.vallist = vallist
        self.step = step

        def gencolorarray(color, l, step):
            """ ��������������� �������
            ��������� ����, �����, ���
            ���������� ������ """
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

        self.cl = cl # �������� � ���������� ���������� ������


    def get(self, currentvalue):
        """ ������� ���������� ���� ����������. ���� ��������
        ������� �� ������� (�� �����, � ����� �������) -- ����������
        ������� ����"""

        i = int(round(((currentvalue - self.vallist[0]) / self.step), 0))
        if i < 0:
            return RED
        try:
            return self.cl[i]
        except IndexError:
            return RED
#}}}
class Compass: #{{{
    """ ����� ��� ��������� �������� """

    def __init__(self, radius, simbolsize):
        """
        ���������:
            radius -- ������ ������
            simbolsize -- ������, ������������ ������ �������
        """
        self.radius = radius
        self.simbolsize = simbolsize

        # ��������� ���������� ����������� ��� ������
        dialsurf = pygame.Surface((2 * radius, 2 * radius))
        # ������ � ��� ����� ����������
        dialsurf.set_colorkey(BLACK)
        # ����
        self.center = (radius, radius)
        self.dialsurf = dialsurf


    def __coursedetector(self, surf, course, dest, center):
        """ �������������� 
        ���������:
            surf -- �����������, �� ������� ���� ����������
            dest -- ����������� ���������
            center-- ����� �������� ���������
            """
        lr = self.radius - 22.0
        # ������� � ����� �������
        fi = course + 0.5 * pi - dest
        # �������
        endcoord = pol2ort(0.8 * lr, fi, center)
        pygame.draw.line(surf, WHITE, center, endcoord,  3)
        # ��������� �����
        endcoord = pol2ort(0.6 * lr, fi - pi, center)
        pygame.draw.line(surf, WHITE, center, endcoord,  3)
        # ��������� ��������
        tail = pol2ort(0.2 * lr, fi - 1.2*pi, endcoord)
        pygame.draw.line(surf, WHITE, endcoord, tail,  3)
        tail = pol2ort(0.2 * lr, fi - 0.8*pi, endcoord)
        pygame.draw.line(surf, WHITE, endcoord, tail,  3)
        # �����
        endcoord = pol2ort(0.6 * lr, fi - 1.3*pi, center)
        pygame.draw.line(surf, WHITE, center, endcoord,  3)
        endcoord = pol2ort(0.6 * lr, fi - 0.7*pi, center)
        pygame.draw.line(surf, WHITE, center, endcoord,  3)


    def get(self, course, destination):
        """
        ������ ���� ������� �������� �������� ����������

        ���������:
            course -- ������� ����
            destination -- ����������� ��������������
        ����������:
            ����������� � ��������
        """
        self.dialsurf.fill(BLACK)
        pygame.draw.circle(self.dialsurf, WHITE, self.center, self.radius, 2)

        course_d = course
        course = 2 * pi * float(course) / 360
        dest_d = destination
        dest = 2 * pi * float(destination) / 360

        # �����
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

        # ��������������
        self.__coursedetector(self.dialsurf, course, dest, self.center)

        # ������� ��� �������������� �����
        xy = (0, 1.9 * self.radius)
        self.dialsurf.blit(smallFont.render(str(dest_d) + "�", 0, WHITE), xy)

        # �����
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

        #������� ����� �����������, �� ������� �������� ����������� �����, � ����� �����
        indicator_h = 30
        compass_surf = pygame.Surface((2 * self.radius, 2 * self.radius + indicator_h))
        compass_surf.set_colorkey(BLACK)
        compass_surf.fill(BLACK)

        # ����������� ����� 
        pointlist = [(r-10,indicator_h-10), (r+10,indicator_h-10), (r, indicator_h)]
        pygame.draw.polygon(compass_surf, RED, pointlist, 0)
        # ������� � ���������
        xy = (r, 11)
        st = str(round(course_d, 1)) + "�"
        compass_surf.blit(mediumFont.render(st, HIQUALITY, (GREEN)), (r-25,0))
        # ������������� ����� � ���������������
        compass_surf.blit(self.dialsurf, (0, 0 + indicator_h))

        return compass_surf
#}}}
class Scale:#{{{
    """ �������� ����� � ��������� ����������� """
    _scale_surf = None
    _grid_surf = None
    _grid_height = 0
    _indicator_surf = None
    _mirror = None
    _pixel_val = 0.0
    _zero_h = 0 # ������������ ���������� ������ �����

    # ������ �������� ����
    _label_width = 0
    #������ �����
    _marks_width = 0


    def __init__(self, height, step_count, color, font, mirror, b, e, colorist):
        """
        height -- ������ �������. WARNING - ��������������
            ������ ����� ����� ������ �� ���� ����
        step_count -- ���������� �������
        color -- ���� ����� � ����
        font -- �����, ������� ���� ������� �������
        mirror -- ���� �� ����������� ����� �� �����������
        b -- ��������� �������� �����
        colorist -- ������ ���������� ���� ����������
        """
        self._mirror = mirror
        # ��� ������ �������
        self._grid_height = height
        self._pixel_val = float(height) / (e - b)

        # ����� ����� ������� ������ ������ 4 ��������
        self._grid_surf = self.__scalegrid(height, step_count, color, font, mirror, b, e)

        rect = self._grid_surf.get_rect()
        # ������������ ���������� ������ �����
        self._zero_h = float(e) * height / (e - b) + (rect.height - height) / 2

        self._scale_surf = pygame.Surface((150, rect.height))

        self._scale_surf.set_colorkey(BLACK)
        self._scale_surf.fill((BLACK))

        self.colorist = colorist

    def __scalegrid(self, height, step_count, color, font, mirror, b, e):
        """
        ������� ��������� ������������ ������������ ����

        ���������:
            height -- ������ � ������ �������. WARNING - ��������������
                ������ ����� ����� ������ �� ���� ����
            step_count -- ���������� �������
            color -- ���� ����� � ����
            font -- �����, ������� ���� ������� �������
            mirror -- ���� �� ����������� ����� �� �����������
            b -- ��������� �������� �����
            e -- �������� �������� �����
        ����������:
            �����������
        """
        # ���� �������
        if (e - b) % step_count == 0:# ������� �� ����
            div_val = (e - b) / step_count
        else:
            div_val = (e - b) / float(step_count)
            div_val = round(div_val,1)

        # ���������� �������� �� ���� �������
        pixel_step = height / float(step_count)

        # ���������� ����� ������� � �������
        kern = 5
        # ����� �����
        if len(str(b)) - len(str(e)) > 0:
            label_width = font.size(str(b))[0] + kern
        else:
            label_width = font.size(str(e))[0] + kern

        self._label_width = label_width
        self._marks_width = 20
        marks_width = self._marks_width

        # �������� �����������, ������� � ������ �������, ����� ������ �����
        scale_surf = pygame.Surface((label_width + marks_width, height + 2 * pixel_step))
        #������ � ��� ����� ����������
        scale_surf.set_colorkey(BLACK)
        #�������� �������� ������
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
        ��������� ���������
        surf -- �����������, �� ������� ���� ����������
        coord -- ���������� "������"
        l -- ������ ������������� ���� (����� ���� �������������,
            ����� ��������� ���������� �������������)
        h -- ������ ������������� ���� (���������� ������)
        color -- ����
        st -- ������, ����������� � ������������� ����
        """

        if (l < 0):# ��� ������ �������� � ������������� �������
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
        ���������� ���������:
            val -- ��������, ������� ���� ���������� �� �����
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
    """����� ��������� ������� ���������� ���������"""
    _center = (0,0)# ���������� ������
    _br = 0.0 # ������ ������� �������
    _mr = 0.0 # ������ ������� �������
    _sr = 0.0 # ������ ��������� �������

    # ���������� ��� ��������� �����
    _altbaroground = None
    _altbarocbuf = dsp.RingBuffer(32)

    def __init__(self, r):
        """
        r -- ������ """

        self._center = (r, r)
        self._br = 0.5 * r
        self._mr = 0.6 * r
        self._sr = 0.95 * r

        # ������� ��������� ����������� ��� �����
        self.dial_surf = pygame.Surface((2*r, 2*r))
        #��� �������� ������ �� ���������
        self.dial_surf.fill(BLACK)
        #������ � ��� ����� ����������
        self.dial_surf.set_colorkey(BLACK)

        _center = self._center
        #������� �����, � ����������� �������
        pygame.draw.circle(self.dial_surf, WHITE, _center, r, 2)
        pygame.draw.circle(self.dial_surf, WHITE, _center, 8, 4)
        # ������ �����
        step = 2 * pi / 50
        i = 0
        while i <= 49:
            b = pol2ort(0.93*r, -step * i + pi/2, _center)
            e = pol2ort(r, -step * i + pi/2, _center)
            pygame.draw.aaline(self.dial_surf, WHITE, b, e, 1)
            i += 1
        # �����
        step = 2 * pi / 10.0
        i = 0
        while i <= 9:
            #������� ����� �������� ����
            b = pol2ort(0.9*r, -step * i + pi/2, _center)
            e = pol2ort(r, -step * i + pi/2, _center)
            pygame.draw.line(self.dial_surf, GREEN, b, e, 3)

            st = str(i)
            c = pol2ort(0.75*r, -step * i + pi/2, _center)
            plc(self.dial_surf, st, WHITE, bigFont, c)
            i += 1

        # ��������� � ������� ��������� ������ ������������� �����������
        #self.dial_surf = dial_surf



    def zero_adjust(self):
        """C��������� ����� ���������� �������� � ����"""
        self._altbaroground = None


    def get(self, alt_baro, alt_sonar):
        """������ ������� � ��������
        ���������:
            alt_baro -- ������ �� ��������� � ������
            alt_sonar -- ������ �� ������ � ������
        ����������:
            ����������� � ������������ ��������"""

        # ���������� ���������� ������
        _br = self._br
        _mr = self._mr
        _sr = self._sr
        _center = self._center

        if self._altbaroground == None:
            self._altbaroground = self._altbarocbuf.get_avg()
        self._altbarocbuf.append(alt_baro)

        # �������, �� ������ ������� ����� ���������������
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

        # ��������� � ���� ��������
        hm = h # �������� ������ � ������
        h = h * 2 * pi / 10

        # �������� �� ������ ������� � �����
        alt_surf = pygame.Surface.copy(self.dial_surf)

        # ������� �������
        bx = _center[0] + _br * cos(-h/1000 + pi/2)
        by = _center[1] - _br * sin(-h/1000 + pi/2)
        pygame.draw.line(alt_surf, WHITE, (bx, by), _center,  6)
        # ������� �������
        bx = _center[0] + _mr * cos(-h/100 + pi/2)
        by = _center[1] - _mr * sin(-h/100 + pi/2)
        pygame.draw.line(alt_surf, WHITE, (bx, by), _center,  3)
        # ��������� �������
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
        #��������� �����
        self.rbuf = dsp.RingBuffer(128)
        # ������� �����
        self.variometerscale = Scale(height, step_count, color, font, mirror, b, e, self.colorist)
        #��������� ���������
        self.time_p = time.time()
        time.sleep(0.04)
        self.time_n = time.time()
        #�������� ��������
        self.alt_p = 0
        self.alt_n = 0.1

    def put(self, parent, coord, alt):
        """ ��������� ������� ������ �� ��������� """

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
        """ ��������� ������, �� �������� ����� ��������� """

         # ��� ������������� ������������ ������
        self.v_colorist = Colorist(VVALUELIST, VCOLORLIST, VSTEP) # �������
        self.c_colorist = Colorist(CVALUELIST, CCOLORLIST, CSTEP) # ���
        self.f_colorist = Colorist(FVALUELIST, FCOLORLIST, FSTEP) # ������� � ����

        self.capcitance = config.getfloat('Power', 'capacitance') # ������� ���������

        self.crbuf = dsp.RingBuffer(4) # ��� ����������� ����
        self.vrbuf = dsp.RingBuffer(4) # ��� ����������� �������
        self.trbuf = dsp.RingBuffer(64) # ��� ����������� ����������� ������� � �������

        self.font = mediumFont
        #��������� ���������
        self.time_p = time.time()
        time.sleep(0.04)
        self.time_n = time.time()
        # ���� ������������ ��� ��� ������ ��������, ����� ������ ���������
        # ����� ������������
        self.time_good = False
        #������� ����������
        self.energy = 0.0

        self.surf = pygame.Surface((screenH / 4, 100))
        self.surf.set_colorkey(BLACK)


    def put(self, parent, coord, voltage, current, pns_time):
        rect = None # ������������� ����������

        self.crbuf.append(current)
        self.vrbuf.append(voltage)

        self.time_p = self.time_n
        self.time_n = pns_time
        if self.time_good == False:
            self.time_good = True
            return self.surf.get_rect()


        # �������� ����������
        v_color = self.v_colorist.get(self.vrbuf.get_avg()) # ��������������� ����
        st = "voltage = " + str(round(self.vrbuf.get_avg(), 1)) + " V"
        c = (coord[0], coord[1] + 0)
        rect = parent.blit(self.font.render(st, HIQUALITY, (v_color), BLACK), c)

        # ������������ ���
        c_color = self.c_colorist.get(self.crbuf.get_avg())
        st = "current = " + str(round(self.crbuf.get_avg(), 1)) + " A"
        c = (coord[0], coord[1] + 20)
        rect = rect.union(parent.blit(self.font.render(st, HIQUALITY, (c_color), BLACK), c))

        # ������������ ��������
        st = "power   = " + str(round(self.crbuf.get_avg() * self.vrbuf.get_avg(), 1)) + " W"
        c = (coord[0], coord[1] + 40)
        rect = rect.union(parent.blit(self.font.render(st, HIQUALITY, (GREEN), BLACK), c))

        # ������������ ������� � ������ ������
        f_color = self.f_colorist.get(self.energy)
        self.energy += (self.time_n - self.time_p) * current / 3600.0
        st = "fuel    = " + str(round(self.energy, 2)) + " Ah"
        c = (coord[0], coord[1] + 60)
        rect = rect.union(parent.blit(self.font.render(st, HIQUALITY, (f_color), BLACK), c))

        ahspeed = current / 3600.0 # �������� ����������� ���������� � �������
        self.trbuf.append(ahspeed)
        try:
            t = int((self.capcitance - self.energy) / self.trbuf.get_avg()) # ���������� ����� � ��������
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
    """ ����� ��������� ��������� �� ������ ������ Scale """
    def __init__(self, height, step_count, color, font, mirror, b, e):
        self.colorist = Colorist(ASVALUELIST, ASCOLORLIST, ASSTEP)
        self.speedometerscale = Scale(height, step_count, color, font, mirror, b, e, self.colorist)

    def put(self, parent, coord, speed):
        """ ���������:
            speed -- ��������
            parent -- ����������� ��� ���������
            coord -- ����������
        ���������� �������������
        """
        rect = parent.blit(self.speedometerscale.get(speed), coord)
        scalewidth = 50
        rect.width = rect.width - scalewidth - 20
        rect.left  = rect.left  + scalewidth
        return rect
#}}}




