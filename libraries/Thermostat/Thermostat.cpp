#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "Thermostat.h"

Thermostat::Thermostat(int IO_Pin, int ee_addr, bool invertedRelay)
{
	_IO_Pin        		= IO_Pin;
	_ee_addr		= ee_addr;
	_isWorking     	= false;
	_isEnable      	= false;
	_invertedRelay	= invertedRelay;
	pinMode(_IO_Pin,OUTPUT);
}


float Thermostat::getValue(int type)
{
  return _data[type];
}

void Thermostat::setValue(int type,float value)
{
  _data[type] = value;
}

void Thermostat::saveValue(int type)
{
	int loc = _ee_addr + (sizeof(float) * type);
	switch (type)
	{
		case THERMO_DAY_MIN:
			EEPROM.put(loc, _data[THERMO_DAY_MIN]);
			break;
		
		case THERMO_DAY_MAX:
			EEPROM.put(loc, _data[THERMO_DAY_MAX]);
			break;
			
		case THERMO_NIGHT_MIN:
			EEPROM.put(loc, _data[THERMO_NIGHT_MIN]);
			break;
		
		case THERMO_NIGHT_MAX:
			EEPROM.put(loc, _data[THERMO_NIGHT_MAX]);
			break;
		
		case THERMO_ENABLE:
			EEPROM.write(loc, (_isEnable ? 1 : 0));
			break;
		
		default:
			break;
	}
}


void Thermostat::run(float currentValue, bool lightMode)
{
	if(_isEnable)
	{
		float min, max;
		bool new_state = false;
		
		if(lightMode)
		{
			min = _data[THERMO_DAY_MIN];
			max = _data[THERMO_DAY_MAX];
		}  
 		else
		{
			min = _data[THERMO_NIGHT_MIN];
			max = _data[THERMO_NIGHT_MAX];
		} 
		
		new_state = runCycle(currentValue, min, max);
		
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
bool Thermostat::isEnable(void)
{
  return _isEnable;
}


int Thermostat::getEEPROM(void)
{
	return _ee_addr;
}

int Thermostat::getNextEEPROM(void)
{
	return _ee_addr + THERMO_EEPROM_LEN;
}

void Thermostat::setEEPROM(int addr)
{
	_ee_addr = addr;
}

void Thermostat::loadAll(void)
{
	int loc = _ee_addr;
	EEPROM.get(loc, _data[THERMO_DAY_MIN]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[THERMO_DAY_MAX]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[THERMO_NIGHT_MIN]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[THERMO_NIGHT_MAX]);
	loc += sizeof(float);
	_isEnable = (EEPROM.read(loc) & 1);
}

void Thermostat::saveAll(void)
{
	int loc = _ee_addr;
	EEPROM.put(loc, _data[THERMO_DAY_MIN]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[THERMO_DAY_MAX]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[THERMO_NIGHT_MIN]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[THERMO_NIGHT_MAX]);
	loc += sizeof(float);
	EEPROM.write(loc, (_isEnable ? 1 : 0));
}


bool Thermostat::runCycle(float value, float min, float max)
{
	bool working = false;
	if(_isWorking)
	{
		if(value >= max) working = false;
		else working = true;
	}  
	else
	{
		if(value <= min) working = true;
		else working = false;
	} 
	return working;
}

void Thermostat::activateRelay()
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

void Thermostat::desactivateRelay()
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
