"""This files contains all the parameters that will be used to simulate the temperature and smoke sensors."""
from random import randint, random

"""Simulation Settings"""
# Amount of time the simulation will run (s) (default : 180)
simulationTime = 180
# Relative path from the python script to the folder to put the environmental data in (default : environment_data)
dataFolder = "../environment_data/"
# Name of the file to write the temperature data in (default : "temp.data")
tempDataFile = "temp.data"
# Name of the file to write the smoke data in (default : "smoke.data")
smokeDataFile = "smoke.data"
# Name of the file to write the battery levels in (default : "battery.data")
battDataFile = "battery.data"
# If True, will show the data in a graph after the end of the simulation (default : False)
doPlotData = True
# If True, will write smoke and temperature data in a file every second (default : True)
doWriteData = True

"""Plot Settings"""
# Color of the temperature plot (default : "tab:red")
temperatureColor = "tab:red"
# Color of the obscuration plot (default : "tab:blue")
smokeColor = "tab:blue"
# Color of the vertical line representing the start of the fire (default : "black")
fireStartColor = "black"
# Temperature threshold above which the alarm will detect a fire (°C) (default : 50)
temperatureAlarmThreshold = 50
# Obscuration threshold above which the alarm will detech a fire (%/ft) (default : 5)
smokeAlarmThreshhold = 5

"""Perlin Noise Settings"""
# Zoom level of the perlin noise (default : 100)
scale = 100
# Level of detail of the perlin noise (default : 4)
octaves = 4

"""Temperature Settings"""
# Standard average temperature (°C) (default : 20)
stdTemp = 20
# Standard temperature variation (°C) (default : 2)
deltaTemp = 2
# Average temperature when there is a fire (°C) (default : 100)
fireTemp = 100
# Temperature variation when there is a fire (°C) (default : N/A)
# fireDeltaTemp = N/A
# Min time for the heat to fully reach the sensor after a fire has started (s) (default : 60)
tempRiseTimeMin = 60
# Maxi time for the heat to fully reach the sensor after a fire has started (s) (default : 120)
tempRiseTimeMax = 120
# Background noise on the temperature sensor (°C) (default : 0.05)
tempSensorNoise = 0.05

"Smoke Settings"
# Standard average obscuration (%/ft) (default : N/A)
# stdSmoke = N/A
# Standard obscuration variation (%/ft) (default : N/A)
# deltaSmoke = N/A
# Average obscuration when there is a fire (%/ft)  (default : 5)
fireSmoke = 5
# Obscuration variation when there is a fire (%/ft) (default : 5)
fireDeltaSmoke = 5
# Min time for the smoke to fully reach the sensors after a fire has started (s) (default : 30)
smokeRiseTimeMin = 30
# Max time for the smoke to fully reach the sensors after a fire has started (s) (default : 45)
smokeRiseTimeMax = 45
# Background noise on the smoke sensor (%/ft) (default : 0.05)
smokeSensorNoise = 0.05

"Fire Settings"
# Time the fire will start at (s) (default : 20)
fireStartAt = 20


"""Standard Random Settings : DO NOT CHANGE"""
smokeOffset = randint(0, 1024) + randint(0, 1024)/1024
tempOffset = randint(0, 1024) + randint(0, 1024)/1024

tempRT = (tempRiseTimeMin + random() *
          (tempRiseTimeMax - tempRiseTimeMin)) / 10
smokeRT = (smokeRiseTimeMin + random() *
           (smokeRiseTimeMax - smokeRiseTimeMin)) / 10
