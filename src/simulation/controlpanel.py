#!/usr/bin/python3

import tkinter
import os

# get the path to this script
dirname = os.path.dirname(os.path.realpath(__file__))

path_arm = dirname + "/../button/arm.button"
path_test = dirname + "/../button/test.button"
path_reset = dirname + "/../button/reset.button"
path_batteries = dirname + "/../environment_data/battery.data"

# get default state
def_arm = "Armer l'alarme"
def_test = "Appuyer sur le bouton de test"
def_reset = "Appuyer sur le bouton de reset"

if (os.path.isfile(path_arm)):
    def_arm = "Désarmer l'alarme"
if (os.path.isfile(path_test)):
    def_test = "Relâcher le bouton de test"
if (os.path.isfile(path_reset)):
    def_reset = "Relâcher le bouton de reset"


def toggle_arm():
    """Toggles the presence of the corresponding file"""
    path = path_arm
    if (os.path.isfile(path)):
        os.remove(path)
        button_arm.configure(text="Armer l'alarme")
        print("Alarme désarmée")
    else:
        open(path, 'a').close()
        button_arm.configure(text="Désarmer l'alarme")
        print("Alarme armée")


def toggle_test():
    """Toggles the presence of the corresponding file"""
    path = path_test
    if (os.path.isfile(path)):
        os.remove(path)
        button_test.configure(text="Appuyer sur le bouton de test")
        print("Bouton test relâché")

    else:
        open(path, 'a').close()
        button_test.configure(text="Relâcher le bouton de test")
        print("Bouton test enfoncé")


def toggle_reset():
    """Toggles the presence of the corresponding file"""
    path = path_reset
    if (os.path.isfile(path)):
        os.remove(path)
        button_reset.configure(text="Appuyer sur le bouton de reset")
        print("Bouton reset relâché")

    else:
        open(path, 'a').close()
        button_reset.configure(text="Relâcher le bouton de reset")
        print("Bouton reset enfoncé")


def changeBatteries(path):
    """Writes 100 to the specified file"""
    print("Batteries changées")
    open(path, 'w').write("100")


win = tkinter.Tk()
win.title("Alarm control")
button_arm = tkinter.Button(win, text=def_arm,
                            command=toggle_arm)
button_test = tkinter.Button(win, text=def_test,
                             command=toggle_test)
button_reset = tkinter.Button(win, text=def_reset,
                              command=toggle_reset)
button_batteries = tkinter.Button(
    win, text="Changer les piles", command=lambda: changeBatteries(path_batteries))


button_arm.pack()
button_test.pack()
button_reset.pack()
button_batteries.pack()
win.mainloop()
