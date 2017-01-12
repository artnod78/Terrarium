# ReadKey
Permet la lecture d'un keypad.

## Constantes
 * `btnRIGHT` = 0
 * `btnUP` = 1
 * `btnDOWN` = 2
 * `btnLEFT` = 3
 * `btnSELECT` = 4
 * `btnNONE` = 5

## Méthodes
* [ReadKey()](#readkeyio_pin)
* [read()](#read)
* [isPress()](#ispress)
* [key()](#key)
* [val()](#val)

-------------

### ReadKey(IO_Pin)
Instancie l'objet ReadKey.

Paramètres	  | Type | Requis | Description
------------- | ---- | ------ | -----------
IO_Pin	      | int  | Non	  | Broche analogique où est connecté le keypad.


-------------

### read()
Lance la lecture.


-------------

### isPress()
Renvoie `true` si une touche a été appuyée. Sinon `false`.


-------------

### key()
Renvoie l'identifiant de la touche appuyé sous la forme d'un entier.
`btnRIGHT` , `btnUP` , `btnDOWN` , `btnLEFT` , `btnSELECT` , `btnNONE`.


-------------

### val()
Renvoie la valeur lu lors de l'appel de `read()` sous la forme d'un entier.


-------------
