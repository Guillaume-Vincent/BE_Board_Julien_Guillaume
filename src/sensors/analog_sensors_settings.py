"""This files contains all the parameters that will be used to simulate the temperature and smoke sensors."""
from random import randint, random

"""Simulation Settings"""
simulationTime = 300  # Amount of time the simulation will run (s) (default : 300)
tempDataFile = "temp.data"  # Name of the file to write the temperature data in (default : "temp.data")
smokeDataFile = "smoke.data"  # Name of the file to write the smoke data in (default : "smoke.data")
doPlotData = True  # If True, will show the data in a graph after the end of the simulation (default : False)
doWriteData = True  # If True, will write smoke and temperature data in a file every second (default : True)

"""Plot Settings"""
temperatureColor = "tab:red"  # Color of the temperature plot (default : "tab:red")
smokeColor = "tab:blue"  # Color of the obscuration plot (default : "tab:blue")
fireStartColor = "black"  # Color of the vertical line representing the start of the fire (default : "black")
temperatureAlarmThreshold = 50  # Temperature threshold above which the alarm will detect a fire (°C) (default : 50)
smokeAlarmThreshhold = 5  # Obscuration threshold above which the alarm will detech a fire (%/ft) (default : 5)

"""Perlin Noise Settings"""
scale = 100  # Zoom level of the perlin noise (default : 100)
octaves = 4  # Level of detail of the perlin noise (default : 4)

"""Temperature Settings"""
stdTemp = 20  # Standard average temperature (°C) (default : 20)
deltaTemp = 2  # Standard temperature variation (°C) (default : 2)
fireTemp = 100  # Average temperature when there is a fire (°C) (default : 100)
# fireDeltaTemp = N/A  # Temperature variation when there is a fire (°C) (default : N/A)
tempRiseTimeMin = 60  # Min time for the heat to fully reach the sensor after a fire has started (s) (default : 60)
tempRiseTimeMax = 120  # Maxi time for the heat to fully reach the sensor after a fire has started (s) (default : 120)
tempSensorNoise = 0.05  # Background noise on the temperature sensor (°C) (default : 0.05)

"Smoke Settings"
# stdSmoke = N/A  # Standard average obscuration (%/ft) (default : N/A)
# deltaSmoke = N/A  # Standard obscuration variation (%/ft) (default : N/A)
fireSmoke = 5  # Average obscuration when there is a fire (%/ft)  (default : 5)
fireDeltaSmoke = 5  # Obscuration variation when there is a fire (%/ft) (default : 5)
smokeRiseTimeMin = 30  # Min time for the smoke to fully reach the sensors after a fire has started (s) (default : 30)
smokeRiseTimeMax = 45  # Max time for the smoke to fully reach the sensors after a fire has started (s) (default : 45)
smokeSensorNoise = 0.05  # Background noise on the smoke sensor (%/ft) (default : 0.05)

"Fire Settings"
fireStartAt = 30  # Time the fire will start at (s) (default : 30)


"""Standard Random Settings : DO NOT CHANGE"""
smokeOffset = randint(0, 1024) + randint(0, 1024)/1024
tempOffset = randint(0, 1024) + randint(0, 1024)/1024

tempRT = (tempRiseTimeMin + random() * (tempRiseTimeMax - tempRiseTimeMin)) / 10
smokeRT = (smokeRiseTimeMin + random() * (smokeRiseTimeMax - smokeRiseTimeMin)) / 10