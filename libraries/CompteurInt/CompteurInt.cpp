#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CompteurInt.h"

CompteurInt::CompteurInt(int min, int max)
{
	_value = 0;
	_isSelect = false;
	_min = min;
	_max = max;
}

void CompteurInt::start(int value)
{
	_value = value;
	_isSelect = false;
}


void CompteurInt::run(int key)
{
	switch (key)
	{
		case 0:
			if(++_value > _max ) _value = _min;
			break;
			
		case 1:
			if(++_value > _max ) _value = _min;
			break;
			
		case 2:
			if(--_value < _min ) _value = _max;
			break;
			
		case 3:
			if(--_value < _min ) _value = _max;
			break;
			
		case 4:
			_isSelect = true;
			break;
		
		default:
			break;
	}
}


int CompteurInt::value(void)
{
	return _value;
}

bool CompteurInt::isSelect(void)
{
	return _isSelect;
}