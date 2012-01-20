#!/usr/bin/python
# -*- coding: cp1251 -*-
#

#временной интервал между точками интегрирования
dt = 0.04



def trapezoidal(f):
    a = 0
    b = dt
    I = (b - a) * (f[0] + f[1]) * 0.5
    return I

def simpson_quadratic(f):
    a = 0
    b = dt * 2
    I = ((b - a) / 6.0) * (f[0] + 4*f[1] + f[2])
    return I

def simpson_cubic(fa, fm1, fm2, fb):
    a = 0
    b = dt * 3
    I = ((b - a) / 8.0) * (fa + 3*fm1 + 3*fm2 + fb)
    return I



class Gyroscope:
    """ Предназначен для обсчета гироскопов """
    points = 16
    i_points = 0
    iterations = 16
    i_iterations = 0

    ZERO_ADJ = False

    def __init__(self):
        # установленные нули
        self.Wx0 = 1850.0
        self.Wy0 = 1850.0
        self.Wz0 = 1850.0
        #начальные интервалы для поиска нулей
        self.Wx0_min = 1800.0
        self.Wx0_max = 1900.0
        self.Wy0_min = 1800.0
        self.Wy0_max = 1900.0
        self.Wz0_min = 1800.0
        self.Wz0_max = 1900.0
        #текущий угол
        self.fi_x = 0.0
        self.fi_y = 0.0
        self.fi_z = 0.0
        #буфера для вычисления интеграла
        self.rbuf_x = RingBuffer(2)
        self.rbuf_y = RingBuffer(2)
        self.rbuf_z = RingBuffer(2)
        # буфера для выставки нулей
        self.adj_rbuf_x = RingBuffer(self.points)
        self.adj_rbuf_y = RingBuffer(self.points)
        self.adj_rbuf_z = RingBuffer(self.points)


    def zero_adj(self, rawx, rawy, rawz):
        """ Высчитывает нули. Когда все итерации сделаны --
        взводит флаг ZERO_ADJ"""
        if self.i_iterations < self.iterations:
            if self.i_points < self.points:
                self.adj_rbuf_x.append(rawx - self.Wx0)
                self.adj_rbuf_y.append(rawy - self.Wy0)
                self.adj_rbuf_z.append(rawz - self.Wz0)

                self.i_points += 1
            else: # насобиралось нужное количество значений
                #print "x", rawx - self.Wx0, "y", rawy - self.Wy0, "z", rawz - self.Wz0

                self.i_iterations += 1
                self.i_points = 0

                if self.adj_rbuf_x.get_avg() > 0:
                    self.Wx0_min = self.Wx0
                    self.Wx0 = self.Wx0 + (self.Wx0_max - self.Wx0) / 2
                else:
                    self.Wx0_max = self.Wx0
                    self.Wx0 = self.Wx0 - (self.Wx0 - self.Wx0_min) / 2

                if self.adj_rbuf_y.get_avg() > 0:
                    self.Wy0_min = self.Wy0
                    self.Wy0 = self.Wy0 + (self.Wy0_max - self.Wy0) / 2
                else:
                    self.Wy0_max = self.Wy0
                    self.Wy0 = self.Wy0 - (self.Wy0 - self.Wy0_min) / 2

                if self.adj_rbuf_z.get_avg() > 0:
                    self.Wz0_min = self.Wz0
                    self.Wz0 = self.Wz0 + (self.Wz0_max - self.Wz0) / 2
                else:
                    self.Wz0_max = self.Wz0
                    self.Wz0 = self.Wz0 - (self.Wz0 - self.Wz0_min) / 2

        else: #self.i_iterations < self.iterations
            self.ZERO_ADJ = True






    def get_angle(self, rawx, rawy, rawz):

        if self.ZERO_ADJ != True:
            self.zero_adj(rawx, rawy, rawz)
            return (0.0, 0.0, 0.0)
        else:
            # запихиваем одну точку в буфер.
            # предыдущая точка сдвигается а начало
            # и у нас снова получается готовый промежуток
            # для метода трапеций
            self.rbuf_x.append(rawx - self.Wx0)
            self.rbuf_y.append(rawy - self.Wy0)
            self.rbuf_z.append(rawz - self.Wz0)

            self.fi_x += trapezoidal(self.rbuf_x.data)
            self.fi_y += trapezoidal(self.rbuf_y.data)
            self.fi_z += trapezoidal(self.rbuf_z.data)


        So = 0.003752 # (V/dps) чувствительность гироскопа
        Vref = 3.3 # (V) опорное напряжение АЦП
        d = 4096 # разрядность АЦП
        Sadc = Vref / d # (V/LSB) чувствительность АЦП
        Sadc = 0.0008056640625 # расчетное 
        #Sadc = 0.0008100513374764 измеренное
        Sadc_o = So / Sadc #(LSB/dps) чувствительность гироскопа "в цифре"
        Sadc_o = 4.6570278787
        Sadc_o = Sadc_o / 20 # почему оно в получилось в 20 раз больше - так и не понял






# кольцевой буфер для нужд трудящихся
class RingBuffer:
    def __init__(self, size):
        self.data = [0.0 for i in xrange(size)]
        self.summ = 0.0

    def append(self, x):
        self.summ += x
        self.summ -= self.data[0]
        self.data.pop(0)
        self.data.append(x)

    def get_summ(self):
        return self.summ

    def get_avg(self):
        return self.summ / len(self.data)
