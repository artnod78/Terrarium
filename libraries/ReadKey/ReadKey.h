#ifndef ReadKey_h
#define ReadKey_h

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

class ReadKey
{
	public:
		ReadKey(int IO_Pin);
		void read(void);
		bool isPress(void);
		int key(void);
		int val(void);

	private:
		int _IO_Pin;
		int _key;
		int _val;
		bool _isPress;
		int readKey(void);
};
#endif