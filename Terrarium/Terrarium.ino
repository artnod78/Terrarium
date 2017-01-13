#include <EEPROM.h>

#include <Wire.h>
#include <RTClib.h>

#include <LiquidCrystal.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <DHT.h>
#include <DHT_U.h>

#include <NewPing.h>

#include <DailyTimer.h>
#include <CyclicTimer.h>
#include <Reservoir.h>
#include <Thermostat.h>
#include <RetroLcd.h>

#include <ReadKey.h>

#include <Compteur.h>
#include <CompteurDate.h>
#include <CompteurHeure.h>
#include <CompteurSeconde.h>
#include <CompteurInt.h>
#include <CompteurBool.h>

#define KEY_PIN			0
#define ONE_WIRE_BUS	2
#define DHT_PIN			3
#define RETRO_PIN		10
#define ECHO_PIN		11
#define TRIGGER_PIN		12
#define BRUMI_PIN		13
#define LIGHT_PIN		15
#define PULVE_PIN		16
#define TAPIS_PIN		17

#define EEPROM_START	0

#define RETRO_SECOND_ON		15
#define TEMPERATURE_SECOND	5
#define DHT_SECOND			1
#define SONAR_SECOND		1

#define DHTTYPE			DHT11
#define MAX_DISTANCE	100

// CLOCK
RTC_DS1307 rtc;
DateTime now;

// LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
ReadKey keypad(KEY_PIN);

// DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
unsigned long last_temperature = 0;
float temperature = 0;

// DHT11
DHT dht(DHT_PIN, DHTTYPE);
unsigned long last_humidity = 0;
float humA = 0;
float tempA = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
unsigned long last_sonar = 0;
unsigned int cm = 0;

// OBJECTS
DailyTimer lumiere(LIGHT_PIN);
CyclicTimer pulverisateur(PULVE_PIN);
Reservoir reservoir;
Thermostat tapis(TAPIS_PIN);
Thermostat brumi(BRUMI_PIN);
RetroLcd retro(RETRO_PIN);

// COMPTEUR
Compteur cpt_MENU(MENU_HOME,			MENU_GENERAL);
Compteur cpt_LIGHT(DAILY_ON,			DAILY_RETURN);
Compteur cpt_PULVE(CYCLIC_DAY_ON,		CYCLIC_RETURN);
Compteur cpt_RESERVOIR(RESERVOIR_LIMIT,	RESERVOIR_RETURN);
Compteur cpt_TAPIS(THERMO_DAY_MIN,		THERMO_RETURN);
Compteur cpt_BRUMI(THERMO_DAY_MIN,		THERMO_RETURN);
Compteur cpt_CLOCK(CLOCK_DATE,			CLOCK_RETURN);
Compteur cpt_GENERAL(RETRO_TIME,		GENERAL_RETURN);

CompteurDate cpt_DATE;
CompteurHeure cpt_HEURE;
CompteurSeconde cpt_SECONDE;
CompteurInt cpt_INT;
CompteurBool cpt_BOOL;

// ### SENSORS ###
void mesurer_sondes()
{
	// DS18B20
	if ((now.unixtime() - last_temperature) >= TEMPERATURE_SECOND)
	{
		sensors.requestTemperatures();
		float temp_temperature = sensors.getTempCByIndex(0);
		if(temp_temperature > 0) temperature= temp_temperature;
		last_temperature = now.unixtime();
	}
	
	// DHT11/22
	if ((now.unixtime() - last_humidity) >=  DHT_SECOND)
	{
		sensors.requestTemperatures();
		float tmp_hum = dht.readHumidity();
		float tmp_temp = dht.readTemperature();
		if (isnan(tmp_hum) || isnan(tmp_temp))
		{
			return;
		}
		humA	= tmp_hum;
		tempA	= tmp_temp;
		last_humidity = now.unixtime();
	}
	
	// HC-SR04
	if ((now.unixtime() - last_sonar) >=  SONAR_SECOND)
	{
		unsigned int temp_cm = sonar.ping_cm();
		if ((temp_cm > 0) && (temp_cm < MAX_DISTANCE))
		{
			reservoir.run(temp_cm);
			cm = temp_cm;
		}
		last_sonar = now.unixtime();
	}
}

