# FanSpeed
Régulateur de vitesse. Module une broche PWM sur 3 vitesse.
Utilise la température et le taux d'humidité pour réguler la vitesse.
Configuration différente pour le jour et la nuit.

## Constantes
 * `FAN_TEMP_DAY_MIN` = 0
 * `FAN_TEMP_DAY_MAX` = 1
 * `FAN_HUM_DAY_MIN` = 2
 * `FAN_HUM_DAY_MAX` = 3
 * `FAN_TEMP_NIGHT_MIN` = 4
 * `FAN_TEMP_NIGHT_MAX`  = 5
 * `FAN_HUM_NIGHT_MIN` = 6
 * `FAN_HUM_NIGHT_MAX` = 7
 * `FAN_ENABLE` = 8
Valeur que vous pouvez adapter:
 * `FAN_SPEED_1`  = 85
 * `FAN_SPEED_2` = 170
 * `FAN_SPEED_3`  = 255


## Méthodes
* [FanSpeed()](#fanspeedio_pin-ee_addr)
* [getValue()](#getvaluetype)
* [setValue()](#setvaluetype-value)
* [saveValue()](#savevaluetype)
* [run()](#runcurrenttemp-currenthum-lightmode)
* [isWorking()](#isworking)
* [enable()](#enablevalue)
* [isEnable()](#isenable)
* [getEEPROM()](#geteeprom)
* [getNextEEPROM()](#getnexteeprom)
* [setEEPROM()](#seteepromaddr)
* [loadAll()](#loadall)
* [saveAll()](#saveall)

-------------

### FanSpeed(IO_Pin, ee_addr)
Instancie l'objet FanSpeed.

Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
IO_Pin		  | int  | Oui	  | Numéro de la broche PWM utilisé.
ee_addr	      | int  | Non	  | Par défaut égal `0`. Position de début dans l'EEPROM. Occupe 33 octets.


-------------

### getValue(type)
Renvoie le paramètre souhaité sous la forme d'un flottant.

Paramètres | Type  | Requis | Description
---------- | ----- | ------ | -----------
type	   | int   | Oui	| Utiliser les constantes `FAN_TEMP_...` et `FAN_HUM_...`.


-------------

### setValue(type, value)
Permet de configurer un paramètre.

Parametres | Type  | Requis | Description
---------- | ----- | ------ | -----------
type	   | int   | Oui	| Utiliser les constantes `FAN_TEMP_...` et `FAN_HUM_...`.
value  	   | float | Oui	| Nombre de seconde.


-------------

### saveValue(type)
Sauvegarde le paramètre dans l'EEPROM.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `FAN_TEMP_...` et `FAN_HUM_...`.


-------------

### run(currentTemp, currentHum, lightMode)
Lance l'analyse.

Paramètres	 | Type	 | Requis | Description
------------ | ----- | ------ | -----------
currentTemp	 | float | Oui	  | Température actuelle.
currentHum	 | float | Oui	  | Hygrométrie actuelle.
lightMode	 | bool	 | Non	  | Par défaut égal `true`. Jour ou nuit.


-------------

### isWorking()
Renvoie un booléen signifiant l'état de la broche. Si elle est à l'etat HIGH ou LOW.


-------------

### enable(value)
Active ou désactive le FanSpeed.

Parameters	  | Type | Requis | Description
------------- | ---- | ------ | -----------
value		  | bool | Non	  | Par défaut égal `true`. Active `true` ou désactive `false` le timer.


-------------

### isEnable()
Renvoie un booléen si le timer est actif ou non.


-------------

### getEEPROM()
renvoie l'adresse EEPROM


-------------

### getNextEEPROM()
renvoie le prochain octet libre


-------------

### setEEPROM(addr)
modifier l'adresse EEPROM

Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
addr		  | int  | Oui	  | Remplace l'adresse EEPROM.


-------------

### loadAll()
Lis et remplace la configuration depuis l'EEPROM (33 octets).

-------------

### saveAll()
Sauvegarde la configuration dans l'EEPROM (33 octets).


-------------
