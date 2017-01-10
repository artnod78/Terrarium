#ifndef CompteurSeconde_h
#define CompteurSeconde_h

class CompteurSeconde
{
	public:
		CompteurSeconde(int value = 0);
		void start(int value = 0);
		
		void run(int key);
		
		int seconde(void);
		bool isSelect(void);
		
		int increment(void);

	private:
		int _seconde;
		bool _isSelect;
		
		int _increment;
};
#endif