// ### HOME ###
void home_menu()
{
	// affichage
	lcd.setCursor(0, 0);
	if (now.hour() < 10) lcd.print(0);
	lcd.print(now.hour());
	lcd.print(':');
	if (now.minute() < 10) lcd.print(0);
	lcd.print(now.minute());
	lcd.print(':');
	if (now.second() < 10) lcd.print(0);
	lcd.print(now.second());
	
	lcd.setCursor(9, 0);
	if (reservoir.alert()) lcd.print("!!");
	else lcd.print("  ");
	
	lcd.setCursor(12, 0);
	lcd.print(lumiere.isEnable() ? 1 : 0);
	lcd.print(pulverisateur.isEnable() ? 1 : 0);
	lcd.print(tapis.isEnable() ? 1 : 0);
	lcd.print(brumi.isEnable() ? 1 : 0);
	
	lcd.setCursor(0, 1);
	lcd.print((int)temperature);
	lcd.print(" ");
	lcd.print((int)tempA);
	lcd.print(" ");
	lcd.print((int)humA);
	lcd.print(" ");
	if (cm < 10) lcd.print(0);
	lcd.print(cm);
	
	lcd.setCursor(12, 1);
	lcd.print(lumiere.isWorking() ? 1 : 0);
	lcd.print(pulverisateur.isWorking() ? 1 : 0);
	lcd.print(tapis.isWorking() ? 1 : 0);
	lcd.print(brumi.isWorking() ? 1 : 0);
}

// ### LUMIERE ###
void lumiere_home()
{
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Timer Lumiere");
}
void lumiere_conf()
{
	lcd.setCursor(0, 0);
	switch (cpt_LIGHT.index())
	{
		case DAILY_ON:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Timer ON");
			break;
		
		case DAILY_OFF:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Timer OFF");
			break;
		
		case DAILY_ENABLE:
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(lumiere.isEnable() ? "Oui" : "Non");
			break;
		
		case DAILY_RETURN:
			lcd.print("Retour");
			break;
		
		default:
			break;
	}
}
void lumiere_saisi()
{
	lcd.setCursor(0, 0);
	switch (cpt_LIGHT.index())
	{
		case DAILY_ON:
			if (cpt_HEURE.selected()) lcd.print("Heure ON");
			else lcd.print("Minute ON");
			break;
		
		case DAILY_OFF:
			if (cpt_HEURE.selected()) lcd.print("Heure OFF");
			else lcd.print("Minute OFF");
			break;
		
		default:
			break;
	}
	lcd.setCursor(0, 1);
	if (cpt_HEURE.heure() < 10) lcd.print("0");
	lcd.print(cpt_HEURE.heure());
	lcd.print(":");
	if (cpt_HEURE.minute() < 10) lcd.print("0");
	lcd.print(cpt_HEURE.minute());
}

// ### PULVERISATEUR ###
void pulve_home()
{
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Timer Pulve");
}
void pulve_conf()
{
	lcd.setCursor(0, 0);
	switch (cpt_PULVE.index()) {
		case CYCLIC_DAY_ON:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Day Time ON");
			break;
		
		case CYCLIC_DAY_OFF:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Day Time OFF");
			break;
		
		case CYCLIC_NIGHT_ON:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Night Time ON");
			break;
		
		case CYCLIC_NIGHT_OFF:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Night Time OFF");
			break;
		
		case CYCLIC_ENABLE:
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(pulverisateur.isEnable() ? "Oui" : "Non");
			break;
		
		case CYCLIC_RETURN:
			lcd.print("Retour");
			break;
			
		default:
			break;
	}
}
void pulve_saisi()
{
	unsigned int int_val = cpt_SECONDE.seconde();
	int increment = cpt_SECONDE.increment();
	lcd.setCursor(0, 0);
	switch (cpt_PULVE.index()) {
		case CYCLIC_DAY_ON:
			lcd.print("Day Time ON");
			break;
		
		case CYCLIC_DAY_OFF:
			lcd.print("Day Time OFF");
			break;
		
		case CYCLIC_NIGHT_ON:
			lcd.print("Night Time ON");
			break;
		
		case CYCLIC_NIGHT_OFF:
			lcd.print("Night Time OFF");
			break;
			
		default:
			break;
	}
	lcd.setCursor(0, 1);
	if (int_val > 999 & int_val < 10000) lcd.print("0");
	else if (int_val > 99 & int_val < 10000) lcd.print("00");
	else if (int_val > 9 & int_val < 10000) lcd.print("000");
	else if (int_val < 10000)lcd.print("0000");
	lcd.print(int_val);
	if (increment == 1) lcd.setCursor(15, 1);
	else if (increment == 60) lcd.setCursor(14, 1);
	else if (increment == 3600) lcd.setCursor(12, 1);
	lcd.print(increment);
}

