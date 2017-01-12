# CompteurBool
Compteur permettant la saisi d'un booléen.

## Méthodes
* [CompteurBool()](#compteurboolvalue)
* [start()](#startvalue)
* [run()](#runkey)
* [value()](#value)
* [isSelect()](#isselect)


-----------

#### CompteurBool(value)
Instancie l'objet CompteurBool.
 
Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
value	   | bool | Non	   | Par défaut égal `false`. Valeur de début.


-------------

#### run(key)
Incrémente le menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
key		      | int  | Oui	  | Valeur correspondant à une touche du keypad. Voire la classe **ReadKey**.


-------------

#### value()
Renvoie sous la forme d'un booléen la saisi.


-------------

#### isSelect()
Renvoie `true` si le saisi est validée. Sinon `false`.


-------------