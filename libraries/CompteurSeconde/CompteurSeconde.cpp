#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CompteurSeconde.h"

CompteurSeconde::CompteurSeconde(int value)
{
	_seconde = value;
	_increment = 1;
	_isSelect = false;
	_last_key = 4;
}

void CompteurSeconde::start(int value)
{
	_seconde = value;
	_increment = 1;
	_isSelect = false;
	_last_key = 4;
}

void CompteurSeconde::run(int key)
{
	if(key != _last_key)
	{
		switch (key)
		{
			case btnUP:
				_seconde += _increment;
				if(_seconde > 86400 ) _seconde = 0;
				break;
			case btnDOWN:
				_seconde -= _increment;
				if(_seconde < 0 ) _seconde = 86400;
				break;
			case btnRIGHT:
				if(_increment == 1) _increment = 60;
				else if(_increment == 60) _increment = 3600;
				else if(_increment == 3600) _increment = 1;
				break;
			case btnLEFT:
				if(_increment == 1) _increment = 3600;
				else if(_increment == 60) _increment = 1;
				else if(_increment == 3600) _increment = 60;
				break;
			case btnSELECT:
				_isSelect = true;
				break;
		}
		_last_key = key;
	}
}

bool CompteurSeconde::isSelect(void)
{
	return _isSelect;
}

int CompteurSeconde::seconde(void)
{
	return _seconde;
}

int CompteurSeconde::increment(void)
{
	return _increment;
}