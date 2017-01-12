#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "Reservoir.h"

Reservoir::Reservoir(int ee_addr)
{
	_ee_addr = ee_addr;
	_limit = 0;
	_alert = false;
	_isEnable = false;
}


void Reservoir::run(unsigned int currentValue)
{
	if(_isEnable)
	{
		if(currentValue >= _limit) _alert = true;
		else _alert = false;
	}
}

bool Reservoir::alert(void)
{
	return _alert;
}


int Reservoir::getValue()
{
	return _limit;
}

void Reservoir::setValue(int value)
{
	_limit = value;
}

void Reservoir::saveValue(int type)
{
	int loc = _ee_addr + (sizeof(int) * type);
	if (type == RESERVOIR_LIMIT) EEPROM.put(loc, _limit);
	else if (type == RESERVOIR_ENABLE) EEPROM.write(loc, _isEnable?1:0);
}


void Reservoir::enable(bool value)
{
	if((value != _isEnable) && (value == false)) _alert = false;
	_isEnable = value;
}

bool Reservoir::isEnable(void)
{
	return _isEnable;
}


int Reservoir::getEEPROM(void)
{
	return _ee_addr;
}

int Reservoir::getNextEEPROM(void)
{
	return _ee_addr + RESERVOIR_EEPROM_LEN;
}

void Reservoir::setEEPROM(int addr)
{
	_ee_addr = addr;
}

void Reservoir::loadAll(void)
{
	int loc = _ee_addr;
	EEPROM.get(loc, _limit);
	loc += sizeof(int);
	_isEnable = EEPROM.read(loc);
}

void Reservoir::saveAll(void)
{
	int loc = _ee_addr;
	EEPROM.put(loc, _limit);
	loc += sizeof(int);
	EEPROM.write(loc, _isEnable?1:0);
}