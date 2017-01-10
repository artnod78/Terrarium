#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "Compteur.h"

Compteur::Compteur(int min, int max)
{
	_index = min;
	_isSelect = false;
	_min = min;
	_max = max;
}

void Compteur::run(int key)
{
	switch (key)
	{
		case 0:
			_index += 1;
			if(_index > _max) _index = _min;
			break;
			
		case 1:
			_index += 1;
			if(_index > _max) _index = _min;
			break;
			
		case 2:
			_index -= 1;
			if(_index < _min) _index = _max;
			break;
			
		case 3:
			_index -= 1;
			if(_index < _min) _index = _max;
			break;
			
		case 4:
			_isSelect = true;
			break;
		
		default:
			break;
	}
}


int Compteur::index(void)
{
	return _index;
}

void Compteur::setIndex(int index)
{
	_index = index;
}


bool Compteur::isSelect(void)
{
	return _isSelect;
}

void Compteur::setSelect(bool value)
{
	_isSelect = value;
}