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
	_selected = true;
}

void CompteurHeure::start(int time)
{
	_heure = (int)time / 60;
	_minute = (int)time % 60;
	_isSelect = false;
	_selected = true;
}


void CompteurHeure::run(int key)
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
				if(++_heure > 23) _heure = 0;
			}
			else
			{
				if(++_minute > 59) _minute = 0;
			}
			break;
			
		case 2:
			if(_selected)
			{
				if(--_heure < 0) _heure = 23;
			}
			else
			{
				if(--_minute < 0 ) _minute = 59;
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

bool CompteurHeure::isSelect(void)
{
	return _isSelect;
}


bool CompteurHeure::selected(void)
{
	return _selected;
}