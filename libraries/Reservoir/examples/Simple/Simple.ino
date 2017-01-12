#include <Reservoir.h>

Reservoir reserve;

void setup()
{	
	// definition des paramètres voulu
	// la distance entre le capteur et le niveau
	// de l'eau ne dois pas dépassé 20cm
 	reserve.setValue(20);

	// active le Reservoir
	reserve.enable();
}

void loop()
{
	unsigned int currentValue = 12; // A remplacer une lecture d'une sonde
	
	// param 1 = valeur actuelle
	reserve.run(currentValue); 
	
	
	bool alerte = reserve.alert();
	// alerte == true si currentValue >= limit
	// sinon alerte == false
}