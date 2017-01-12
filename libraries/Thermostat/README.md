# Thermostat
Thermostat. Active ou désactive une broche en dehors de la plage définis.
Peut être utilisé pour température ou de taux d'humidité ou autres.
Configuration différente pour le jour et la nuit.

## Constantes
 * `THERMO_DAY_MIN` = 0
 * `THERMO_DAY_MAX` = 1
 * `THERMO_NIGHT_MIN` = 2
 * `THERMO_NIGHT_MAX` = 3
 * `THERMO_ENABLE` = 4
 * `THERMO_EEPROM_LEN`  = 5

## Méthodes
* [Thermostat()](#thermostatio_pin-ee_addr-invertedrelay)
* [getValue()](#getvaluetype)
* [setValue()](#setvaluetype-value)
* [saveValue()](#savevaluetype)
* [run()](#runcurrentvalue-lightmode)
* [isWorking()](#isworking)
* [enable()](#enablevalue)
* [isEnable()](#isenable)
* [getEEPROM()](#geteeprom)
* [getNextEEPROM()](#getnexteeprom)
* [setEEPROM()](#seteepromaddr)
* [loadAll()](#loadall)
* [saveAll()](#saveall)

-------------

### Thermostat(IO_Pin, ee_addr, invertedRelay)
Instancie l'objet Thermostat.

Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
IO_Pin		  | int  | Oui	  | Numéro de la broche utilisé.
ee_addr	      | int  | Non	  | Par défaut égal `0`. Position de début dans l'EEPROM. Occupe 17 octets.
invertedRelay | bool | Non	  | Par défaut égal `false`. Inverse l'état de la broche utilisé si égal `true`.


-------------

### getValue(type)
Renvoie le paramètre souhaité sous la fourme d'un flottant.

Paramètres | Type  | Requis | Description
---------- | ----- | ------ | -----------
type	   | int   | Oui	| Utiliser les constantes `THERMO_DAY_MIN` , `THERMO_DAY_MAX` , `THERMO_NIGHT_MIN` , `THERMO_NIGHT_MAX`.


-------------

### setValue(type, value)
Permet de configurer un paramètre.

Parametres | Type  | Requis | Description
---------- | ----- | ------ | -----------
type	   | int   | Oui	| Utiliser les constantes `THERMO_DAY_MIN` , `THERMO_DAY_MAX` , `THERMO_NIGHT_MIN` , `THERMO_NIGHT_MAX`.
value  	   | float | Oui	| Nombre de seconde.


-------------

### saveValue(type)
Sauvegarde le paramètre dans l'EEPROM.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `THERMO_DAY_MIN` , `THERMO_DAY_MAX` , `THERMO_NIGHT_MIN` , `THERMO_NIGHT_MAX` , `THERMO_ENABLE`.


-------------

### run(currentValue, lightMode)
Lance l'analyse.

Paramètres	 | Type	 | Requis | Description
------------ | ----- | ------ | -----------
currentValue | float | Oui	  | Numéro de la broche utilisé.
lightMode	 | bool	 | Non	  | Par défaut égal `true`. Jour ou nuit.


-------------

### isWorking()
Renvoie un booléen signifiant l'état de la broche. Si elle est à l'etat HIGH ou LOW.


-------------

### enable(value)
Active ou désactive le timer.

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
Lis et remplace la configuration depuis l'EEPROM (17 octets).

-------------

### saveAll()
Sauvegarde la configuration dans l'EEPROM (17 octets).


-------------
