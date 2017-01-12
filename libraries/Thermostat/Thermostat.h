#ifndef Thermostat_h
#define Thermostat_h

#include <EEPROM.h>

#define THERMO_DAY_MIN		0
#define THERMO_DAY_MAX		1
#define THERMO_NIGHT_MIN	2
#define THERMO_NIGHT_MAX	3
#define THERMO_ENABLE		4
#define THERMO_EEPROM_LEN	17

class Thermostat
{
	public:
		// Déclaration de l'objet
		Thermostat(int IO_Pin, int ee_addr = 0, bool invertedRelay = false);

		// renvoie la valeur int d'un objet suivant sa catégorie
		// type = THERMO_DAY_MIN, THERMO_DAY_MAX, THERMO_NIGHT_MIN, THERMO_NIGHT_MAX
		float	getValue(int type);
		// configure la temperature par catégorie 
		// param 1 = THERMO_DAY_MIN, THERMO_DAY_MAX, THERMO_NIGHT_MIN, THERMO_NIGHT_MAX
		// param 2 = valeur
		void	setValue(int type, float value);
		// sauvegarde le parametre dans l'EEPROM
		// param 1 = THERMO_DAY_MIN, THERMO_DAY_MAX, THERMO_NIGHT_MIN, THERMO_NIGHT_MAX
		void	saveValue(int type);
		
		// lance l'analyse
		void 	run(float currentValue, bool lightMode = true);
		//renvoie un booléen signifiant sont état
		bool 	isWorking(void);
		
		// active ou desactive le thermostat		
		void	enable(bool value = true);		
		//renvoie un booléen s'il est activé
		bool 	isEnable(void);

		// renvoie l'adresse EEPROM
		int		getEEPROM(void);
		// renvoie le prochain octet libre
		int		getNextEEPROM(void);
		// modifier l'adresse EEPROM
		void	setEEPROM(int addr);
		//charge la conf depuis l'EEPROM
		void	loadAll(void);
		//sauvegarde la conf dans l'EEPROM
		void	saveAll(void);
		
	private:
		int		_IO_Pin;
		int		_ee_addr;
		bool	_isWorking;
		bool	_isEnable;
		bool	_invertedRelay;
		float	_data[4];	
		bool	runCycle(float value, float min, float max);
		void	activateRelay(void);
		void	desactivateRelay(void);
};
#endif