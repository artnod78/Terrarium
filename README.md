Terrarium
===================
Contrôleur pour terrarium à base d'Arduino

DailyTimer
-------------
Minuterie journalière avec chevauchement sur 2 jours.
  - **DailyTimer(IO_Pin, invertedRelay)** : Instancie l'objet DailyTimer.

Parameters	  | Type | Required | Description
------------- | ---- | -------- | -----------
IO_Pin		  | Int  | Oui		| Numéro de la broche utilisé.
invertedRelay | bool | Non		| Par défaut égal `false`. Inverse l'état de la broche utilisé si égal `true`.

  - **getValue(type)** : Renvoie le paramètre souhaité sous la fourme d'un entier, représentant un nombre de minute depuis minuit.

Parameters | Type | Required | Description
---------- | ---- | -------- | -----------
type	   | Int  | Oui		 | Utiliser les constantes `TIMER_ON` et `TIMER_OFF`.

  - **setValue(type, minute)** : Permet de configurer un paramètre.

Parameters | Type | Required | Description
---------- | ---- | -------- | -----------
type	   | Int  | Oui		 | Utiliser les constantes `TIMER_ON` et `TIMER_OFF`.
minute	   | Int  | Oui		 | Nombre de minute depuis minuit. Exemple pour *10:27* `minute = (10*60) + 27`

  - **setValue(type, HH, MM)** : Permet de configurer un paramètre.

Parameters | Type | Required | Description
---------- | ---- | -------- | -----------
type	   | Int  | Oui		 | Utiliser les constantes `TIMER_ON` et `TIMER_OFF`.
HH	   	   | Int  | Oui		 | Heure. Exemple pour *10:27* `HH = 10`
MM	       | Int  | Oui		 | Minute. Exemple pour *10:27* `MM = 27`

  - **saveValue(loc, type)** : Sauvegarde le paramètre dans l'EEPROM.

Parameters | Type | Required | Description
---------- | ---- | -------- | -----------
loc		   | Int  | Oui		 | Position de l'objet dans la mémoire EEPROM.
type	   | Int  | Oui		 | Utiliser les constantes `TIMER_ON` , `TIMER_OFF` et `TIMER_ENABLE`.

   - **run(currentTime)** : Lance l'analyse.

Parameters	  | Type | Required | Description
------------- | ---- | -------- | -----------
currentTime	  | Int  | Oui		| Nombre de minute depuis minuit. Exemple pour *10:27* `minute = (10*60) + 27`

  - **isWorking()** : Renvoie un booléen signifiant l'état de la broche. Si elle est à l'etat HIGH ou LOW.
  - **enable(value)** :  Active ou désactive le timer.

Parameters	  | Type | Required | Description
------------- | ---- | -------- | -----------
value		  | bool | Non		| Par défaut égal `true`. Active `true` ou désactive `false` le timer.

  - **isEnable()** : Renvoie un booléen si le timer est actif ou non.
  - **loadAll(loc)** : Lis et remplace la configuration depuis l'EEPROM (5 octets).

Parameters | Type | Required | Description
---------- | ---- | -------- | -----------
loc		   | Int  | Oui		 | Position de l'objet dans la mémoire EEPROM.

  - **saveAll(loc)** : Sauvegarde la configuration dans l'EEPROM (5 octets).

Parameters | Type | Required | Description
---------- | ---- | -------- | -----------
loc		   | Int  | Oui		 | Position de l'objet dans la mémoire EEPROM.

