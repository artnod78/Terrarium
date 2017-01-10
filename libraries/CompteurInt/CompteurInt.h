#ifndef CompteurInt_h
#define CompteurInt_h

class CompteurInt
{
	public:
		CompteurInt(int min = 0, int max = 100);
		void start(int value = 0);
		
		void run(int key);
		
		int value(void);
		bool isSelect(void);

	private:		
		int _value;	
		bool _isSelect;
		
		int _min;
		int _max;
};
#endif
