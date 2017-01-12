#include <Thermostat.h>

#define TAPIS_PIN 13

Thermostat brumi(TAPIS_PIN); // Declaration du thermostat sur la broche 13 de l'arduino

void setup()
{	
	// definition des paramètres voulu
 	brumi.setValue(THERMO_DAY_MIN, 25);
 	brumi.setValue(THERMO_DAY_MAX, 27);
 	brumi.setValue(THERMO_NIGHT_MIN, 20);
 	brumi.setValue(THERMO_NIGHT_MAX, 22);

	// active le thermostat
	brumi.enable();
}

void loop()
{
	float currentValue = 23.45; // A remplacer une lecture d'une sonde
	bool jour = true;
	
	// param 1 = valeur actuelle
	// param 2 = jour ou nuit
	brumi.run(currentValue, jour); 
}