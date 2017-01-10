#ifndef DailyTimer_h
#define DailyTimer_h

#include <EEPROM.h>

#define DAILY_ON   0
#define DAILY_OFF  1
#define DAILY_ENABLE  2
#define DAILY_EEPROM_LEN  5

class DailyTimer
{
   	public:
		// Déclaration de l'objet
  		DailyTimer(int IO_Pin, int ee_addr = 0, bool invertedRelay = false);
		
		// renvoie le paramètre
		// type = TIMER_ON ou TIMER_OFF
		// return = nombre de minute depuis minuit (22:30 -> 22*60 + 30 = 1350)
		int getValue(int type);
		// permet de modifier les valeurs par catégorie de parametrage
		// type = TIMER_ON ou TIMER_OFF
		// minute = nombre de minute depuis minuit (22:30 -> 22*60 + 30 = 1350)
		// HH - MM = heure - minute (22:30 -> HH = 22 et MM = 30)
		void setValue(int type, int minute);
		void setValue(int type,int HH, int MM);
		// sauvegarde le parametre dans l'EEPROM
		// type = DAILY_ON ou DAILY_OFF ou DAILY_ENABLE
		void saveValue(int type);
		
		
		// lance l'analyse
		// currentTime = nombre de minute depuis minuit (22:30 -> 22*60 + 30 = 1350)
		void run(int currentTime);
		// renvoie un booléen signifiant sont état
		bool isWorking(void);
		
		// active ou desactive le timer
		void enable(bool value = true);		
		//renvoie un booléen s'il est activé
		bool isEnable(void);
		
		// renvoie l'adresse EEPROM
		int getEEPROM(void);
		// renvoie le prochain octet libre
		int getNextEEPROM();
		// modifier l'adresse EEPROM
		void setEEPROM(int addr);
		//charge la conf depuis l'EEPROM
		void loadAll(void);	
		//sauvegarde la conf dans l'EEPROM
		void saveAll(void);
		
   	private:
  		int _IO_Pin;
		int _ee_addr;
		bool _invertedRelay;
		
		int _data[2];
  		bool _isWorking;
		bool _isEnable;
		bool runCycle(int now, int start, int stop);
		void activateRelay(void);
		void desactivateRelay(void);
};
#endif