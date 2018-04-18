#ifndef FanSpeed_h
#define FanSpeed_h

#include <EEPROM.h>

#define FAN_TEMP_DAY_MIN	0
#define FAN_TEMP_DAY_MAX	1
#define FAN_TEMP_NIGHT_MIN	2
#define FAN_TEMP_NIGHT_MAX	3

#define FAN_HUM_DAY_MIN		4
#define FAN_HUM_DAY_MAX		5
#define FAN_HUM_NIGHT_MIN	6
#define FAN_HUM_NIGHT_MAX	7

#define FAN_ENABLE		8
#define FAN_EEPROM_LEN	33

#define FAN_SPEED_0	0
#define FAN_SPEED_1	85
#define FAN_SPEED_2	170
#define FAN_SPEED_3	255

class FanSpeed
{
	public:
		// Déclaration de l'objet
		FanSpeed(int IO_Pin, int ee_addr = 0);

		// renvoie la valeur int d'un objet suivant sa catégorie
		float	getValue(int type);
		// configure la temperature par catégorie 
		void	setValue(int type, float value);
		// sauvegarde le parametre dans l'EEPROM
		void	saveValue(int type);
		
		// lance l'analyse
		void 	run(float currentTemp, float currentHum, bool lightMode = true);
		
		//renvoie un booléen signifiant sont état
		int 	isWorking(void);
		
		// active ou desactive le FanSpeed		
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
		int		_isWorking;
		bool	_isEnable;
		float	_data[8];	
		int	runCycle(float temp, float hum, float temp_min, float temp_max, float hum_min, float hum_max);
		void	set_speed(int speed);
};
#endif