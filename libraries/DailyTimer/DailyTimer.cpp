#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "DailyTimer.h"

DailyTimer::DailyTimer(int IO_Pin, int ee_addr, bool invertedRelay)
{
	_IO_Pin			= IO_Pin;
	_ee_addr		= ee_addr;
	_isWorking		= false;
	_isEnable		= false;
	_invertedRelay	= invertedRelay;
	pinMode(_IO_Pin,OUTPUT);
	digitalWrite(_IO_Pin,LOW);
}


int DailyTimer::getValue(int type)
{
	return _data[type];
}

void DailyTimer::setValue(int type, int minute)
{
	_data[type] = minute;
}

void DailyTimer::setValue(int type, int HH, int MM)
{
	_data[type] = (HH*60)+MM;
}

void DailyTimer::saveValue(int type)
{
	int loc = _ee_addr + (sizeof(int) * type);
	switch (type)
	{
		case DAILY_ON:
			EEPROM.put(loc, _data[DAILY_ON]);
			break;
		
		case DAILY_OFF:
			EEPROM.put(loc, _data[DAILY_OFF]);
			break;
		
		case DAILY_ENABLE:
			EEPROM.write(loc, (_isEnable ? 1 : 0));
			break;
		
		default:
			break;
	}
}


void DailyTimer::run(int currentTime)
{
	if(_isEnable)
	{		
		bool new_state = runCycle(currentTime, _data[DAILY_ON], _data[DAILY_OFF]);

		if(new_state != _isWorking)
		{
			if(new_state) activateRelay();
			else desactivateRelay();
			_isWorking = new_state;
		}
	}
}

bool DailyTimer::isWorking(void)
{
	return _isWorking;
}


void DailyTimer::enable(bool value)
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

bool DailyTimer::isEnable(void)
{
	return _isEnable;
}


int DailyTimer::getEEPROM(void)
{
	return _ee_addr;
}

int DailyTimer::getNextEEPROM(void)
{
	return _ee_addr + DAILY_EEPROM_LEN;
}

void DailyTimer::setEEPROM(int addr)
{
	_ee_addr = addr;
}

void DailyTimer::loadAll(void)
{
	int loc = _ee_addr;
	EEPROM.get(loc, _data[DAILY_ON]);
	loc += sizeof(int);
	EEPROM.get(loc, _data[DAILY_OFF]);
	loc += sizeof(int);
	_isEnable = EEPROM.read(loc) & 1;
}

void DailyTimer::saveAll(void)
{
	int loc = _ee_addr;
	EEPROM.put(loc, _data[DAILY_ON]);
	loc += sizeof(int);
	EEPROM.put(loc, _data[DAILY_OFF]);
	loc += sizeof(int);
	EEPROM.write(loc, (_isEnable ? 1 : 0));
}


bool DailyTimer::runCycle(int now, int start, int stop)
{
	bool working = false;
	if(start < stop) // operation le jour meme
	{
		if((now >= start) && (now < stop)) // jour
		{
			working = true;
		}
		else // nuit
		{
			working = false;
		}
	}  
	else if(start > stop)  // opération chevauche 2 jours 
	{
		if((now < start) && (now >= stop)) // nuit
		{
			working = false;
		}
		else // jour
		{
			working = true;
		}
	}
	return working;
}

void DailyTimer::activateRelay(void)
{
	if(_invertedRelay) digitalWrite(_IO_Pin,LOW);
	else digitalWrite(_IO_Pin,HIGH);
}

void DailyTimer::desactivateRelay(void)
{
	if(_invertedRelay) digitalWrite(_IO_Pin,HIGH);
	else digitalWrite(_IO_Pin,LOW);
}