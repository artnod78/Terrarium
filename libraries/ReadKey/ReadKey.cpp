#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "ReadKey.h"

ReadKey::ReadKey(int IO_Pin)
{
	_IO_Pin = IO_Pin;
	_key = btnNONE;
	_val = 0;
	pinMode(_IO_Pin, INPUT);
}

void ReadKey::read(void)
{
	int key = readKey();
	if (key != _key)
	{
		_key = key;
	}
}

int ReadKey::key(void)
{
	return _key;
}

int ReadKey::val(void)
{
	return _val;
}

int ReadKey::readKey(void)
{
	int key = analogRead(_IO_Pin);
	_val = key;
	if (key < 800) {
		if (key < 90) return btnRIGHT;
		else if (key < 200) return btnUP;
		else if (key < 400) return btnDOWN;
		else if (key < 600) return btnLEFT;
		else return btnSELECT;
	}
	return btnNONE;
}