#include <Hygrostat.h>

#define BRUMI_PIN 13

Hygrostat brumi(BRUMI_PIN); // declaration de la minuterie sur pin 10 de l'arduino

void setup()
{	
	// definition de l'hygrométrie voulu
 	brumi.setValue(HYGRO_DAY_MIN, 75);
 	brumi.setValue(HYGRO_DAY_MAX, 85);
 	brumi.setValue(HYGRO_NIGHT_MIN, 80);
 	brumi.setValue(HYGRO_NIGHT_MAX, 90);

	// active la minuterie
	brumi.enable();
}

void loop()
{
	bool jour = true;
	float current_hygro = 82.56; // A remplacer une lecture de sonde hygrométrique
	
	// param 1 = hygrométrie actuelle
	// param 2 = jour ou nuit
	brumi.run(current_hygro,jour); 
}