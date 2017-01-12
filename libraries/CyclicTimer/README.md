# CyclicTimer
Minuterie cyclique. Précision à la seconde.

## Constantes
 * `CYCLIC_DAY_ON` = 0
 * `CYCLIC_DAY_OFF` = 1
 * `CYCLIC_NIGHT_ON` = 2
 * `CYCLIC_NIGHT_OFF` = 3
 * `CYCLIC_ENABLE` = 4
 * `DAILY_EEPROM_LEN`  = 17

## Méthodes
* [CyclicTimer()](#cyclictimerio_pin-ee_addr-invertedrelay)
* [getValue()](#getvaluetype)
* [setValue()](#setvaluetype-sec)
* [saveValue()](#savevaluetype)
* [run()](#runcurrentunixtime-lightmode)
* [isWorking()](#isworking)
* [stop()](#stop)
* [enable()](#enablevalue)
* [isEnable()](#isenable)
* [getEEPROM()](#geteeprom)
* [getNextEEPROM()](#getnexteeprom)
* [setEEPROM()](#seteepromaddr)
* [loadAll()](#loadall)
* [saveAll()](#saveall)

-------------

### CyclicTimer(IO_Pin, ee_addr, invertedRelay)
Instancie l'objet CyclicTimer.

Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
IO_Pin		  | int  | Oui	  | Numéro de la broche utilisé.
ee_addr	      | int  | Non	  | Par défaut égal `0`. Position de début dans l'EEPROM. Occupe 17 octets.
invertedRelay | bool | Non	  | Par défaut égal `false`. Inverse l'état de la broche utilisé si égal `true`.


-------------

### getValue(type)
Renvoie le paramètre souhaité sous la fourme d'un long non signé, représentant un nombre de seconde.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `CYCLIC_DAY_ON` , `CYCLIC_DAY_OFF` , `CYCLIC_NIGHT_ON` , `CYCLIC_NIGHT_OFF`.


-------------

### setValue(type, sec)
Permet de configurer un paramètre.

Paramètres | Type		   | Requis | Description
---------- | ------------- | ------ | -----------
type	   | int		   | Oui	| Utiliser les constantes `CYCLIC_DAY_ON` , `CYCLIC_DAY_OFF` , `CYCLIC_NIGHT_ON` , `CYCLIC_NIGHT_OFF`.
sec	   	   | unsigned long | Oui	| Nombre de seconde.


-------------

### saveValue(type)
Sauvegarde le paramètre dans l'EEPROM.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `CYCLIC_DAY_ON` , `CYCLIC_DAY_OFF` , `CYCLIC_NIGHT_ON` , `CYCLIC_NIGHT_OFF` , `CYCLIC_ENABLE`.


-------------

### run(currentUnixTime, lightMode)
Lance l'analyse.

Paramètres		| Type			| Requis | Description
--------------- | ------------- | ------ | -----------
currentUnixTime | unsigned long | Oui	 | Numéro de la broche utilisé.
lightMode		| bool			| Non	 | Par défaut égal `true`. Jour ou nuit.


-------------

### isWorking()
Renvoie un booléen signifiant l'état de la broche. Si elle est à l'etat HIGH ou LOW.


-------------

### stop()
Passe la broche à l'etat LOW.


-------------

### enable(value)
Active ou désactive le timer.

Paramètres	  | Type | Requis | Description
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