// ### PULVERISATEUR ###
void reservoir_home()
{
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Taille reservoir");
}
void reservoir_conf()
{
	lcd.setCursor(0, 0);
	switch (cpt_RESERVOIR.index()) {
		case RESERVOIR_LIMIT:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Niveau limite");
			break;
		
		case RESERVOIR_ENABLE:
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(reservoir.isEnable() ? "Oui" : "Non");
			break;
		
		case RESERVOIR_RETURN:
			lcd.print("Retour");
			break;
			
		default:
			break;
	}
}
void reservoir_saisi()
{
	lcd.setCursor(0, 0);
	lcd.print("Distance limite");
	lcd.setCursor(0, 1);
	if (cpt_INT.value() < 10) lcd.print("0");
	lcd.print(cpt_INT.value());
}

// ### TAPIS ###
void tapis_home()
{
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Thermostat Tapis");
}
void tapis_conf()
{
	lcd.setCursor(0, 0);
	switch (cpt_TAPIS.index())
	{
		case THERMO_DAY_MIN:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Temp Min Jour");
			break;
		
		case THERMO_DAY_MAX:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Temp Max Jour");
			break;
		
		case THERMO_NIGHT_MIN:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Temp Min Nuit");
			break;
		
		case THERMO_NIGHT_MAX:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Temp Max Nuit");
			break;
		
		case THERMO_ENABLE:
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(tapis.isEnable() ? "Oui" : "Non");
			break;
		
		case THERMO_RETURN:
			lcd.print("Retour");
			break;
		
		default:
			break;
	}
}
void tapis_saisi()
{
	lcd.setCursor(0, 0);
	switch (cpt_TAPIS.index())
	{
		case THERMO_DAY_MIN:
			lcd.print("Temp Min Jour");
			break;
		
		case THERMO_DAY_MAX:
			lcd.print("Temp Max Jour");
			break;
		
		case THERMO_NIGHT_MIN:
			lcd.print("Temp Min Nuit");
			break;
		
		case THERMO_NIGHT_MAX:
			lcd.print("Temp Max Nuit");
			break;
		
		default:
			break;
	}
	lcd.setCursor(0, 1);
	if (cpt_INT.value() < 10) lcd.print("0");
	lcd.print(cpt_INT.value());
	lcd.print((char)223);
	lcd.print("C");
}

// ### BRUMI ###
void brumi_home()
{
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Hygrostat Brumi");
}
void brumi_conf()
{
	lcd.setCursor(0, 0);
	switch (cpt_BRUMI.index())
	{
		case THERMO_DAY_MIN:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Hygro Min Jour");
			break;
		
		case THERMO_DAY_MAX:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Hygro Max Jour");
			break;
		
		case THERMO_NIGHT_MIN:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Hygro Min Nuit");
			break;
		
		case THERMO_NIGHT_MAX:
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Hygro Max Nuit");
			break;
		
		case THERMO_ENABLE:
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(brumi.isEnable() ? "Oui" : "Non");
			break;
		
		case THERMO_RETURN:
			lcd.print("Retour");
			break;
		
		default:
			break;
	}
}
void brumi_saisi()
{
	lcd.setCursor(0, 0);
	switch (cpt_BRUMI.index())
	{
		case THERMO_DAY_MIN:
			lcd.print("Hygro Min Jour");
			break;
		
		case THERMO_DAY_MAX:
			lcd.print("Hygro Max Jour");
			break;
		
		case THERMO_NIGHT_MIN:
			lcd.print("Hygro Min Nuit");
			break;
		
		case THERMO_NIGHT_MAX:
			lcd.print("Hygro Max Nuit");
			break;
		
		default:
			break;
	}
	lcd.setCursor(0, 1);
	if (cpt_INT.value() < 10) lcd.print("0");
	lcd.print(cpt_INT.value());
	lcd.print("%");
}

