#include <Reservoir.h>

#define TAPIS_PIN 13

Reservoir reserve(TAPIS_PIN); // Declaration du thermostat sur la broche 13 de l'arduino

void setup()
{	
	// definition des paramètres voulu
	// la distance entre le capteur et le niveau
	// de l'eau ne dois pas dépassé 20cm
 	reserve.setValue(20);

	// active le thermostat
	reserve.enable();
}

void loop()
{
	unsigned int currentValue = 12; // A remplacer une lecture d'une sonde
	
	// param 1 = valeur actuelle
	reserve.run(currentValue); 
	
	
	bool alerte = reserve.alert();
	// alerte == true si on a depasse la limit est dépassé
	// sinon alerte == false
}