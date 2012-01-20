#!/usr/bin/python
# -*- coding: cp1251 -*-
# 

import struct
import sys
import time

from Tkinter import *
import tkFileDialog, tkMessageBox
from Queue import Empty # ��� ������ ����������
from multiprocessing import Queue, Event
from binascii import hexlify

from localconfig import *


class ComboScale(Frame):#{{{
    """ ��������� ������, ���������� �����, �������� � �������� """


    def __createWidgets(self, labeltext, f, t, var):
        self.label = Label(self, text=labeltext, width=10)
        self.label.pack(side=LEFT)

        self.scale = Scale(self, orient=HORIZONTAL, length=800, from_=f, to=t, showvalue=False, variable=var)
        self.scale.pack(side=LEFT)

        self.spinbox = Spinbox(self, from_=f, to=t, textvariable=var, width=4)
        self.spinbox.pack(side=LEFT)


    def __init__(self, parent, labeltext, f, t, var):
        Frame.__init__(self, parent, borderwidth=0)
        self.__createWidgets(labeltext, f, t, var)
        self.pack(side=TOP)
#}}}
class ServoFrame(Frame):#{{{
    """ ��� ��������, ����������� ��� ��������� ����� ����� """

    servovals = None # ������ ��� �������� ���������� � ����� ����������

    def __scaleframe_cb(self, *fakeargs):
        """ ������ �� ����������� ��������
        ���� �������� �� ������� - ������ ���� ���� �� �������

        """
        min_     = int(self.minval.get())
        max_     = int(self.maxval.get())
        neutral_ = int(self.neutral.get())
        # ���������� �� ��������� � �������� ������� �������
        #neutral_ = min_ + ((max_ - min_) * neutral_) / 100
        if ((max_ - min_) < 100) or (neutral_ < min_) or (neutral_ > max_):
            self.configure(background="red")
            self.servovals = (0,0,0,False)
        else:
            self.configure(background="SystemButtonFace")
            self.servovals = (min_, max_, neutral_, True)


    def __createWidgets(self, labeltext):
        self.label = Label(self, text=labeltext, font=("Tahoma", 14))
        self.label.pack(side=TOP)
        self.neutralframe = ComboScale(self, "neutral", 2000, 4000, self.neutral)
        self.neutralframe.pack(side=TOP)
        self.minframe = ComboScale(self, "min", 2000, 4000, self.minval)
        self.minframe.pack(side=TOP)
        self.maxframe = ComboScale(self, "max", 2000, 4000, self.maxval)
        self.maxframe.pack(side=TOP)


    def __init__(self, parent, labeltext):
        Frame.__init__(self, parent, borderwidth=1, background="green")

        self.neutral = StringVar()
        self.maxval  = StringVar()
        self.minval  = StringVar()

        self.minval.set(0)
        self.maxval.set(0)
        self.neutral.set(0)

        self.minval.trace( "w", self.__scaleframe_cb)
        self.maxval.trace( "w", self.__scaleframe_cb)
        self.neutral.trace("w", self.__scaleframe_cb)

        self.__createWidgets(labeltext)
        self.pack(side=TOP)


    def set(self, lst):
        """ ���������� �������� �� �������� ��������� """
        self.minval.set(lst[0])
        self.maxval.set(lst[1])
        self.neutral.set(lst[2])
#}}}
class ServoEqualizer(Frame):#{{{
    """ ��������� ��� ���� ���� � ����� ������� """

    """ �������� ��������, ������������� ����������
        ������� ���������� -- min max neutral """
    equalizervals = {"s0" : (0,40000,0,True),
                     "s1" : (0,0,0,False),
                     "s2" : (0,0,0,False),
                     "s3" : (0,40000,0,True),
                     }

    def __createWidgets(self):
        self.s1 = ServoFrame(self, "servo 1")
        self.s1.pack(side=TOP)
        self.s2 = ServoFrame(self, "servo 2")
        self.s2.pack(side=TOP)

    def __init__(self, parent):
        Frame.__init__(self, parent)
        self.__createWidgets()
        self.pack()

    def set(self, lst):
        """ ���������� �������� �� �������� ��������� """
        self.s1.set(lst[3:6])
        self.s2.set(lst[6:9])

    def get(self):
        self.equalizervals["s1"] = self.s1.servovals
        self.equalizervals["s2"] = self.s2.servovals
        return self.equalizervals
#}}}






packedservovals = None # ��� �������� ��������� ����������� �������� � ���� �������� ������

def ServoTuner(q_up, q_servo):
    """ ������������ �������������

    ���������:
    q_up -- ������� ��� �������� ��������� � ���������
    q_servo -- ������� ��� ������������ �������� ��������� �� ����������

    """

    def about_cb():
        tkMessageBox.showinfo(message='Place you advertising material here.')


    def fileopen_cb():
        f = tkFileDialog.askopenfile(mode='r', defaultextension='srv')
        line = f.read()
        if len(line) == 24:
            applysettings(line)
        else:
            tkMessageBox.showerror(title='Error!', message='File corrupted.')
        f.close()


    def filesave_cb():
        if (packedservovals != None):
            f = tkFileDialog.asksaveasfile(mode='w', defaultextension='srv')
            f.write(packedservovals)
            f.close()
        else:
            tkMessageBox.showerror(title='Error!', message='You can not save, when one, or more values inconsistent.')


    def applysettings(line):
        global packedservovals
        packedservovals = line
        lst = struct.unpack('>12H', line)
        servoequalizer.set(lst)


    def readeeprom():
        """ ������ ������ �������� � ������� � ����������, ���� ����� """
        servoreq_str = SETTINGS_SERVO + READ
        q_up.put(servoreq_str)
        time.sleep(0.2)
        try:
            line = q_servo.get(True, 2)
            applysettings(line)
        except Empty:
            tkMessageBox.showinfo(message='No response. Possible reason -- packet lost.')


    def motion_cb(*arg):
        """ ����������� ������� �������� � ���� �������� ����� � ������ ��� � ������� """

        equalizervals = servoequalizer.get()
        #print equalizervals

        kosher = True
        lst = []
        for key in sorted(equalizervals.iterkeys()):
            kosher &= equalizervals[key][3]
            lst.append(equalizervals[key][0])
            lst.append(equalizervals[key][1])
            lst.append(equalizervals[key][2])

        if kosher:
            line = SETTINGS_SERVO + WRITE
            for i in lst:
                line += struct.pack('>1H',i)
            #print hexlify(line)
            q_up.put(line)
            packedservovals = line
        else:
            packedservovals = None




    root = Tk()
    root.title("Servo tuner")
    root.resizable(FALSE,FALSE)
    root.bind('<Motion>', motion_cb)

    servoequalizer = ServoEqualizer(root)
    servoequalizer.pack()

    menu = Menu(root)
    root.config(menu=menu)

    filemenu = Menu(menu)
    menu.add_cascade(label="File", menu=filemenu)
    filemenu.add_command(label="Open", command=fileopen_cb)
    filemenu.add_command(label="Save", command=filesave_cb)
    filemenu.add_command(label="Exit", command=sys.exit)

    helpmenu = Menu(menu)
    menu.add_cascade(label="Help", menu=helpmenu)
    helpmenu.add_command(label="About", command=about_cb)

    labelframe = LabelFrame(root, text="This is a LabelFrame")
    labelframe.pack(fill="both", expand="yes")
    left = Label(labelframe, text="Inside the LabelFrame")
    left.pack()
    loadbutton = Button(labelframe, text="Read from EEPROM", command=readeeprom)
    loadbutton.pack(side=TOP)


    mainloop()