// ### CLOCK ###
void save_clock(int param)
{
	switch (param)
	{
		case CLOCK_DATE:
			rtc.adjust(DateTime(cpt_DATE.annee(), cpt_DATE.mois(), cpt_DATE.jour(), now.hour(), now.minute(), now.second()));
			break;
		
		case CLOCK_HEURE:
			rtc.adjust(DateTime(now.year(), now.month(), now.day(), cpt_HEURE.heure(), cpt_HEURE.minute(), 0));
			break;
		
		default:
			break;
	}
}
void clock_home()
{
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Horloge");
}
void clock_conf()
{
	switch (cpt_CLOCK.index())
	{
		case CLOCK_DATE:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Date");
			break;
		
		case CLOCK_HEURE:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Heure");
			break;
		
		case CLOCK_RETURN:
			lcd.setCursor(0, 0);
			lcd.print("Retour");
			break;
		
		default:
			break;
	}
}
void clock_saisi()
{
	switch (cpt_CLOCK.index())
	{
		case CLOCK_DATE:
			lcd.setCursor(0, 0);
			switch (cpt_DATE.selected())
			{
				case YEAR:
					lcd.print("Annee");
					break;
		
				case MONTH:
					lcd.print("Mois");
					break;
		
				case DAY:
					lcd.print("Jour");
					break;
		
				default:
					break;
			}
			lcd.setCursor(0, 1);
			lcd.print(cpt_DATE.annee());
			lcd.print("/");
			if (cpt_DATE.mois() < 10) lcd.print(0);
			lcd.print(cpt_DATE.mois());
			lcd.print("/");
			if (cpt_DATE.jour() < 10) lcd.print(0);
			lcd.print(cpt_DATE.jour());
			break;
		
		case CLOCK_HEURE:
			lcd.setCursor(0, 0);
			if (cpt_HEURE.selected()) lcd.print("Heure");
			else lcd.print("Minute");
			lcd.setCursor(0, 1);
			if (cpt_HEURE.heure() < 10) lcd.print(0);
			lcd.print(cpt_HEURE.heure());
			lcd.print(":");
			if (cpt_HEURE.minute() < 10) lcd.print(0);
			lcd.print(cpt_HEURE.minute());
			break;
		
		default:
			break;
	}
}

// ### GENERAL ###
void resetArduino()
{
	for (int i = 0; i < retro.getNextEEPROM(); i++)
	{
		EEPROM.write(i, 0);
	}
	loadObjects();
	retro.setValue(RETRO_TIME, 15);
	retro.setValue(RETRO_BRIGHT, 95);
	retro.saveAll();
}
void general_home()
{
	lcd.setCursor(0, 0);
	lcd.print("Configuration");
	lcd.setCursor(0, 1);
	lcd.print("General");
}
void general_conf()
{
	switch (cpt_GENERAL.index())
	{
		case RETRO_TIME:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Duree Retro Lcd");
			break;
		
		case RETRO_BRIGHT:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Intensite Retro");
			break;
		
		case GENERAL_RESET:
			lcd.setCursor(0, 0);
			lcd.print("Reinitialiser");
			lcd.setCursor(0, 1);
			lcd.print("TerrAduino");
			break;
		
		case GENERAL_RETURN:
			lcd.setCursor(0, 0);
			lcd.print("Retour");
			break;
		
		default:
			break;
	}
}
void general_saisi()
{
	switch (cpt_GENERAL.index())
	{
		case RETRO_TIME:
			lcd.setCursor(0, 0);
			lcd.print("Duree Retro Lcd");
			lcd.setCursor(0, 1);
			if (cpt_SECONDE.seconde() < 10000) lcd.print("0");
			if (cpt_SECONDE.seconde() < 1000) lcd.print("0");
			if (cpt_SECONDE.seconde() < 100) lcd.print("0");
			if (cpt_SECONDE.seconde() < 10)lcd.print("0");
			lcd.print(cpt_SECONDE.seconde());
			if (cpt_SECONDE.increment() == 1) lcd.setCursor(15, 1);
			else if (cpt_SECONDE.increment() == 60) lcd.setCursor(14, 1);
			else if (cpt_SECONDE.increment() == 3600) lcd.setCursor(12, 1);
			lcd.print(cpt_SECONDE.increment());
			break;
		
		case RETRO_BRIGHT:
			lcd.setCursor(0, 0);
			lcd.print("Intensite Retro");
			lcd.setCursor(0, 1);
			if (cpt_INT.value() < 100) lcd.print("0");
			if (cpt_INT.value() < 10) lcd.print("0");
			lcd.print(cpt_INT.value());
			break;
		
		case GENERAL_RESET:
			lcd.setCursor(0, 0);
			lcd.print("Etes vous sure?");
			lcd.setCursor(0, 1);
			lcd.print(cpt_BOOL.value()? "Oui":"Non");
			break;
		
		default:
			break;
	}
}

