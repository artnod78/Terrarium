#ifndef Reservoir_h
#define Reservoir_h

#include <EEPROM.h>

#define RESERVOIR_LIMIT   0
#define RESERVOIR_ENABLE  1
#define RESERVOIR_EEPROM_LEN  3

class Reservoir
{
	public:
		// Déclaration de l'objet
		Reservoir(int ee_addr = 0);
		
		// renvoie un paramètre
		int getValue(void);
		// permet de modifier un paramètre
		void setValue(int value);
		// sauvegarde le parametre dans l'EEPROM
		void saveValue(int type);
		
		// lance l'analyse
		void run(unsigned int currentValue);
		bool alert(void);
		
		// active ou desactive le timer
		void enable(bool value = true);		
		//renvoie un booléen s'il est activé
		bool isEnable(void);
		
		// renvoie l'adresse EEPROM
		int getEEPROM(void);
		// renvoie le prochain octet libre
		int getNextEEPROM(void);
		// modifier l'adresse EEPROM
		void setEEPROM(int addr);
		//charge la conf depuis l'EEPROM
		void loadAll(void);
		//sauvegarde la conf dans l'EEPROM
		void saveAll(void);
		// sauvegarde le parametre dans l'EEPROM
		
	private:
		int _ee_addr;
		int _limit;
		bool _alert;
		bool _isEnable;
};
#endif