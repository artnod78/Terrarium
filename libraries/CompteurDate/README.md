# CompteurDate
Compteur permettant la saisi d'une date (année, mois et jour).

## Méthodes
* `YEAR` = 0
* `MONTH` = 1
* `DAY` = 2

## Méthodes
* [CompteurDate()](#compteurdateannee-mois-jour)
* [start()](#startannee-mois-jour)
* [run()](#runkey)
* [value()](#value)
* [isSelect()](#isselect)
* [selected()](#isselect)


-----------

#### CompteurDate(annee, mois, jour)
Instancie l'objet CompteurDate.
 
Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
annee	   | int  | Non	   | Par défaut égal `2017`. Valeur de début.
mois	   | int  | Non	   | Par défaut égal `01`. Valeur de début.
jour	   | int  | Non	   | Par défaut égal `01`. Valeur de début.


-------------

#### start(annee, mois, jour)
Réinitialise l'objet CompteurDate.
 
Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
annee	   | int  | Non	   | Par défaut égal `2017`. Valeur de début.
mois	   | int  | Non	   | Par défaut égal `01`. Valeur de début.
jour	   | int  | Non	   | Par défaut égal `01`. Valeur de début.


-------------

#### run(key)
Incrémente le menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
key		      | int  | Oui	  | Valeur correspondant à une touche du keypad. Voire la classe **ReadKey**.


-------------

#### annee()
Renvoie sous la forme d'un entier l'année saisi.


-------------

#### mois()
Renvoie sous la forme d'un entier le mois saisi.


-------------

#### jour()
Renvoie sous la forme d'un entier le jour saisi.


-------------

#### isSelect()
Renvoie `true` si le saisi est validée. Sinon `false`.


-------------

#### selected()
Renvoie `YEAR` si le saisi est sur l'année.
Renvoie `MONTH` si le saisi est sur le mois.
Renvoie `DAY` si le saisi est sur le jour.


-------------