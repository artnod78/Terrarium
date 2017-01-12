#ifndef CompteurHeure_h
#define CompteurHeure_h

class CompteurHeure
{
	public:
		CompteurHeure(int time = 0);
		void	start(int time = 0);
		
		void	run(int key);
		
		int		time(void);
		int		heure(void);
		int		minute(void);
		bool	isSelect(void);
		
		bool	selected(void);		
		
	private:		
		int		_heure;
		int		_minute;
		bool	_isSelect;		
		bool	_selected;
};
#endif
