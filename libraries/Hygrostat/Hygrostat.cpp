#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "Hygrostat.h"

Hygrostat::Hygrostat(int IO_Pin, bool invertedRelay)
{
	_IO_Pin        		= IO_Pin;
	_isWorking     	= false;
	_isEnable      	= false;
	_invertedRelay	= invertedRelay;
	pinMode(_IO_Pin,OUTPUT);
}


void Hygrostat::setValue(int type,float hygro)
{
  _data[type] = hygro;
}

void Hygrostat::enable(bool value)
{
	if(value != _isEnable)
	{
		if(_isWorking)
		{
			_isWorking = false;
			desactivateRelay();
		}
		_isEnable = value;
	}
}

void Hygrostat::run(float currentHygro, bool lightMode)
{
	if(_isEnable)
	{
		float hygro_min, hygro_max;
		bool new_state = false;
		
		if(lightMode)
		{
			hygro_min = _data[HYGRO_DAY_MIN];
			hygro_max = _data[HYGRO_DAY_MAX];
		}  
 		else
		{
			hygro_min = _data[HYGRO_NIGHT_MIN];
			hygro_max = _data[HYGRO_NIGHT_MAX];
		} 
		
		new_state = runCycle(currentHygro, hygro_min, hygro_max);
		
		if(new_state != _isWorking)
		{
			if(new_state) activateRelay();
			else desactivateRelay();
			_isWorking = new_state;
		}
	}
  
}

bool Hygrostat::isWorking(void)
{
  return _isWorking;
}

bool Hygrostat::isEnable(void)
{
  return _isEnable;
}

float Hygrostat::getValue(int type)
{
  return _data[type];
}

void Hygrostat::loadAll(int loc)
{
	EEPROM.get(loc, _data[HYGRO_DAY_MIN]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[HYGRO_DAY_MAX]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[HYGRO_NIGHT_MIN]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[HYGRO_NIGHT_MAX]);
	loc += sizeof(float);
	_isEnable = (EEPROM.read(loc) & 1);
}

void Hygrostat::saveAll(int loc)
{
	EEPROM.put(loc, _data[HYGRO_DAY_MIN]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[HYGRO_DAY_MAX]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[HYGRO_NIGHT_MIN]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[HYGRO_NIGHT_MAX]);
	loc += sizeof(float);
	EEPROM.write(loc, (_isEnable ? 1 : 0));
}

void Hygrostat::saveValue(int loc, int type)
{
	loc += sizeof(float) * type;
	switch (type)
	{
		case HYGRO_DAY_MIN:
			EEPROM.put(loc, _data[HYGRO_DAY_MIN]);
			break;
		
		case HYGRO_DAY_MAX:
			EEPROM.put(loc, _data[HYGRO_DAY_MAX]);
			break;
			
		case HYGRO_NIGHT_MIN:
			EEPROM.put(loc, _data[HYGRO_NIGHT_MIN]);
			break;
		
		case HYGRO_NIGHT_MAX:
			EEPROM.put(loc, _data[HYGRO_NIGHT_MAX]);
			break;
		
		case HYGRO_ENABLE:
			EEPROM.write(loc, (_isEnable ? 1 : 0));
			break;
		
		default:
			break;
	}
}

bool Hygrostat::runCycle(float currentHygro, float hygro_min, float hygro_max)
{
	bool working = false;
	if(_isWorking)
	{
		if(currentHygro >= hygro_max) working = false;
		else working = true;
	}  
	else
	{
		if(currentHygro <= hygro_min) working = true;
		else working = false;
	} 
	return working;
}

void Hygrostat::activateRelay()
{
  if(_invertedRelay)
  {
    digitalWrite(_IO_Pin,LOW);
  }
  else
  {  
    digitalWrite(_IO_Pin,HIGH);
  }
}

void Hygrostat::desactivateRelay()
{
   if(_invertedRelay)
  {
    digitalWrite(_IO_Pin,HIGH);
  }
  else
  {  
    digitalWrite(_IO_Pin,LOW);
  }
}
