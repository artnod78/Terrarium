# RetroLcd
Permet de contrôler l'intensité du rétro éclairage (de 0 à 8) et la durée après avoir appuyé sur une touche.

## Constantes
 * `RETRO_TIME` = 0
 * `RETRO_BRIGHT` = 1
 * `RETRO_EEPROM_LEN` = 4

## Méthodes
* [RetroLcd()](#retrolcdio_pin-ee_addr)
* [getValue()](#getvaluetype)
* [setValue()](#setvaluetype-value)
* [saveValue()](#savevaluetype)
* [run()](#runcurrentunixtime-keypress)
* [isWorking()](#isworking)
* [getEEPROM()](#geteeprom)
* [getNextEEPROM()](#getnexteeprom)
* [setEEPROM()](#seteepromaddr)
* [loadAll()](#loadall)
* [saveAll()](#saveall)

-------------

### RetroLcd(IO_Pin, ee_addr)
Instancie l'objet RetroLcd.

Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
IO_Pin		  | int  | Oui	  | Numéro de la broche utilisé.
ee_addr	      | int  | Non	  | Par défaut égal `0`. Position de début dans l'EEPROM.


-------------

### getValue(type)
Renvoie le paramètre souhaité sous la fourme d'un entier.

Parametres | Type  | Requis | Description
---------- | ----- | ------ | -----------
type  	   | int   | Oui	| Utiliser les constantes `RETRO_TIME` , `RETRO_BRIGHT`.


-------------

### setValue(type, value)
Permet de configurer un paramètre.

Parametres | Type  | Requis | Description
---------- | ----- | ------ | -----------
type  	   | int   | Oui	| Utiliser les constantes `RETRO_TIME` , `RETRO_BRIGHT`.
value  	   | int   | Oui	| Nouvelle valeur.


-------------

### saveValue(type)
Sauvegarde le paramètre dans l'EEPROM.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `RETRO_TIME` , `RETRO_BRIGHT`.


-------------

### run(currentUnixTime, keyPress)
Lance l'analyse.

Paramètres	 	| Type		    | Requis | Description
--------------- | ------------- | ------ | -----------
currentUnixTime | unsigned long | Oui	 | Heure actuel.
keyPress		| bool			| Oui	 | Si une touche a été appuyée.


-------------

### isWorking()
Renvoie un booléen de l'état du rétro éclairage est allumé ou non.


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
