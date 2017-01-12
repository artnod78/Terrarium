#ifndef CyclicTimer_h
#define CyclicTimer_h

#include <EEPROM.h>

#define CYCLIC_DAY_ON	0
#define CYCLIC_DAY_OFF	1
#define CYCLIC_NIGHT_ON	2
#define CYCLIC_NIGHT_OFF 3
#define CYCLIC_ENABLE	4
#define CYCLIC_EEPROM_LEN  17

class CyclicTimer
{
	public:
		// Déclaration de l'objet
		CyclicTimer(int IO_Pin, int ee_addr = 0, bool invertedRelay = false);

		// renvoie la valeur de l'objet suivant sa catégorie
		// type = CYCLIC_DAY_ON ou CYCLIC_DAY_OFF ou CYCLIC_NIGHT_ON ou CYCLIC_NIGHT_OFF 
		unsigned long getValue(int type);
		// permet de modifier en cours de route les valeurs par catégorie de parametrage
		// type = CYCLIC_DAY_ON ou CYCLIC_DAY_OFF ou CYCLIC_NIGHT_ON ou CYCLIC_NIGHT_OFF 
		// value = nombre de seconde
		void	setValue(int type, unsigned long sec);
		// sauvegarde le parametre dans l'EEPROM
		// type = CYCLIC_DAY_ON ou CYCLIC_DAY_OFF ou CYCLIC_NIGHT_ON ou CYCLIC_NIGHT_OFF ou CYCLIC_ENABLE
		void	saveValue(int type);
		
		// lance l'analyse
		void	run(unsigned long currentUnixTime, bool lightMode = true);
		// renvoie un booléen signifiant sont état
		bool	isWorking(void);
		// passe la broche à l'etat LOW
		void	stop(void);
		
		// active ou desactive le timer
		void	enable(bool value = true);
		//renvoie un booléen s'il est activé
		bool	isEnable(void);

		// renvoie l'adresse EEPROM
		int		getEEPROM(void);
		// renvoie le prochain octet libre
		int		getNextEEPROM();
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
		unsigned long _lastChange;
		unsigned long _data[4];	
		bool	runCycle(unsigned long currentUnixTime, unsigned long timeON, unsigned long timeOFF);
		void	activateRelay(void);
		void	desactivateRelay(void);
};
#endif