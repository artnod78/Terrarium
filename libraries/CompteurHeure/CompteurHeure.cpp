#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CompteurHeure.h"

CompteurHeure::CompteurHeure(int time)
{
	_heure = (int)time / 60;
	_minute = (int)time % 60;
	_isSelect = false;
	_heure_select = true;
	_last_key = 4;
}

void CompteurHeure::start(int time)
{
	_heure = (int)time / 60;
	_minute = (int)time % 60;
	_isSelect = false;
	_heure_select = true;
	_last_key = 4;
}

void CompteurHeure::run(int key)
{
	if(key != _last_key)
	{
		switch (key)
		{
			case 0:
				if(_heure_select) _heure_select = false;
				else _heure_select = true;
				break;
				
			case 1:
				if(_heure_select)
				{
					if(++_heure > 23) _heure = 0;
				}
				else
				{
					if(++_minute > 59) _minute = 0;
				}
				break;
				
			case 2:
				if(_heure_select)
				{
					if(--_heure < 0) _heure = 23;
				}
				else
				{
					if(--_minute < 0 ) _minute = 59;
				}
				break;
				
			case 3:
				if(_heure_select) _heure_select = false;
				else _heure_select = true;
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

bool CompteurHeure::isSelect(void)
{
	return _isSelect;
}

int CompteurHeure::time(void)
{
	return (_heure * 60) + _minute;
}

int CompteurHeure::heure(void)
{
	return _heure;
}

int CompteurHeure::minute(void)
{
	return _minute;
}

bool CompteurHeure::heure_select(void)
{
	return _heure_select;
}