#!/usr/bin/python
# -*- coding: cp1251 -*-
# 


from Tkinter import *

import tkFileDialog
import tkMessageBox

def servotuner():
    def callback():
        print "called the callback!"

    def fileopen_cb():
        print "fileopen"
        print tkFileDialog.askopenfilename(title="Open me, honey.")

    def about_cb():
        tkMessageBox.showinfo(message="Place you advertising material here.")


    root = Tk()

    # create a menu
    menu = Menu(root)
    root.config(menu=menu)

    filemenu = Menu(menu)
    menu.add_cascade(label="File", menu=filemenu)
    filemenu.add_command(label="New", command=callback)
    filemenu.add_command(label="Open...", command=fileopen_cb)
    filemenu.add_separator()
    filemenu.add_command(label="Exit", command=callback)

    helpmenu = Menu(menu)
    menu.add_cascade(label="Help", menu=helpmenu)
    helpmenu.add_command(label="About...", command=about_cb)

    s = Scale(root, orient=HORIZONTAL, length=500, from_=1.0, to=10.0, digits=5, resolution=0.001)
    s.set(1.1)
    s.pack(side=TOP)

    servo1 = Scale(root, orient=HORIZONTAL, length=500, from_=2000, to=3000, relief=RIDGE)
    servo1.set(2700)
    servo1.pack(side=BOTTOM)

    mainloop()

