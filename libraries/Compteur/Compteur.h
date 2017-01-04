#ifndef Compteur_h
#define Compteur_h

#define MENU_HOME	0
#define MENU_LIGHT	1
#define MENU_PULVE	2
#define MENU_TAPIS	3
#define MENU_BRUMI	4
#define MENU_CLOCK	5

#define LIGHT_ENABLE 	2
#define LIGHT_RETURN 	3

#define PULVE_ENABLE 	4
#define PULVE_RETURN 	5

#define TAPIS_ENABLE 	2
#define TAPIS_RETURN 	3

#define BRUMI_ENABLE 	4
#define BRUMI_RETURN 	5

#define CLOCK_DATE   	0
#define CLOCK_HEURE	 	1
#define CLOCK_RETURN 	2

class Compteur
{
	public:
		Compteur(int min, int max, int horizontal=1, int vertical=1);
		void run(int key);
		void setIndex(int index);
		void setSelect(bool value = true);
		
		bool isSelect(void);
		int index(void);

	private:
		bool _isSelect;
		int _last_key;
		int _index;
		int _min;
		int _max;
		int _horizontal;
		int _vertical;
};
#endif
