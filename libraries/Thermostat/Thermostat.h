#ifndef Thermostat_h
#define Thermostat_h

#include <EEPROM.h>

#define THERMOSTAT_DAY		0
#define THERMOSTAT_NIGHT	1
#define THERMOSTAT_ENABLE	2

class Thermostat
{
	public:
		// Déclaration de l'objet
		Thermostat(int IO_Pin, bool invertedRelay = false);

		// configure la temperature par catégorie 
		// param 1 = DAY_TEMPERATURE, NIGHT_TEMPERATURE
		// param 2 = température en degrès
		void    setValue(int type,float temperature);
		
		// active ou desactive le thermostat		
		void	enable(bool value = true);

		// lance l'analyse
		void 	run(float currentTemperature, bool lightMode = true);

		//renvoie un booléen signifiant sont état
		bool 	isWorking(void);
		
		//renvoie un booléen s'il est activé
		bool 	isEnable(void);

		// renvoie la valeur int d'un objet suivant sa catégorie
		float     getValue(int type);
		
		void loadAll(int loc);
		void saveAll(int loc);
		void saveValue(int loc, int type);
		
			
	private:
		int		_IO_Pin;
		bool	_isWorking;
		bool	_isEnable;
		bool	_invertedRelay;
		float	_data[2];	
		bool	runCycle(float currentTemperature, float temperature);
		void	activateRelay(void);
		void	desactivateRelay(void);
};
#endif
