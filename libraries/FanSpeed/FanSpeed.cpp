#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include "FanSpeed.h"

FanSpeed::FanSpeed(int IO_Pin, int ee_addr)
{
	_IO_Pin        	= IO_Pin;
	_ee_addr		= ee_addr;
	_isWorking     	= false;
	_isEnable      	= false;
	pinMode(_IO_Pin,OUTPUT);
}


float FanSpeed::getValue(int type)
{
	return _data[type];
}

void FanSpeed::setValue(int type,float value)
{
	_data[type] = value;
}

void FanSpeed::saveValue(int type)
{
	int loc = _ee_addr + (sizeof(float) * type);
	switch (type)
	{
		case FAN_TEMP_DAY_MIN:
			EEPROM.put(loc, _data[FAN_TEMP_DAY_MIN]);
			break;
		
		case FAN_TEMP_DAY_MAX:
			EEPROM.put(loc, _data[FAN_TEMP_DAY_MAX]);
			break;
			
		case FAN_HUM_DAY_MIN:
			EEPROM.put(loc, _data[FAN_HUM_DAY_MIN]);
			break;
		
		case FAN_HUM_DAY_MAX:
			EEPROM.put(loc, _data[FAN_HUM_DAY_MAX]);
			break;
			
		case FAN_TEMP_NIGHT_MIN:
			EEPROM.put(loc, _data[FAN_TEMP_NIGHT_MIN]);
			break;
		
		case FAN_TEMP_NIGHT_MAX:
			EEPROM.put(loc, _data[FAN_TEMP_NIGHT_MAX]);
			break;
			
		case FAN_HUM_NIGHT_MIN:
			EEPROM.put(loc, _data[FAN_HUM_NIGHT_MIN]);
			break;
		
		case FAN_HUM_NIGHT_MAX:
			EEPROM.put(loc, _data[FAN_HUM_NIGHT_MAX]);
			break;
		
		case FAN_ENABLE:
			EEPROM.write(loc, (_isEnable ? 1 : 0));
			break;
		
		default:
			break;
	}
}


void FanSpeed::run(float currentTemp, float currentHum, bool lightMode)
{
	if(_isEnable)
	{
		float temp_min, temp_max, hum_min, hum_max;
		int new_speed = 0;
		
		if(lightMode)
		{
			temp_min = _data[FAN_TEMP_DAY_MIN];
			temp_max = _data[FAN_TEMP_DAY_MAX];
			hum_min = _data[FAN_HUM_DAY_MIN];
			hum_max = _data[FAN_HUM_DAY_MAX];
		}  
 		else
		{
			temp_min = _data[FAN_TEMP_NIGHT_MIN];
			temp_max = _data[FAN_TEMP_NIGHT_MAX];
			hum_min = _data[FAN_HUM_NIGHT_MIN];
			hum_max = _data[FAN_HUM_NIGHT_MAX];
		} 
		
		new_speed = runCycle(currentTemp, currentHum, temp_min, temp_max, hum_min, hum_max);
		
		if(new_speed != _isWorking)
		{
			set_speed(new_speed);
			_isWorking = new_speed;
		}
	}
}

int FanSpeed::isWorking(void)
{
	return _isWorking;
}

void FanSpeed::enable(bool value)
{
	if(value != _isEnable)
	{
		if(_isWorking != 0)
		{
			_isWorking = 0;
			set_speed(0);
		}
		_isEnable = value;
	}
}
bool FanSpeed::isEnable(void)
{
	return _isEnable;
}


int FanSpeed::getEEPROM(void)
{
	return _ee_addr;
}

int FanSpeed::getNextEEPROM(void)
{
	return _ee_addr + FAN_EEPROM_LEN;
}

void FanSpeed::setEEPROM(int addr)
{
	_ee_addr = addr;
}

void FanSpeed::loadAll(void)
{
	int loc = _ee_addr;
	EEPROM.get(loc, _data[FAN_TEMP_DAY_MIN]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[FAN_TEMP_DAY_MAX]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[FAN_HUM_DAY_MIN]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[FAN_HUM_DAY_MAX]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[FAN_TEMP_NIGHT_MIN]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[FAN_TEMP_NIGHT_MAX]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[FAN_HUM_NIGHT_MIN]);
	loc += sizeof(float);
	EEPROM.get(loc, _data[FAN_HUM_NIGHT_MAX]);
	loc += sizeof(float);
	_isEnable = (EEPROM.read(loc) & 1);
}

void FanSpeed::saveAll(void)
{
	int loc = _ee_addr;
	EEPROM.put(loc, _data[FAN_TEMP_DAY_MIN]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[FAN_TEMP_DAY_MAX]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[FAN_HUM_DAY_MIN]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[FAN_HUM_DAY_MAX]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[FAN_TEMP_NIGHT_MIN]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[FAN_TEMP_NIGHT_MAX]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[FAN_HUM_NIGHT_MIN]);
	loc += sizeof(float);
	EEPROM.put(loc, _data[FAN_HUM_NIGHT_MAX]);
	loc += sizeof(float);
	EEPROM.write(loc, (_isEnable ? 1 : 0));
}


int FanSpeed::runCycle(float temp, float hum, float temp_min, float temp_max, float hum_min, float hum_max)
{
	int speed;
	
	// high speed
	if((temp > temp_max) && !(hum < hum_min))
	{
		speed = 3;
	}
	// mid speed
	else if((temp >= temp_min && temp <= temp_max) && !(hum < hum_min))
	{
		speed = 2;
	}
	else if((temp > temp_max) && (hum < hum_min))
	{
		speed = 2;
	}
	// low speed
	else
	{
		speed = 1;
	}
	
	return speed;
}

void FanSpeed::set_speed(int speed)
{
	switch(speed)
	{
		case 0:
			analogWrite(_IO_Pin, FAN_SPEED_0);
			break;
		
		case 1:
			analogWrite(_IO_Pin, FAN_SPEED_1);
			break;
			
		case 2:
			analogWrite(_IO_Pin, FAN_SPEED_2);
			break;
		
		case 3:
			analogWrite(_IO_Pin, FAN_SPEED_3);
			break;
			
		default:
			analogWrite(_IO_Pin, FAN_SPEED_0);
			break;
	}
}