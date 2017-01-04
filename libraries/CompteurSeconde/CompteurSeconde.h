#ifndef CompteurSeconde_h
#define CompteurSeconde_h

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

class CompteurSeconde
{
	public:
		CompteurSeconde(int value = 0);
		void start(int value = 0);
		void run(int key);
		
		bool isSelect(void);
		int seconde(void);
		int increment(void);

	private:
		bool _isSelect;
		int _last_key;
		int _seconde;
		int _increment;
};
#endif
