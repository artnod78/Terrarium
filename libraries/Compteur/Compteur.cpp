#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "Compteur.h"

Compteur::Compteur(int min, int max, int horizontal, int vertical)
{
	_isSelect = false;
	_index = min;
	_min = min;
	_max = max;
	_horizontal = horizontal;
	_vertical = vertical;
	_last_key = 4;
}

void Compteur::run(int key)
{
	if(key != _last_key)
	{
		switch (key)
		{
			case 0:
				_index += _horizontal;
				if(_index > _max) _index = _min;
				break;
				
			case 1:
				_index += _vertical;
				if(_index > _max) _index = _min;
				break;
				
			case 2:
				_index -= _horizontal;
				if(_index < _min) _index = _max;
				break;
				
			case 3:
				_index -= _vertical;
				if(_index < _min) _index = _max;
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

void Compteur::setIndex(int index)
{
	_index = index;
}

void Compteur::setSelect(bool value)
{
	_isSelect = value;
}

int Compteur::index(void)
{
	return _index;
}

bool Compteur::isSelect(void)
{
	return _isSelect;
}
