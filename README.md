Terrarium
===================
Gestion d'un terrarium à base d'Arduino
* Timer journalier pour le réglage de la lumière ON/OFF
* Timer cyclic pour les cycle de pulvérisation
* Thermostat/Hygrostat pour le chauffage/brumisateur
* Alerte niveau d'eau pour le réservoir
* Régulateur de vitesse pour le ventilateur
* IHM: lcd 16x2 et keypad 5 touches
* Gestion retro eclairage (durée et instensité)
* Horloge temps réel
* Rénitialisation d'usine de la configuration

![alt tag](https://raw.githubusercontent.com/artnod78/Terrarium/master/Images/Arduino_UNO_R3_Pinout.png)


[discord](https://discord.gg/dszbz)  

-------------

### Documentations
* [DailyTimer](https://github.com/artnod78/Terrarium/blob/master/libraries/DailyTimer)
* [CyclicTimer](https://github.com/artnod78/Terrarium/blob/master/libraries/CyclicTimer)
* [Thermostat](https://github.com/artnod78/Terrarium/blob/master/libraries/Thermostat)
* [FanSpeed](https://github.com/artnod78/Terrarium/blob/master/libraries/FanSpeed)
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

### TODO List
* Refonte de la Classe CyclicTimer (type de cycle, nombre de pulvérisation et durée pulverisation).
* Test du shield + doc.
* Création du boitier.
* Compléter la documentation.

-------------

### PATCH Note
#### 2018/04/18 v0.6
* Bug fix (constants des menu).

#### 2017/05/19 v0.5
* Modification des menus.
* Création du shield.
* Compléter la documentation.
* Bug fix.

#### 2017/03/18 v0.4
* Création de la librairies FanSpeed (menu, saisi...).
* Utiliser qu'un compteur pour les sous menu.
* Modifier le reset. Ne réinitiliser que les paramètres qui ont été modifié.
* Création d'un compteur pour la sasi de float.
* Compléter la documentation.

#### 2017/01/12 v0.3
* Création des menu pour la saisi du niveau d'eau critique dans le réservoir.
* Création des menu pour l'intensité et la durée du rétro éclairage.
* Création des menu pour vider l'EEPROM.
* Compléter la documentation.

#### 2017/01/10 v0.2
* Fusionner les librairies Thermostat et Hygrostat pour en faire qu'une.
* Limiter les sauvegardes dans l'EEPROM dans le cas où la nouvelle valeur et identique à l'ancienne.
* Configurer l'adresse EEPROM pour les objets lors de sa déclaration (au lieu de le spécifier a chaque fois lors des sauvegarde et chargement).
* Quelques modifications dans les compteurs.
* Compléter la documentation.

#### 2016/xx/xx v0.1
* Start
