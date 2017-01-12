#include <RetroLcd.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
DateTime now;

#define RETRO_PIN 10

RetroLcd retro(RETRO_PIN);

void setup()
{	
	Wire.begin();
	rtc.begin();
	
	// durée allumé apres appui d'une touche
 	retro.setValue(RETRO_TIME, 15);
	// l'intensité entre 0 et 8
 	retro.setValue(RETRO_BRIGHT, 3);
}

void loop()
{
	now = rtc.now();
	bool key_press = true;
	// param 1 = heure actuelle
	// param 2 = une touche a été appuyée? (oui=true, non=false)
	retro.run(now.unixtime(), key_press);
}