#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "CyclicTimer.h"

CyclicTimer::CyclicTimer(int IO_Pin, bool invertedRelay)
{
	_IO_Pin			= IO_Pin;
	_isWorking     	= false;
	_isEnable      	= false;
	_lastChange	= 0;
	_invertedRelay	= invertedRelay;
	pinMode(_IO_Pin,OUTPUT);
}

void CyclicTimer::setValue(int type,unsigned long sec)
{
  _data[type] = sec;
}

void CyclicTimer::enable(bool value)
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

void CyclicTimer::run(unsigned long currentUnixTime, bool lightMode)
{
	if(_isEnable)
	{
		unsigned long duration_ON, duration_OFF;
		bool new_state = false;
		
		if(lightMode) // jour
		{
			duration_ON  = _data[CYCLIC_DAY_ON];
			duration_OFF = _data[CYCLIC_DAY_OFF];
		}  
		else // nuit
		{
			duration_ON  = _data[CYCLIC_NIGHT_ON];
			duration_OFF = _data[CYCLIC_NIGHT_OFF];
		} 
  
		new_state = runCycle(currentUnixTime, duration_ON, duration_OFF);

		if(new_state != _isWorking)
		{
			if(new_state) activateRelay();
			else desactivateRelay();
			_isWorking = new_state;
		}
	}
}
    
unsigned long CyclicTimer::getValue(int type)
{
  return _data[type];
}

bool CyclicTimer::isWorking(void)
{
  return _isWorking;
}

bool CyclicTimer::isEnable(void)
{
  return _isEnable;
}

void CyclicTimer::loadAll(int loc)
{
	EEPROM.get(loc, _data[CYCLIC_DAY_ON]);
	loc += sizeof(unsigned long);
	EEPROM.get(loc, _data[CYCLIC_DAY_OFF]);
	loc += sizeof(unsigned long);
	EEPROM.get(loc, _data[CYCLIC_NIGHT_ON]);
	loc += sizeof(unsigned long);
	EEPROM.get(loc, _data[CYCLIC_NIGHT_OFF]);
	loc += sizeof(unsigned long);
	_isEnable = (EEPROM.read(loc) & 1);
}

void CyclicTimer::saveAll(int loc)
{
	EEPROM.put(loc, _data[CYCLIC_DAY_ON]);
	loc += sizeof(unsigned long);
	EEPROM.put(loc, _data[CYCLIC_DAY_OFF]);
	loc += sizeof(unsigned long);
	EEPROM.put(loc, _data[CYCLIC_NIGHT_ON]);
	loc += sizeof(unsigned long);
	EEPROM.put(loc, _data[CYCLIC_NIGHT_OFF]);
	loc += sizeof(unsigned long);
	EEPROM.write(loc, (_isEnable ? 1 : 0));
}

void CyclicTimer::saveValue(int loc, int type)
{
	loc += sizeof(unsigned long) * type;
	switch (type)
	{
		case CYCLIC_DAY_ON:
			EEPROM.put(loc, _data[CYCLIC_DAY_ON]);
			break;
		
		case CYCLIC_DAY_OFF:
			EEPROM.put(loc, _data[CYCLIC_DAY_OFF]);
			break;
		
		case CYCLIC_NIGHT_ON:
			EEPROM.put(loc, _data[CYCLIC_NIGHT_ON]);
			break;
		
		case CYCLIC_NIGHT_OFF:
			EEPROM.put(loc, _data[CYCLIC_NIGHT_OFF]);
			break;
		
		case CYCLIC_ENABLE:
			EEPROM.write(loc, (_isEnable ? 1 : 0));
			break;
		
		default:
			break;
	}
}

bool CyclicTimer::runCycle(unsigned long currentUnixTime, unsigned long timeON, unsigned long timeOFF)
{
	bool working = false;
	if(_isWorking)
	{
		if((currentUnixTime - _lastChange) >= timeON)
		{
			_lastChange = currentUnixTime;
			working = false;
		}
		else
		{
			working = true;
		}
	}  
	else
	{
		if((currentUnixTime - _lastChange) >= + timeOFF)
		{
			_lastChange = currentUnixTime;
			working = true;
		}
		else
		{
			working = false;
		}
	} 
	return working;
}

void CyclicTimer::activateRelay(void)
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

void CyclicTimer::desactivateRelay(void)
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