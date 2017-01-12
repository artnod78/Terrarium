#ifndef CompteurDate_h
#define CompteurDate_h

#define YEAR  	  0
#define MONTH     1
#define DAY		  2

class CompteurDate
{
	public:
		CompteurDate(int annee = 2017, int mois = 1, int jour = 1);
		void	start(int annee = 2017, int mois = 1, int jour = 1);
		
		void	run(int key);		
		
		int		annee(void);
		int		mois(void);
		int		jour(void);
		bool	isSelect(void);
		
		int		selected(void);

	private:
		int		_annee;
		int		_mois;
		int		_jour;
		bool	_isSelect;
		int		_selected;
};
#endif
