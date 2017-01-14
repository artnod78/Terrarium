# CompteurFloat
Compteur permettant la saisi d'un nombre décimal.

## Méthodes
* [CompteurFloat()](#compteurfloatvalue)
* [start()](#startvalue)
* [run()](#runkey)
* [value()](#value)
* [entier()](#entier)
* [decimal()](#decimal)
* [isSelect()](#isselect)
* [selected()](#isselect)


-----------

#### CompteurFloat(value)
Instancie l'objet CompteurFloat.
 
Paramètres | Type  | Requis | Description
---------- | ----- | ------ | -----------
value	   | float | Non	| Par défaut égal `0`.


-------------

#### start(value)
Réinitialise l'objet CompteurFloat.
 
Paramètres | Type  | Requis | Description
---------- | ----- | ------ | -----------
value	   | float | Non	| Par défaut égal `0`.


-------------

#### run(key)
Incrémente le menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
key		      | int  | Oui	  | Valeur correspondant à une touche du keypad. Voire la classe **ReadKey**.


-------------

#### value()
Renvoie sous la forme d'un nombre décimal.


-------------

#### entier()
Renvoie sous la forme d'un entier.


-------------

#### decimal()
Renvoie sous la forme d'un entier les decimal.


-------------

#### isSelect()
Renvoie `true` si le saisi est validée. Sinon `false`.


-------------

#### selected()
Renvoie `true` si le saisi est sur l'heure.
Renvoie `false` si le saisi est sur les minutes.


-------------