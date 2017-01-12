#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CompteurBool.h"

CompteurBool::CompteurBool(bool value)
{
	_value = value;
	_isSelect = false;
}

void CompteurBool::start(bool value)
{
	_value = value;
	_isSelect = false;
}


void CompteurBool::run(int key)
{
	switch (key)
	{
		case 0:
			if(_value) _value = false;
			else _value = true;
			break;
			
		case 1:
			if(_value) _value = false;
			else _value = true;
			break;
			
		case 2:
			if(_value) _value = false;
			else _value = true;
			break;
			
		case 3:
			if(_value) _value = false;
			else _value = true;
			break;
			
		case 4:
			_isSelect = true;
			break;
		
		default:
			break;
	}
}


bool CompteurBool::value(void)
{
	return _value;
}

bool CompteurBool::isSelect(void)
{
	return _isSelect;
}