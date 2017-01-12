#ifndef RetroLcd_h
#define RetroLcd_h

#include <EEPROM.h>

#define RETRO_TIME   0
#define RETRO_BRIGHT  1
#define RETRO_EEPROM_LEN  4

class RetroLcd
{
	public:
		// Déclaration de l'objet
		RetroLcd(int IO_Pin, int ee_addr = 0);
		
		// renvoie un paramètre
		// type = RETRO_TIME ou RETRO_BRIGHT
		int		getValue(int type);
		// permet de modifier un paramètre
		// type = RETRO_TIME ou RETRO_BRIGHT
		void	setValue(int type, int value);
		// sauvegarde le parametre dans l'EEPROM
		// type = RETRO_TIME ou RETRO_BRIGHT
		void	saveValue(int type);
		
		// lance l'analyse
		void	run(unsigned long currentUnixTime, bool keyPress);
		bool	isWorking(void);
		
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
		// sauvegarde le parametre dans l'EEPROM
		// type = RETRO_TIME ou RETRO_BRIGHT
		
	private:
		int		_IO_Pin;
		int		_ee_addr;
		bool	_isWorking;
		int		_data[2];
		unsigned long _last_change;
};
#endif