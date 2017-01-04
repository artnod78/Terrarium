#ifndef CyclicTimer_h
#define CyclicTimer_h

#include <EEPROM.h>

#define CYCLIC_DAY_ON	0
#define CYCLIC_DAY_OFF	1
#define CYCLIC_NIGHT_ON	2
#define CYCLIC_NIGHT_OFF 3
#define CYCLIC_ENABLE	4

class CyclicTimer
{
	public:
		// Déclaration de l'objet
		CyclicTimer(int IO_Pin, bool invertedRelay = false);

		// permet de modifier en cours de route les valeurs par catégorie de parametrage
		// type = DAY_DURATION_ON ou DAY_DURATION_OFF ou NIGHT_DURATION_ON ou NIGHT_DURATION_OFF
		// value = nombre de seconde
		void	setValue(int type,unsigned long sec);
		
		// active ou desactive le timer
		void	enable(bool value = true);

		// lance l'analyse
		void 	run(unsigned long currentUnixTime, bool lightMode = true);

		// renvoie la valeur de l'objet suivant sa catégorie
		unsigned long getValue(int type);

		//renvoie un booléen signifiant sont état
		bool	isWorking(void);
		
		//renvoie un booléen s'il est activé
		bool	isEnable(void);

		void loadAll(int loc);
		void saveAll(int loc);
		void saveValue(int loc, int type);
		
	private:
		int				_IO_Pin;
		bool			_isWorking;
		bool			_isEnable;
		bool			_invertedRelay;
		unsigned long	_lastChange;
		unsigned long	_data[4];	
		bool			runCycle(unsigned long currentUnixTime, unsigned long timeON, unsigned long timeOFF);
		void			activateRelay(void);
		void			desactivateRelay(void);
};
#endif
