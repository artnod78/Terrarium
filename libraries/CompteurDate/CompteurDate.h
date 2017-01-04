#ifndef CompteurDate_h
#define CompteurDate_h

#define YEAR  	  0
#define MONTH     1
#define DAY		  2

class CompteurDate
{
	public:
		CompteurDate(int annee = 2017, int mois = 1, int jour = 1);
		void start(int annee = 2017, int mois = 1, int jour = 1);
		void run(int key);		
		
		bool isSelect(void);
		int annee(void);
		int mois(void);
		int jour(void);
		int selected(void);

	private:
		bool _isSelect;
		int _last_key;
		int _annee;
		int _mois;
		int _jour;
		int _selected;
};
#endif
