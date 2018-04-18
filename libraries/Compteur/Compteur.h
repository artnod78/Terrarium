#ifndef Compteur_h
#define Compteur_h

#define MENU_HOME		0
#define MENU_LIGHT		1
#define MENU_PULVE		2
#define MENU_RESERVOIR	3
#define MENU_TEMP		4
#define MENU_HUM		5
#define MENU_THERMO		6
#define MENU_CLOCK		7
#define MENU_GENERAL	8

#define DAILY_RETURN		3
#define CYCLIC_RETURN		5
#define RESERVOIR_RETURN	2
#define FAN_TEMP_RETURN		4
#define FAN_HUM_RETURN		8


#define THERMO_HEAT		0
#define THERMO_FAN		1
#define THERMO_RETURN	2

#define CLOCK_DATE   	0
#define CLOCK_HEURE	 	1
#define CLOCK_RETURN 	2

#define GENERAL_RESET	2
#define GENERAL_RETURN	3

class Compteur
{
	public:
		Compteur(int min = 0 , int max = 0);
		void run(int key);
		
		int index(void);
		void setIndex(int index);
		
		bool isSelect(void);
		void setSelect(bool value = true);
		
	private:
		int	_index;
		bool _isSelect;
		
		int	_min;
		int _max;
};
#endif
