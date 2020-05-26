# Application du C++ au domaine des objets connectés :
## Conception d'une alarme incendie automatique 

### Présentation
Ce projet implémente une alarme incendie.
Les périphériques utilisés sont : 
- 3 boutons : 
    - test : déclenche l'alarme 
    - reset : stoppe l'alarme pour un court moment 
    - arm : permet d'armer et de désarmer le système
- 3 capteurs analogiques : 
    - capteur de température
    - capteur de niveau de fumée
    - capteur de niveau de batterie
- 2 LEDs : 
    - Indicateur de statut de l'alarme : allumée lorsque l'alarme est armée
    - Indicateur de niveau de batterie : allumée lorsque le niveau de batterie est faible

### Utilisation classique
Il y a plusieurs manière de faire fonctionner le système simulé. On peut simplement écrire dans les fichier suivants pour modifier les valeurs environnementales de niveaux de température, de fumée et de batterie : 
- _environment_data/temp.data_
- _environment_data/smoke.data_
- _environment_data/battery.data_

De plus, l'état des boutons est simulé par la présence et l'absence des fichiers suivants : 
- _button/arm.button_
- _button/test.button_
- _button/reset.button_

### Utilisation simplifiée
Cependant, devant la complexité et le caractère rébarbatif des manipulations décrites précédemment, nous avons jugé bon de les automatiser avec deux scripts python : 
- _sensors/analog_sensors.py_ : 
Ce programme simule un incendie du point de vue des capteurs environnementaux du système d'alarme. La configuration est réalisable dans _analog_sensors_settings.py_. Par défault, la simulation dure 5 minutes.

- _controlpanel<span></span>.py_ : Ce programme permet d'avoir une interface graphique permettant de simuler les boutons du systèmes, en créant/supprimant les fichiers .button

