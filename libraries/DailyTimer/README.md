# DailyTimer
Minuterie journalière avec chevauchement sur 2 jours.

## Constantes
 * `TIMER_ON` = 0
 * `TIMER_OFF` = 1
 * `TIMER_ENABLE` = 2
 * `DAILY_EEPROM_LEN`  = 5

## Méthodes
* [DailyTimer()](#dailytimerio_pin-ee_addr-invertedrelay)
* [getValue()](#getvaluetype)
* [setValue(min)](#setvaluetype-minute)
* [setValue(HH,MM)](#setvaluetype-hh-mm)
* [saveValue()](#savevaluetype)
* [run()](#runcurrenttime)
* [isWorking()](#isworking)
* [enable()](#enablevalue)
* [isEnable()](#isenable)
* [getEEPROM()](#geteeprom)
* [getNextEEPROM()](#getnexteeprom)
* [setEEPROM()](#seteepromaddr)
* [loadAll()](#loadall)
* [saveAll()](#saveall)

-------------

### DailyTimer(IO_Pin, ee_addr, invertedRelay)
 Instancie l'objet DailyTimer.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
IO_Pin		  | int  | Oui	  | Numéro de la broche utilisé.
ee_addr	      | int  | Non	  | Par défaut égal `0`. Position de début dans l'EEPROM. Occupe 5 octets.
invertedRelay | bool | Non	  | Par défaut égal `false`. Inverse l'état de la broche utilisé si égal `true`.


-------------

### getValue(type)
Renvoie le paramètre souhaité sous la fourme d'un entier, représentant un nombre de minute depuis minuit.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `TIMER_ON` et `TIMER_OFF`.


-------------

### setValue(type, minute)
Permet de configurer un paramètre.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `TIMER_ON` et `TIMER_OFF`.
minute	   | int  | Oui	   | Nombre de minute depuis minuit. Exemple pour *10:27* `minute = (10*60) + 27`


-------------

### setValue(type, HH, MM)
Permet de configurer un paramètre.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `TIMER_ON` et `TIMER_OFF`.
HH	   	   | int  | Oui	   | Heure. Exemple pour *10:27* `HH = 10`
MM	       | int  | Oui	   | Minute. Exemple pour *10:27* `MM = 27`


-------------

### saveValue(type)
Sauvegarde le paramètre dans l'EEPROM.

Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
type	   | int  | Oui	   | Utiliser les constantes `TIMER_ON` , `TIMER_OFF` et `TIMER_ENABLE`.


-------------

### run(currentTime)
Lance l'analyse.

Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
currentTime	  | int  | Oui	  | Nombre de minute depuis minuit. Exemple pour *10:27* `minute = (10*60) + 27`


-------------

### isWorking()
Renvoie un booléen signifiant l'état de la broche. Si elle est à l'etat HIGH ou LOW.


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
Charge la configuration depuis l'EEPROM (5 octets).


-------------

### saveAll()
Sauvegarde la configuration dans l'EEPROM (5 octets).


-------------
