#include <Thermostat.h>

#define TAPIS_PIN 12

Thermostat tapis(TAPIS_PIN); // declaration de la minuterie sur pin 10 de l'arduino

void setup()
{	
	// definition de la temperature voulu
	// param 1 choix de temporisation (DAY_TEMPERATURE,NIGHT_TEMPERATURE)
	// param 2 = temperature
 	tapis.setValue(THERMOSTAT_DAY, 26);
 	tapis.setValue(THERMOSTAT_NIGHT, 21);

	// active la minuterie
	tapis.enable();
}

void loop()
{
	bool jour = true;
	float current_temperature = 24.6; // A remplacer une lecture de sonde temperature
	
	// param 1 = temperature actuelle
	// param 2 = jour ou nuit
	tapis.run(current_temperature,jour); 
}