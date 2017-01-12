#include <CyclicTimer.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
DateTime now;

#define BRUMI_PIN 11

CyclicTimer brumi(BRUMI_PIN);

void setup()
{
	Wire.begin();
	rtc.begin();
	
	brumi.setValue(CYCLIC_DAY_ON, 8);			// 8 secondes ON le jour
	brumi.setValue(CYCLIC_DAY_OFF, 10800);		// 3 heures OFF le jour
	brumi.setValue(CYCLIC_NIGHT_ON, 4);			// 4 secondes ON la nuit
	brumi.setValue(CYCLIC_NIGHT_OFF, 21600);	// 6 heures OFF la nuit
	bruni.enable();
}

void loop()
{
	now = rtc.now();
	bool jour = true;
	brumi.run(now.unixtime(), jour);
}



