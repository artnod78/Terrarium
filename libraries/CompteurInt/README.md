# CompteurInt
Compteur permettant la saisi d'un entier.

## Méthodes
* [CompteurInt()](#compteurintmin-max)
* [start()](#startmin-max)
* [run()](#runkey)
* [value()](#value)
* [isSelect()](#isselect)


-----------

#### CompteurInt(min, max)
Instancie l'objet CompteurInt.
 
Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
min		   | int  | Non	   | Par défaut égal `0`. Valeur minimum.
max		   | int  | Non	   | Par défaut égal `100`. Valeur maximum.


-------------

#### start(min, max)
Réinitialise l'objet CompteurInt.
 
Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
min		   | int  | Non	   | Par défaut égal `0`. Valeur minimum.
max		   | int  | Non	   | Par défaut égal `100`. Valeur maximum.


-------------

#### run(key)
Incrémente le menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
key		      | int  | Oui	  | Valeur correspondant à une touche du keypad. Voire la classe **ReadKey**.


-------------

#### value()
Renvoie sous la forme d'un entier la valeur saisi.


-------------

#### isSelect()
Renvoie `true` si le saisi est validée. Sinon `false`.


-------------