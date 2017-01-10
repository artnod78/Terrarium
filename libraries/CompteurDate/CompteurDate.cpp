#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CompteurDate.h"

CompteurDate::CompteurDate(int annee, int mois, int jour)
{
	_annee = annee;
	_mois = mois;
	_jour = jour;
	_isSelect = false;
	_selected = YEAR;
}

void CompteurDate::start(int annee, int mois, int jour)
{
	_annee = annee;
	_mois = mois;
	_jour = jour;
	_isSelect = false;
	_selected = YEAR;
}


void CompteurDate::run(int key)
{
	switch (key)
	{
		case 0:
			if(++_selected > DAY) _selected = YEAR;
			break;
			
		case 1:
			switch(_selected)
			{
				case YEAR:
					if(++_annee > 2050) _annee = 2016;
					break;
					
				case MONTH:
					if(++_mois > 12) _mois = 1;
					break;
					
				case DAY:
					if(++_jour > 31) _mois = 1;
					break;
					
				default:
					break;
			}
			break;
			
		case 2:
			switch(_selected)
			{
				case YEAR:
					if(--_annee < 2016) _annee = 2050;
					break;
					
				case MONTH:
					if(--_mois < 1) _mois = 12;
					break;
					
				case DAY:
					if(--_jour < 1) _mois = 31;
					break;
					
				default:
					break;
			}
			break;
			
		case 3:
			if(--_selected < YEAR) _selected = DAY;
			break;
			
		case 4:
			_isSelect = true;
			break;
			
		default:
			break;
	}
}


int CompteurDate::annee(void)
{
	return _annee;
}

int CompteurDate::mois(void)
{
	return _mois;
}

int CompteurDate::jour(void)
{
	return _jour;
}

bool CompteurDate::isSelect(void)
{
	return _isSelect;
}


int CompteurDate::selected(void)
{
	return _selected;
}