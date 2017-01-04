#ifndef CompteurInt_h
#define CompteurInt_h

class CompteurInt
{
	public:
		CompteurInt(int min = 0, int max = 100);
		void start(int value = 0);
		void run(int key);
		
		bool isSelect(void);
		int value(void);

	private:		
		bool _isSelect;
		int _last_key;
		int _value;		
		int _min;
		int _max;
};
#endif
