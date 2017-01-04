#ifndef CompteurHeure_h
#define CompteurHeure_h

class CompteurHeure
{
	public:
		CompteurHeure(int time = 0);
		void start(int time = 0);
		void run(int key);
		
		bool isSelect(void);
		int time(void);
		int heure(void);
		int minute(void);
		bool	heure_select(void);
		
	private:		
		bool _isSelect;
		int _last_key;
		int _heure;
		int _minute;		
		bool _heure_select;
};
#endif
