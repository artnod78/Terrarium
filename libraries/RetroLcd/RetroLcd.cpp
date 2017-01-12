#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "RetroLcd.h"

RetroLcd::RetroLcd(int IO_Pin, int ee_addr)
{
	_IO_Pin = IO_Pin;
	_ee_addr = ee_addr;
	_last_change = 0;
	_isWorking = false;
	analogWrite(_IO_Pin, 0);
}


int RetroLcd::getValue(int type)
{
	if(type == RETRO_BRIGHT)
	{
		if(_data[RETRO_BRIGHT] != 0) return (_data[RETRO_BRIGHT]+1)/32;
	}
	return _data[type];
}

void RetroLcd::setValue(int type, int value)
{
	if(type == RETRO_BRIGHT)
	{
		if(value == 0) _data[RETRO_BRIGHT] = 0;
		else _data[RETRO_BRIGHT] = (value *32)-1;
		analogWrite(_IO_Pin, _data[RETRO_BRIGHT]);
	}
	else _data[type] = value;
}

void RetroLcd::saveValue(int type)
{
	int loc = _ee_addr + (sizeof(int) * type);
	EEPROM.put(loc, _data[type]);
}


void RetroLcd::run(unsigned long currentUnixTime, bool keyPress)
{
	// refresh retro timer
	if(keyPress) _last_change = currentUnixTime;
	
	// find new state
	bool new_working = false;
	if ((currentUnixTime - _last_change) <  _data[RETRO_TIME]) new_working = true;
	
	// switch on / off
	if(new_working != _isWorking)
	{
		if(new_working) analogWrite(_IO_Pin, _data[RETRO_BRIGHT]);
		else analogWrite(_IO_Pin, 0);
		_isWorking = new_working;
	}
}

bool RetroLcd::isWorking(void)
{
	return _isWorking;
}


int RetroLcd::getEEPROM(void)
{
	return _ee_addr;
}

int RetroLcd::getNextEEPROM(void)
{
	return _ee_addr + RETRO_EEPROM_LEN;
}

void RetroLcd::setEEPROM(int addr)
{
	_ee_addr = addr;
}

void RetroLcd::loadAll(void)
{
	int loc = _ee_addr;
	EEPROM.get(loc, _data[RETRO_TIME]);
	loc += sizeof(int);
	EEPROM.get(loc, _data[RETRO_BRIGHT]);
}

void RetroLcd::saveAll(void)
{
	int loc = _ee_addr;
	EEPROM.put(loc, _data[RETRO_TIME]);
	loc += sizeof(int);
	EEPROM.put(loc, _data[RETRO_BRIGHT]);
}