# Reservoir
Permet d'avoir une alerte si le niveau d'eau dans un réservoir est en dessous de la limite.

## Constantes
 * `RESERVOIR_LIMIT` = 0
 * `RESERVOIR_ENABLE` = 1
 * `RESERVOIR_EEPROM_LEN` = 3

## Méthodes
* [Reservoir()](#reservoiree_addr)
* [getValue()](#getvalue)
* [setValue()](#setvaluevalue)
* [saveValue()](#savevaluetype)
* [run()](#runcurrentvalue)
* [alert()](#alert)
* [enable()](#enablevalue)
* [isEnable()](#isenable)
* [getEEPROM()](#geteeprom)
* [getNextEEPROM()](#getnexteeprom)
* [setEEPROM()](#seteepromaddr)
* [loadAll()](#loadall)
* [saveAll()](#saveall)

-------------

### Reservoir(ee_addr)
Instancie l'objet Reservoir.

Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
ee_addr	      | int  | Non	  | Par défaut égal `0`. Position de début dans l'EEPROM.


-------------

### getValue()
Renvoie le paramètre souhaité sous la forme d'un entier.


-------------

### setValue(value)
Permet de configurer un paramètre.

Parametres | Type  | Requis | Description
---------- | ----- | ------ | -----------
value  	   | int   | Oui	| Niveau limite.


-------------

### saveValue(type)
Sauvegarde le paramètre dans l'EEPROM.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `RESERVOIR_LIMIT` , `RESERVOIR_ENABLE`.


-------------

### run(currentValue)
Lance l'analyse.

Paramètres	 | Type			| Requis | Description
------------ | ------------ | ------ | -----------
currentValue | unsigned int | Oui	  | Niveau actuel.


-------------

### alert()
Renvoie un booléen si l'alerte est déclenché.


-------------

### enable(value)
Active ou désactive le Reservoir.

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
Lis et remplace la configuration depuis l'EEPROM.

-------------

### saveAll()
Sauvegarde la configuration dans l'EEPROM.


-------------
