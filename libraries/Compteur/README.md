# Compteur
Permet de naviguer à travers un menu.

## Constantes
 * `MENU_HOME` = 0
 * `MENU_LIGHT` = 1
 * `MENU_PULVE` = 2
 * `MENU_RESERVOIR` = 3
 * `MENU_TAPIS` = 4
 * `MENU_BRUMI` = 5
 * `MENU_CLOCK` = 6
 * `MENU_GENERAL` = 7
 * `DAILY_RETURN` = 3
 * `CYCLIC_RETURN` = 5
 * `RESERVOIR_RETURN` = 2
 * `THERMO_RETURN` = 5
 * `CLOCK_DATE` = 0
 * `CLOCK_HEURE` = 1
 * `CLOCK_RETURN` = 2
 * `GENERAL_RESET` = 2
 * `GENERAL_RETURN` = 3


## Méthodes
* [Compteur()](#compteurmin-max)
* [run()](#runkey)
* [index()](#index)
* [setIndex()](#setindexindex)
* [isSelect()](#isselect)
* [setSelect()](#setselectvalue)


-----------

#### Compteur(min, max)
Instancie l'objet Compteur.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
min		      | int  | Oui	  | Valeur minimum du menu.
max		      | int  | Oui	  | Valeur maximum du menu.


-------------

#### run(key)
Incrémente le menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
key		      | int  | Oui	  | Valeur correspondant à une touche du keypad. Voire la classe **ReadKey**.


-------------

#### index()
Renvoie sous la forme d'un entier la position actuelle dans le menu.


-------------

#### setIndex(index)
Modifier l'index du menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
index		  | int  | Oui	  | Nouvelle valeur de du menu.


-------------

#### isSelect()
Renvoie `true` si le menu est sélectionné. Sinon `false`.


-------------

#### setSelect(value)
Sélectionne ou désélectionne le menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
value		  | bool | Non	  | Par défaut égal `true`. Nouvelle valeur.


-------------

