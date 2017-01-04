#ifndef DailyTimer_h
#define DailyTimer_h

#include <EEPROM.h>

#define DAILY_ON   0
#define DAILY_OFF  1
#define DAILY_ENABLE  2

class DailyTimer
{
   	public:
		// Déclaration de l'objet
  		DailyTimer(int IO_Pin, bool invertedRelay = false);
		
		// permet de modifier les valeurs par catégorie de parametrage
		// type = TIMER_ON ou TIMER_OFF
		// minute = nombre de minute depuis minuit (22:30 -> 22*60 + 30 = 1350)
		// HH - MM = heure - minute (22:30 -> HH = 22 et MM = 30)
		void	setValue(int type, int minute);
		void 	setValue(int type,int HH, int MM);
		
		// active ou desactive le timer
		void	enable(bool value = true);
		
		// lance l'analyse
		// currentTime = nombre de minute depuis minuit (22:30 -> 22*60 + 30 = 1350)
		void	run(int currentTime);
	  
		// renvoie le paramètre
		// type = TIMER_ON ou TIMER_OFF
		// return = nombre de minute depuis minuit (22:30 -> 22*60 + 30 = 1350)
		int	getValue(int type);
	  
		// renvoie un booléen signifiant sont état
		bool	isWorking(void);
		
		//renvoie un booléen s'il est activé
		bool	isEnable(void);
		
		//charge la conf depuis l'EEPROM (5 octets)
		// loc = lecture des 5 octets depuis cette position
		void	loadAll(int loc);
		
		//sauvegarde la conf dans l'EEPROM (5 octets)
		// loc = ecriture des 5 octets depuis cette position
		void	saveAll(int loc);
		
		// sauvegarde le parametre dans l'EEPROM
		// loc = position du 1er parametre
		// type = DAILY_ON ou DAILY_OFF ou DAILY_ENABLE
		void	saveValue(int loc, int type);
		
   	private:
  		int		_IO_Pin;
		int		_data[2];
		bool	_invertedRelay;
  		bool	_isWorking;
		bool	_isEnable;
		bool	runCycle(int now, int start, int stop);
		void	activateRelay(void);
		void	desactivateRelay(void);
};
#endif