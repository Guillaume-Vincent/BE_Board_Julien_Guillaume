#!/usr/bin/python3

import tkinter
import os

# get the path to this script
dirname = os.path.dirname(os.path.realpath(__file__))

path_arm = dirname + "/../button/arm.button"
path_test = dirname + "/../button/test.button"
path_reset = dirname + "/../button/reset.button"


def toggleFile(path):
    """Toggles the presence of the corresponding file"""
    print(f"toggling {path}")
    if (os.path.isfile(path)):
        os.remove(path)
    else:
        open(path, 'a').close()


win = tkinter.Tk()
button_arm = tkinter.Button(win, text="Arm button",
                            command=lambda: toggleFile(path_arm))
button_test = tkinter.Button(win, text="Test button",
                             command=lambda: toggleFile(path_test))
button_reset = tkinter.Button(win, text="Reset button",
                              command=lambda: toggleFile(path_reset))
button_arm.pack()
button_test.pack()
button_reset.pack()
win.mainloop()
