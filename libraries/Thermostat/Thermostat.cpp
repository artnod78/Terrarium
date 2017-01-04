#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "Thermostat.h"

Thermostat::Thermostat(int IO_Pin, bool invertedRelay)
{
	_IO_Pin        		= IO_Pin;
	_isWorking     	= false;
	_isEnable      	= false;
	_invertedRelay	= invertedRelay;
	pinMode(_IO_Pin,OUTPUT);
}

void Thermostat::setValue(int type,float temperature)
{
  _data[type] = temperature;
}

void Thermostat::enable(bool value)
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

void Thermostat::run(float currentTemperature, bool lightMode)
{
	if(_isEnable)
	{
		float temperature;
		bool new_state = false;
		if(lightMode) temperature = _data[THERMOSTAT_DAY];
 		else temperature = _data[THERMOSTAT_NIGHT];
		
		new_state = runCycle(currentTemperature, temperature);
		
		if(new_state != _isWorking)
		{
			if(new_state) activateRelay();
			else desactivateRelay();
			_isWorking = new_state;
		} 
	}
}

bool Thermostat::isWorking(void)
{
  return _isWorking;
}

bool Thermostat::isEnable(void)
{
  return _isEnable;
}

float Thermostat::getValue(int type)
{
  return _data[type];
}


void Thermostat::loadAll(int loc)
{
	EEPROM.get(loc, _data[THERMOSTAT_DAY]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[THERMOSTAT_NIGHT]);
	loc += sizeof(float);
	_isEnable = (EEPROM.read(loc) & 1);
}

void Thermostat::saveAll(int loc)
{
	EEPROM.put(loc, _data[THERMOSTAT_DAY]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[THERMOSTAT_NIGHT]);
	loc += sizeof(float);
	EEPROM.write(loc, (_isEnable ? 1 : 0));
}

void Thermostat::saveValue(int loc, int type)
{
	loc += sizeof(float) * type;
	switch (type)
	{
		case THERMOSTAT_DAY:
			EEPROM.put(loc, _data[THERMOSTAT_DAY]);
			break;
		
		case THERMOSTAT_NIGHT:
			EEPROM.put(loc, _data[THERMOSTAT_NIGHT]);
			break;
		
		case THERMOSTAT_ENABLE:
			EEPROM.write(loc, (_isEnable ? 1 : 0));
			break;
		
		default:
			break;
	}
}


bool Thermostat::runCycle(float currentTemperature, float temperature)
{
	bool working = false;
	if(_isWorking)
	{
		if(currentTemperature >= temperature) working = false;
		else working = true;    
	}  
	else
	{
		if(currentTemperature < temperature) working = true;
		else working = false;
	}
	return working;
}

void Thermostat::activateRelay(void)
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

void Thermostat::desactivateRelay(void)
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
