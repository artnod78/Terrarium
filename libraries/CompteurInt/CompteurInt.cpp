#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CompteurInt.h"

CompteurInt::CompteurInt(int min, int max)
{
	_min = min;
	_max = max;
	_value = 0;
	_isSelect = false;
	_last_key = 4;
}

void CompteurInt::start(int value)
{
	_value = value;
	_isSelect = false;
	_last_key = 4;
}

void CompteurInt::run(int key)
{
	if(key != _last_key)
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
		_last_key = key;
	}
}

bool CompteurInt::isSelect(void)
{
	return _isSelect;
}

int CompteurInt::value(void)
{
	return _value;
}
