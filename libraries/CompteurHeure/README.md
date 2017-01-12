# CompteurHeure
Compteur permettant la saisi de l'heure (heure et minute).

## Méthodes
* [CompteurHeure()](#compteurheuretime)
* [start()](#starttime)
* [run()](#runkey)
* [time()](#time)
* [heure()](#heure)
* [minute()](#minute)
* [isSelect()](#isselect)
* [selected()](#isselect)


-----------

#### CompteurHeure(time)
Instancie l'objet CompteurHeure.
 
Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
time	   | int  | Non	   | Par défaut égal `0`. Nombre de minute depuis minuit.


-------------

#### start(time)
Réinitialise l'objet CompteurHeure.
 
Paramètres | Type | Requis | Description
---------- | ---- | ------ | -----------
time	   | int  | Non	   | Par défaut égal `0`. Nombre de minute depuis minuit.


-------------

#### run(key)
Incrémente le menu.
 
Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
key		      | int  | Oui	  | Valeur correspondant à une touche du keypad. Voire la classe **ReadKey**.


-------------

#### time()
Renvoie sous la forme d'un entier l'heure en minute depuis minuit.


-------------

#### heure()
Renvoie sous la forme d'un entier l'heure saisi.


-------------

#### minute()
Renvoie sous la forme d'un entier la minute saisi.


-------------

#### isSelect()
Renvoie `true` si le saisi est validée. Sinon `false`.


-------------

#### selected()
Renvoie `true` si le saisi est sur l'heure.
Renvoie `false` si le saisi est sur les minutes.


-------------