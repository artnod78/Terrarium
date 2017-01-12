#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CompteurSeconde.h"

CompteurSeconde::CompteurSeconde(unsigned long value)
{
	_seconde = value;
	_isSelect = false;
	_increment = 1;
}

void CompteurSeconde::start(unsigned long value)
{
	_seconde = value;
	_isSelect = false;
	_increment = 1;
}


void CompteurSeconde::run(int key)
{
	switch (key)
	{
		case 0:
			if(_increment == 1) _increment = 60;
			else if(_increment == 60) _increment = 3600;
			else if(_increment == 3600) _increment = 1;
			break;
			
		case 1:
			_seconde += _increment;
			if(_seconde > 4294967295 ) _seconde = 0;
			break;
			
		case 2:
			_seconde -= _increment;
			if(_seconde < 0 ) _seconde = 4294967295;
			break;
			
		case 3:
			if(_increment == 1) _increment = 3600;
			else if(_increment == 60) _increment = 1;
			else if(_increment == 3600) _increment = 60;
			break;
			
		case 4:
			_isSelect = true;
			break;
			
		default:
			break;
	}
}


int CompteurSeconde::seconde(void)
{
	return _seconde;
}

bool CompteurSeconde::isSelect(void)
{
	return _isSelect;
}


int CompteurSeconde::increment(void)
{
	return _increment;
}