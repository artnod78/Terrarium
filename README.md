Terrarium
===================
Contrôleur pour terrarium à base d'Arduino

-------------

## Documentations
* [DailyTimer](https://github.com/artnod78/Terrarium/blob/master/libraries/DailyTimer)
* [CyclicTimer](https://github.com/artnod78/Terrarium/blob/master/libraries/CyclicTimer)
* [Thermostat](https://github.com/artnod78/Terrarium/blob/master/libraries/Thermostat)
* [Reservoir](https://github.com/artnod78/Terrarium/blob/master/libraries/Reservoir)
* [ReadKey](https://github.com/artnod78/Terrarium/blob/master/libraries/ReadKey)
* [RetroLcd](https://github.com/artnod78/Terrarium/blob/master/libraries/RetroLcd)
* [Compteur](https://github.com/artnod78/Terrarium/blob/master/libraries/Compteur)
* [CompteurBool](https://github.com/artnod78/Terrarium/blob/master/libraries/CompteurBool)
* [CompteurDate](https://github.com/artnod78/Terrarium/blob/master/libraries/CompteurDate)
* [CompteurHeure](https://github.com/artnod78/Terrarium/blob/master/libraries/CompteurHeure)
* [CompteurSeconde](https://github.com/artnod78/Terrarium/blob/master/libraries/CompteurSeconde)
* [CompteurInt](https://github.com/artnod78/Terrarium/blob/master/libraries/CompteurInt)

-------------

## TODO List
* Utiliser qu'un compteur pour la saisi des paramètres. Réinstancier le même objet avec une autre classe.
* Modifier le le reset. Ne réinitiliser et sauvegarder que les paramètres qui ont été modifié.
* Créer un compteur pour la sasi de float.
* Compléter la documentation.

-------------

## PATCH Note
### 2017/01/12 v0.3
* Créer les menu pour la saisi du niveau d'eau critique dans le réservoir.
* Créer les menu pour l'intensité et la durée du rétro éclairage.
* Créer les menu pour vider l'EEPROM.
* Mise à jour doc existante.

### 2017/01/10 v0.2
* Fusionner les librairies Thermostat et Hygrostat pour en faire qu'une.
* Limiter les sauvegardes dans l'EEPROM dans le cas où la nouvelle valeur et identique à l'ancienne.
* Configurer l'adresse EEPROM pour les objets lors de sa déclaration (au lieu de le spécifier a chaque fois lors des sauvegarde et chargement).
* Quelques modifications dans les compteurs.
* Mise à jour doc existante.

### 2016/xx/xx v0.1
* Start
