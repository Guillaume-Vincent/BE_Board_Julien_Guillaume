import os
import matplotlib.pyplot as plt
from math import exp
from noise import pnoise1
from time import sleep


from analog_sensors_settings import *

# Get the path to the place to save data in
save_path = os.path.dirname(os.path.realpath(__file__)) + "/" + dataFolder


# Sigmoid functions used to simulate changing data after the fire starts


def sigm(time, t0, rt):
    return 1 / (1 + exp(-(time - (t0 + 5*rt)) / rt))


def fire_data(time, t0, delta, rt):
    return delta * (sigm(time, t0, rt) - sigm(t0, t0, rt))


# Lists that will hold data
TIME = []
T = []
S = []

fireToggled = False
tFire = 0
for t in range(0, simulationTime):
    # Basic noise on sensors
    temperature = (random() - 0.5) * 2 * tempSensorNoise
    smoke = max(0, (random() - 0.5) * 2 * smokeSensorNoise)

    if fireToggled is True:  # Temperature and Smoke levels will be rising
        temperature += fire_data(time=t, t0=tFire, delta=fireTemp - stdTemp,
                                 rt=tempRT) + stdTemp + deltaTemp * pnoise1(x=tempOffset + t / scale, octaves=octaves)
        if t < tFire + 10*smokeRT:
            smoke += fire_data(time=t, t0=tFire,
                               delta=fireSmoke + fireDeltaSmoke * pnoise1(x=smokeOffset + (tFire + 10*smokeRT) / scale,
                                                                          octaves=octaves), rt=smokeRT)
        elif tFire + 10 * smokeRT <= t:
            smoke += 5 + 5 * pnoise1(x=smokeOffset +
                                     t / scale, octaves=octaves)
    else:  # Temperature will stand arround stdTemp and smoke sensor will only see some background noise
        temperature += stdTemp + deltaTemp * \
            pnoise1(x=tempOffset + t / scale, octaves=octaves)
        if t == fireStartAt:  # Fire will trigger at t=fireStartAt
            fireToggled = True
            tFire = t

    if doPlotData is True:
        T.append(temperature)
        S.append(smoke)
        TIME.append(t)

    if doWriteData is True:
        tempFile = open(save_path + tempDataFile, "w")
        tempFile.write(str(int(100 * temperature)))
        tempFile.close()

        smokeFile = open(save_path + smokeDataFile, 'w')
        smokeFile.write(str(int(100 * smoke)))
        smokeFile.close()

        sleep(1)

if doWriteData is True:  # Clear the data files
    tempFile = open(tempDataFile, "w")
    tempFile.write("")
    tempFile.close()

    smokeFile = open(smokeDataFile, 'w')
    smokeFile.write("")
    smokeFile.close()

if doPlotData is True:
    fig, ax1 = plt.subplots()
    ax1.set_xlabel('Time(s)')
    ax1.set_ylabel('Temperature (°C)', color=temperatureColor)
    ax1.plot(TIME, T, color=temperatureColor)
    ax1.tick_params(axis='y', labelcolor=temperatureColor)

    ax2 = ax1.twinx()
    ax2.set_ylabel('Obscuration (%/ft)', color=smokeColor)
    ax2.set(ylim=(0, 15))
    ax2.plot(TIME, S, color=smokeColor)
    ax2.tick_params(axis='y', labelcolor=smokeColor)
    ax1.axvline(tFire, color=fireStartColor)
    ax1.axhline(y=temperatureAlarmThreshold,
                color=temperatureColor, linestyle='--')
    ax2.axhline(y=smokeAlarmThreshhold, color=smokeColor, linestyle='--')

    fig.tight_layout()
    ax1.grid(True)
    ax2.grid(True)
    plt.show()