// ### IHM ###
void nav_menu(int key)
{
	// increment le bon compteur
	if(cpt_MENU.isSelect() == false) 									// Menu principale
	{
		cpt_MENU.run(key); 												// increment
		if (cpt_MENU.isSelect() && (cpt_MENU.index() == MENU_HOME)) cpt_MENU.setSelect(false);
	}
	else 																// Menu configurations
	{
		switch (cpt_MENU.index())
		{		
			case MENU_LIGHT:
				if (cpt_LIGHT.isSelect() == false)						// Menu Lumiere
				{
					cpt_LIGHT.run(key); 								// increment
					if (cpt_LIGHT.isSelect())
					{
						if ( cpt_LIGHT.index() == DAILY_ENABLE)  		// switch actif - inactif
						{
							lumiere.enable(!lumiere.isEnable());
							lumiere.saveValue(DAILY_ENABLE);
							cpt_LIGHT.setSelect(false);
						}
						else if ( cpt_LIGHT.index() == DAILY_RETURN)	// retour arrière
						{
							cpt_LIGHT.setSelect(false);
							cpt_LIGHT.setIndex(DAILY_ON);
							cpt_MENU.setSelect(false);
						}
						else  											// prepare saisi Heure
						{
							cpt_HEURE.start(lumiere.getValue(cpt_LIGHT.index()));
						}
					}
				}
				else 													// Menu saisi Heure
				{
					cpt_HEURE.run(key);									// increment
					if (cpt_HEURE.isSelect())							// sauvegarde parametre
					{
						if(cpt_HEURE.time() != lumiere.getValue(cpt_LIGHT.index()) )
						{
							lumiere.setValue(cpt_LIGHT.index(), cpt_HEURE.time());
							lumiere.saveValue(cpt_LIGHT.index());
						}
						cpt_LIGHT.setSelect(false);
					}
				}
				break;
		
			case MENU_PULVE:
				if (cpt_PULVE.isSelect() == false)						// Menu Pulverisateur
				{
					cpt_PULVE.run(key); 								// increment
					if (cpt_PULVE.isSelect())
					{
						if ( cpt_PULVE.index() == CYCLIC_ENABLE)  		// switch actif - inactif
						{
							pulverisateur.enable(!pulverisateur.isEnable());
							pulverisateur.saveValue(CYCLIC_ENABLE);
							cpt_PULVE.setSelect(false);
						}
						else if ( cpt_PULVE.index() == CYCLIC_RETURN) 	// retour arrière
						{
							cpt_PULVE.setSelect(false);
							cpt_PULVE.setIndex(CYCLIC_DAY_ON);
							cpt_MENU.setSelect(false);
						}
						else  											// prepare saisi Seconde
						{
							cpt_SECONDE.start(pulverisateur.getValue(cpt_PULVE.index()));
						}
					}
				}
				else 													// Menu saisi Seconde
				{
					cpt_SECONDE.run(key);								// increment
					if (cpt_SECONDE.isSelect())							// sauvegarde parametre
					{
						if(cpt_SECONDE.seconde() != pulverisateur.getValue(cpt_PULVE.index()) )
						{
							pulverisateur.setValue(cpt_PULVE.index(), cpt_SECONDE.seconde());
							pulverisateur.saveValue(cpt_PULVE.index());
						}
						cpt_PULVE.setSelect(false);
					}
				}
				break;
		
			case MENU_RESERVOIR:
				if (cpt_RESERVOIR.isSelect() == false)					// Menu Reservoir
				{
					cpt_RESERVOIR.run(key); 							// increment
					if (cpt_RESERVOIR.isSelect())
					{
						if ( cpt_RESERVOIR.index() == RESERVOIR_LIMIT) 	// prepare saisi Int
						{
							cpt_INT = CompteurInt(0,99);
							cpt_INT.start(reservoir.getValue());
						}
						if ( cpt_RESERVOIR.index() == RESERVOIR_ENABLE)	// switch actif - inactif
						{
							reservoir.enable(!reservoir.isEnable());
							reservoir.saveValue(RESERVOIR_ENABLE);
							cpt_RESERVOIR.setSelect(false);
						}
						else if ( cpt_RESERVOIR.index() == RESERVOIR_RETURN) // retour arrière
						{
							cpt_RESERVOIR.setSelect(false);
							cpt_RESERVOIR.setIndex(RESERVOIR_LIMIT);
							cpt_MENU.setSelect(false);
						}
						
					}
				}
				else 													// Menu saisi Int
				{
					cpt_INT.run(key);									// increment
					if (cpt_INT.isSelect())								// sauvegarde parametre
					{
						if(cpt_INT.value() != reservoir.getValue() )
						{
							reservoir.setValue(cpt_INT.value());
							reservoir.saveValue(RESERVOIR_LIMIT);
						}
						cpt_RESERVOIR.setSelect(false);
					}
				}
				break;
				
			case MENU_TAPIS:
				if (cpt_TAPIS.isSelect() == false)						// Menu Tapis
				{
					cpt_TAPIS.run(key); 								// increment
					if (cpt_TAPIS.isSelect())
					{
						if ( cpt_TAPIS.index() == THERMO_ENABLE)  		// switch actif - inactif
						{
							tapis.enable(!tapis.isEnable());
							tapis.saveValue(cpt_TAPIS.index());
							cpt_TAPIS.setSelect(false);
						}
						else if ( cpt_TAPIS.index() == THERMO_RETURN) 	// retour arrière
						{
							cpt_TAPIS.setSelect(false);
							cpt_TAPIS.setIndex(THERMO_DAY_MIN);
							cpt_MENU.setSelect(false);
						}
						else											// prepare saisi Int
						{
							cpt_INT = CompteurInt(0, 40);
							cpt_INT.start(tapis.getValue(cpt_TAPIS.index()));
						}
					}
				}
				else 													// Menu saisi Int
				{
					cpt_INT.run(key);					 				// increment
					if (cpt_INT.isSelect())								// sauvegarde parametre
					{
						if(cpt_INT.value() != tapis.getValue(cpt_TAPIS.index()) )
						{
							tapis.setValue(cpt_TAPIS.index(), cpt_INT.value());
							tapis.saveValue(cpt_TAPIS.index());
						}
						cpt_TAPIS.setSelect(false);
					}
				}
				break;
		
			case MENU_BRUMI:
				if (cpt_BRUMI.isSelect() == false)						// Menu Brumisateur
				{
					cpt_BRUMI.run(key); 								// increment
					if (cpt_BRUMI.isSelect())
					{
						if ( cpt_BRUMI.index() == THERMO_ENABLE)  		// switch actif - inactif
						{
							brumi.enable(!brumi.isEnable());
							brumi.saveValue(cpt_BRUMI.index());
							cpt_BRUMI.setSelect(false);
						}
						else if ( cpt_BRUMI.index() == THERMO_RETURN) 	// retour arrière
						{
							cpt_BRUMI.setSelect(false);
							cpt_BRUMI.setIndex(THERMO_DAY_MIN);
							cpt_MENU.setSelect(false);
						}
						else											// prepare saisi Int
						{
							cpt_INT = CompteurInt(0, 100);
							cpt_INT.start(brumi.getValue(cpt_BRUMI.index()));
						}
					}
				}
				else 													// Menu saisi Int
				{
					cpt_INT.run(key); 									// increment
					if (cpt_INT.isSelect())								// sauvegarde parametre
					{
						if(cpt_INT.value() != brumi.getValue(cpt_BRUMI.index()) )
						{
							brumi.setValue(cpt_BRUMI.index(), cpt_INT.value());
							brumi.saveValue(cpt_BRUMI.index());
						}
						cpt_BRUMI.setSelect(false);
					}
				}
				break;
		
			case MENU_CLOCK:
				if (cpt_CLOCK.isSelect() == false)						// Menu Horloge
				{
					cpt_CLOCK.run(key);									// increment
					if (cpt_CLOCK.isSelect())
					{
						if (cpt_CLOCK.index() == CLOCK_DATE) 			// prepare saisi Date
						{
							cpt_DATE.start(now.year(), now.month(), now.day());
						}
						else if (cpt_CLOCK.index() == CLOCK_HEURE) 		// prepare saisi Heure
						{
							cpt_HEURE.start((now.hour() * 60) + now.minute());
						}
						else if ( cpt_CLOCK.index() == CLOCK_RETURN) 	// retour arrière
						{
							cpt_CLOCK.setSelect(false);
							cpt_CLOCK.setIndex(CLOCK_DATE);
							cpt_MENU.setSelect(false);
						}
					}
				}
				else 													// Menu saisi Horloge
				{
					switch (cpt_CLOCK.index())
					{
						case CLOCK_DATE:								// Saisi Date
							cpt_DATE.run(key);							// increment
							if (cpt_DATE.isSelect())					// sauvegarde parametre
							{
								save_clock(cpt_CLOCK.index());
								cpt_CLOCK.setSelect(false);
							}
							break;
							
						case CLOCK_HEURE:								// Saisi Heure
							cpt_HEURE.run(key);							// increment
							if (cpt_HEURE.isSelect())					// sauvegarde parametre
							{
								save_clock(cpt_CLOCK.index());
								cpt_CLOCK.setSelect(false);
							}
							break;
							
						default:
							break;
					}
				}
				break;
		
			case MENU_GENERAL:
				if (cpt_GENERAL.isSelect() == false)					// Menu General
				{
					cpt_GENERAL.run(key);								// increment
					if (cpt_GENERAL.isSelect())
					{
						if (cpt_GENERAL.index() == RETRO_TIME) 			// prepare saisi Heure
						{
							cpt_SECONDE.start(retro.getValue(RETRO_TIME));
						}
						else if (cpt_GENERAL.index() == RETRO_BRIGHT) 	// prepare saisi Int
						{
							cpt_INT = CompteurInt(0, 8);
							cpt_INT.start(retro.getValue(RETRO_BRIGHT));
							
						}
						else if (cpt_GENERAL.index() == GENERAL_RESET) 	// prepare confirmation
						{
							cpt_BOOL.start(false);
						}
						else if ( cpt_GENERAL.index() == GENERAL_RETURN) // retour arrière
						{
							cpt_GENERAL.setSelect(false);
							cpt_GENERAL.setIndex(RETRO_TIME);
							cpt_MENU.setSelect(false);
						}
					}
				}
				else 													// Menu saisi retro lcd
				{
					switch (cpt_GENERAL.index())
					{
						case RETRO_TIME:								// Saisi Date
							cpt_SECONDE.run(key);						// increment
							if (cpt_SECONDE.isSelect())					// sauvegarde parametre
							{
								if(cpt_SECONDE.seconde() != retro.getValue(RETRO_TIME) )
								{
									retro.setValue(RETRO_TIME, cpt_SECONDE.seconde());
									retro.saveValue(RETRO_TIME);
								}
								cpt_GENERAL.setSelect(false);
							}
							break;
							
						case RETRO_BRIGHT:								// Saisi Heure
							cpt_INT.run(key);							// increment
							retro.setValue(RETRO_BRIGHT, cpt_INT.value());
							if (cpt_INT.isSelect())						// sauvegarde parametre
							{
								if(cpt_INT.value() != retro.getValue(RETRO_BRIGHT) )
								{
									retro.setValue(RETRO_BRIGHT, cpt_INT.value());
									retro.saveValue(RETRO_BRIGHT);
								}
								cpt_GENERAL.setSelect(false);
							}
							break;
							
						case GENERAL_RESET:								// Saisi Heure
							cpt_BOOL.run(key);							// increment
							if (cpt_BOOL.isSelect())					// sauvegarde parametre
							{
								if(cpt_BOOL.value()) resetArduino();
								cpt_GENERAL.setSelect(false);
							}
							break;
							
						default:
							break;
					}
				}
				break;
				
			default:
				break;
		}
	}
}
void afficher_lcd(bool working)
{
	if (keypad.isPress()) lcd.clear();
	if(retro.isWorking() != working)
	{
		lcd.clear();		
		if(retro.isWorking() == false)
		{
			cpt_MENU.setIndex(MENU_HOME);
			cpt_MENU.setSelect(false);			
			cpt_LIGHT.setIndex(DAILY_ON);
			cpt_LIGHT.setSelect(false);
			cpt_PULVE.setIndex(CYCLIC_DAY_ON);
			cpt_PULVE.setSelect(false);
			cpt_RESERVOIR.setIndex(RESERVOIR_LIMIT);
			cpt_RESERVOIR.setSelect(false);
			cpt_TAPIS.setIndex(THERMO_DAY_MIN);
			cpt_TAPIS.setSelect(false);
			cpt_BRUMI.setIndex(THERMO_DAY_MIN);
			cpt_BRUMI.setSelect(false);
			cpt_CLOCK.setIndex(CLOCK_DATE);
			cpt_CLOCK.setSelect(false);
			cpt_GENERAL.setIndex(RETRO_TIME);
			cpt_GENERAL.setSelect(false);
		}
	}
	
	switch (cpt_MENU.index())
	{
		case MENU_HOME:
			home_menu();
			break;
	
		case MENU_LIGHT:
			if (cpt_MENU.isSelect() == false) lumiere_home();
			else if (cpt_LIGHT.isSelect() == false) lumiere_conf();
			else lumiere_saisi();
			break;
	
		case MENU_PULVE:
			if (cpt_MENU.isSelect() == false) pulve_home();
			else if (cpt_PULVE.isSelect() == false) pulve_conf();
			else pulve_saisi();
			break;
	
		case MENU_RESERVOIR:
			if (cpt_MENU.isSelect() == false) reservoir_home();
			else if (cpt_RESERVOIR.isSelect() == false) reservoir_conf();
			else reservoir_saisi();
			break;
	
		case MENU_TAPIS:
			if (cpt_MENU.isSelect() == false) tapis_home();
			else if (cpt_TAPIS.isSelect() == false) tapis_conf();
			else tapis_saisi();
			break;
	
		case MENU_BRUMI:
			if (cpt_MENU.isSelect() == false) brumi_home();
			else if (cpt_BRUMI.isSelect() == false) brumi_conf();
			else brumi_saisi();
			break;
	
		case MENU_CLOCK:
			if (cpt_MENU.isSelect() == false) clock_home();
			else if (cpt_CLOCK.isSelect() == false) clock_conf();
			else clock_saisi();
			break;
		
		case MENU_GENERAL:
			if (cpt_MENU.isSelect() == false) general_home();
			else if (cpt_GENERAL.isSelect() == false) general_conf();
			else general_saisi();
			break;
	
		default:
			break;
	}
}
void ihm()
{
	// saisi
	keypad.read(); 
	int key = keypad.key();
	
	// naviguation menu
	if(keypad.isPress()) nav_menu(key); 
	
	// gestion retro-eclairage
	bool working = retro.isWorking();
	retro.run(now.unixtime(), keypad.isPress());
	
	// afficahge lcd	
	afficher_lcd(working); 
}
void loadObjects()
{
	int loc = EEPROM_START;
	
	lumiere.setEEPROM(loc);
	lumiere.loadAll();
	loc = lumiere.getNextEEPROM();
	
	pulverisateur.setEEPROM(loc);
	pulverisateur.loadAll();
	loc = pulverisateur.getNextEEPROM();
	
	reservoir.setEEPROM(loc);
	reservoir.loadAll();
	loc = reservoir.getNextEEPROM();
	
	tapis.setEEPROM(loc);
	tapis.loadAll();
	loc = tapis.getNextEEPROM();
	
	brumi.setEEPROM(loc);
	brumi.loadAll();
	loc = brumi.getNextEEPROM();
	
	retro.setEEPROM(loc);
	retro.loadAll();
}

// ### MAIN ###
void setup()
{
  Wire.begin();
  rtc.begin();
  if (! rtc.isrunning())
  {
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  
  lcd.begin(16, 2);

  dht.begin();

  loadObjects();
}
void loop()
{
	mesurer_sondes();
	
	now = rtc.now();
	int nowInMinutes = (now.hour() * 60) + now.minute();
	
	lumiere.run(nowInMinutes);
	bool jour = lumiere.isWorking();
	
	if (reservoir.alert() == false) pulverisateur.run(now.unixtime(), jour);
	else if (pulverisateur.isWorking()) pulverisateur.stop();
	
	tapis.run(temperature, jour);
	
	brumi.run(humA, jour);
	
	ihm();
}