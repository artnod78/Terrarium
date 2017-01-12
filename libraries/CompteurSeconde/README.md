# CompteurSeconde
Compteur permettant la saisi d'un nombre de seconde.
Modification de l’incrémentation avec les touches `btnLEFT` et `btnRIGHT`.

## Méthodes
* [CompteurSeconde()](#compteurintvalue)
* [start()](#startvalue)
* [run()](#runkey)
* [seconde()](#value)
* [isSelect()](#isselect)
* [increment()](#increment)


-----------

#### CompteurSeconde(value)
Instancie l'objet CompteurSeconde.
 
Paramètres | Type		   | Requis | Description
---------- | ------------- | ------ | -----------
value	   | unsigned long | Non    | Par défaut égal `0`. Valeur de début.


-------------

#### start(value)
Réinitialise l'objet CompteurSeconde.
 
Paramètres | Type		   | Requis | Description
---------- | ------------- | ------ | -----------
value	   | unsigned long | Non	| Par défaut égal `0`. Valeur de début.


-------------

#### run(key)
Incrémente le menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
key		      | int  | Oui	  | Valeur correspondant à une touche du keypad. Voire la classe **ReadKey**.


-------------

#### seconde()
Renvoie sous la forme d'un long non signé la valeur saisi.


-------------

#### isSelect()
Renvoie `true` si le saisi est validée. Sinon `false`.


-------------

#### increment()
Renvoie sous forme d'entier la valeur de l'incrémentation en seconde. **1**, **60** (1 minute) ou **3600** (1 heure).

-------------