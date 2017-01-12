#include <DailyTimer.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
DateTime now;

#define LIGHT_PIN 10

DailyTimer light(LIGHT_PIN); // declaration de la minuterie sur la broche 10 de l'arduino

void setup()
{	
	Wire.begin();
	rtc.begin();
	
	// definition de l'heure de mise en route en période de croissance
	// param 1 choix de temporisation (DAILY_ON,DAILY_OFF)
	// param 2 = heure
	// param 3 = minute
	light.setValue(DAILY_ON, 10,00);	// 10:00
	light.setValue(DAILY_OFF, 22,00);	// 22:00
	
	
	// mais vous pouvez egalement l'écrire de cette manière 
	// param 1 choix de temporisation (DAILY_ON,DAILY_OFF)
	// param 2 (en minutes depuis 00:00 Hr)
	//light.setValue(DAILY_ON, 600);	// 10:00
	//light.setValue(DAILY_OFF , 1320);	// 22:00
	
	// active la minuterie
	light.enable();
}

void loop()
{
	now = rtc.now();
	// nowInMinutes = l'heure actuelle en minute depuis 00:00
	int nowInMinutes = (now.hour()*60)+now.minute();
	light.run(nowInMinutes); 
}