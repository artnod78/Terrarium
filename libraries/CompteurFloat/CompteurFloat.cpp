#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CompteurFloat.h"

CompteurFloat::CompteurFloat(float value)
{
	_entier = (int)value;
	_decimal = (int)((value - _entier)*100);
	_isSelect = false;
	_selected = true;
}

void CompteurFloat::start(float value)
{
	_entier = (int)value;
	_decimal = (int)((value - _entier)*100);
	_isSelect = false;
	_selected = true;
}


void CompteurFloat::run(int key)
{
	switch (key)
	{
		case 0:
			if(_selected) _selected = false;
			else _selected = true;
			break;
			
		case 1:
			if(_selected)
			{
				if(++_entier > 99) _entier = 0;
			}
			else
			{
				if(++_decimal > 99) _decimal = 0;
			}
			break;
			
		case 2:
			if(_selected)
			{
				if(--_entier < 0) _entier = 99;
			}
			else
			{
				if(--_decimal < 0 ) _decimal = 99;
			}
			break;
			
		case 3:
			if(_selected) _selected = false;
			else _selected = true;
			break;
			
		case 4:
			_isSelect = true;
			break;
			
		default:
			break;
	}
}


float CompteurFloat::value(void)
{
	return ((float)(_entier) + ((float)(_decimal)/100.0));
}

int CompteurFloat::entier(void)
{
	return _entier;
}

int CompteurFloat::decimal(void)
{
	return _decimal;
}

bool CompteurFloat::isSelect(void)
{
	return _isSelect;
}


bool CompteurFloat::selected(void)
{
	return _selected;
}