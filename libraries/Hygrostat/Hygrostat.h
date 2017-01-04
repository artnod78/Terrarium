#ifndef Hygrostat_h
#define Hygrostat_h

#include <EEPROM.h>

#define HYGRO_DAY_MIN	0
#define HYGRO_DAY_MAX	1
#define HYGRO_NIGHT_MIN	2
#define HYGRO_NIGHT_MAX	3
#define HYGRO_ENABLE	4

class Hygrostat
{
	public:
		// Déclaration de l'objet
		Hygrostat(int IO_Pin, bool invertedRelay = false);

		// configure la temperature par catégorie 
		// param 1 = DAY_HYGRO_MIN, DAY_HYGRO_MAX, NIGHT_HYGRO_MIN, NIGHT_HYGRO_MAX
		// param 2 = température en degrès
		void    setValue(int type, float hygro);
		
		// active ou desactive le thermostat		
		void	enable(bool value = true);

		// lance l'analyse
		void 	run(float currentHygro, bool lightMode = true);

		//renvoie un booléen signifiant sont état
		bool 	isWorking(void);
		
		//renvoie un booléen s'il est activé
		bool 	isEnable(void);

		// renvoie la valeur int d'un objet suivant sa catégorie
		float	getValue(int type);
		
		void loadAll(int loc);
		void saveAll(int loc);
		void saveValue(int loc, int type);
		
	private:
		int		_IO_Pin;
		bool	_isWorking;
		bool	_isEnable;
		bool	_invertedRelay;
		float	_data[4];	
		bool	runCycle(float currentHygro, float hygro_min, float hygro_max);
		void	activateRelay(void);
		void	desactivateRelay(void);
};
#endif
