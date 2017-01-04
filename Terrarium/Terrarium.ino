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
#include <Thermostat.h>
#include <Hygrostat.h>

#include <ReadKey.h>

#include <Compteur.h>
#include <CompteurDate.h>
#include <CompteurHeure.h>
#include <CompteurSeconde.h>
#include <CompteurInt.h>


#define RETRO_PIN		10
#define RETRO_SECOND_ON	15

#define ONE_WIRE_BUS		2
#define TEMPERATURE_SECOND	15

#define DHT_PIN		3
#define DHTTYPE		DHT11
#define DHT_SECOND	5

#define TRIGGER_PIN		12
#define ECHO_PIN		11
#define MAX_DISTANCE	100
#define LVL_CRIT		20
#define SONAR_SECOND	5

#define LIGHT_PIN		15
#define EEPROM_LIGHT	0

#define PULVE_PIN		16
#define EEPROM_PULVE	5

#define TAPIS_PIN		17
#define EEPROM_TAPIS	22

#define BRUMI_PIN		13
#define EEPROM_BRUMI	31

#define KEY_PIN	0


// CLOCK
RTC_DS1307 rtc;
DateTime now;
int last_sec = 0;

// LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
ReadKey keypad(KEY_PIN);
unsigned long retro_start = 0;
bool retro_on = false;
int refresh_key = btnNONE;

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
unsigned int reservoir = 0;
bool alerte = false;

// OBJECTS
DailyTimer lumiere(LIGHT_PIN);
CyclicTimer pulverisateur(PULVE_PIN);
Thermostat tapis(TAPIS_PIN);
Hygrostat brumi(BRUMI_PIN);

// COMPTEUR
Compteur cpt_MENU(MENU_HOME,		MENU_CLOCK);
Compteur cpt_LIGHT(DAILY_ON,		LIGHT_RETURN);
Compteur cpt_PULVE(CYCLIC_DAY_ON,	PULVE_RETURN);
Compteur cpt_TAPIS(THERMOSTAT_DAY,	TAPIS_RETURN);
Compteur cpt_BRUMI(HYGRO_DAY_MIN,	BRUMI_RETURN);
Compteur cpt_CLOCK(CLOCK_DATE,		CLOCK_RETURN);

CompteurDate cpt_DATE;
CompteurHeure cpt_HEURE;
CompteurSeconde cpt_SECONDE;
CompteurInt cpt_INT;


// ###############
// ### SENSORS ###
// ###############
void mesurer_sondes()
{
  // DS18B20
  if ((now.unixtime() - last_temperature) >= TEMPERATURE_SECOND)
  {
    Serial.println("get sol");
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);
    last_temperature = now.unixtime();
  }

  // DHT11/22
  if ((now.unixtime() - last_humidity) >=  DHT_SECOND)
  {
    Serial.println("get air");
    sensors.requestTemperatures();
    float tmp_hum = dht.readHumidity();
    float tmp_temp = dht.readTemperature();
    if (isnan(tmp_hum) || isnan(tmp_temp))
    {
      Serial.println("DHT FAIL");
      return;
    }
    humA	= tmp_hum;
    tempA	= tmp_temp;
    last_humidity = now.unixtime();
  }

  // HC-SR04
  if ((now.unixtime() - last_sonar) >=  SONAR_SECOND)
  {
    Serial.println("get tank");
    unsigned int temp_cm = sonar.ping_cm();
    if (temp_cm > 0) reservoir = temp_cm;
    if (reservoir >= LVL_CRIT) alerte = true;
    else alerte = false;
    last_sonar = now.unixtime();
  }
}

// ############
// ### HOME ###
// ############
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
	if (alerte) lcd.print("!!");
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
	if ((LVL_CRIT - reservoir) < 10) lcd.print(0);
	lcd.print(LVL_CRIT - reservoir);
	lcd.print(" ");
	
	lcd.setCursor(12, 1);
	lcd.print(lumiere.isWorking() ? 1 : 0);
	lcd.print(pulverisateur.isWorking() ? 1 : 0);
	lcd.print(tapis.isWorking() ? 1 : 0);
	lcd.print(brumi.isWorking() ? 1 : 0);

	// saisi
	keypad.read();
	cpt_MENU.run(keypad.key());
	if (cpt_MENU.isSelect()) cpt_MENU.setSelect(false);
}

// ###############
// ### LUMIERE ###
// ###############
void lumiere_home()
{
	// affichage
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Timer Lumiere");
	
	// saisi
	keypad.read();
	cpt_MENU.run(keypad.key());
}
void lumiere_conf()
{
	// affichage
	switch (cpt_LIGHT.index())
	{
		case DAILY_ON:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Timer ON");
			break;
		
		case DAILY_OFF:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Timer OFF");
			break;
		
		case LIGHT_ENABLE:
			lcd.setCursor(0, 0);
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(lumiere.isEnable() ? "Oui" : "Non");
			break;
		
		case LIGHT_RETURN:
			lcd.setCursor(0, 0);
			lcd.print("Retour");
			break;
		
		default:
			break;
	}
	
	// saisi
	keypad.read();
	cpt_LIGHT.run(keypad.key());
	if (cpt_LIGHT.isSelect())
	{
		if (cpt_LIGHT.index() < LIGHT_ENABLE)
		{
			cpt_HEURE.start(lumiere.getValue(cpt_LIGHT.index()));
		}
		else if ( cpt_LIGHT.index() == LIGHT_ENABLE)
		{
			lumiere.enable(!lumiere.isEnable());
			lumiere.saveValue(EEPROM_LIGHT, cpt_LIGHT.index());
			cpt_LIGHT.setSelect(false);
		}
		else if ( cpt_LIGHT.index() == LIGHT_RETURN)
		{
			cpt_LIGHT.setSelect(false);
			cpt_LIGHT.setIndex(DAILY_ON);
			cpt_MENU.setSelect(false);
		}
	}
}
void lumiere_saisi()
{
	int heure  = cpt_HEURE.heure();
	int minute = cpt_HEURE.minute();
	
	// affichage
	lcd.setCursor(0, 0);
	switch (cpt_LIGHT.index())
	{
		case DAILY_ON:
			if (cpt_HEURE.heure_select()) lcd.print("Heure ON");
			else lcd.print("Minute ON");
			break;
		
		case DAILY_OFF:
			if (cpt_HEURE.heure_select()) lcd.print("Heure OFF");
			else lcd.print("Minute OFF");
			break;
		
		default:
			break;
	}
	lcd.setCursor(0, 1);
	if (heure < 10) lcd.print("0");
	lcd.print(heure);
	lcd.print(":");
	if (minute < 10) lcd.print("0");
	lcd.print(minute);
	
	// saisi
	keypad.read();
	cpt_HEURE.run(keypad.key());
	if (cpt_HEURE.isSelect())
	{
		lumiere.setValue(cpt_LIGHT.index(), cpt_HEURE.time());
		lumiere.saveValue(EEPROM_LIGHT, cpt_LIGHT.index());
		cpt_LIGHT.setSelect(false);
	}
}

// #####################
// ### PULVERISATEUR ###
// #####################
void pulve_home()
{
	// affichage
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Timer Pulve");
	
	// saisi
	keypad.read();
	cpt_MENU.run(keypad.key());
}
void pulve_conf()
{
	// affichage
	switch (cpt_PULVE.index()) {
		case CYCLIC_DAY_ON:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Day Time ON");
			break;
		
		case CYCLIC_DAY_OFF:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Day Time OFF");
			break;
		
		case CYCLIC_NIGHT_ON:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Night Time ON");
			break;
		
		case CYCLIC_NIGHT_OFF:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Night Time OFF");
			break;
		
		case PULVE_ENABLE:
			lcd.setCursor(0, 0);
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(pulverisateur.isEnable() ? "Oui" : "Non");
			break;
		
		case PULVE_RETURN:
			lcd.setCursor(0, 0);
			lcd.print("Retour");
			break;
			
		default:
			break;
	}
	
	// saisi
	keypad.read();
	cpt_PULVE.run(keypad.key());
	if (cpt_PULVE.isSelect())
	{
		if (cpt_PULVE.index() < PULVE_ENABLE)
		{
			cpt_SECONDE.start(pulverisateur.getValue(cpt_PULVE.index()));
		}
		else if ( cpt_PULVE.index() == PULVE_ENABLE)
		{
			pulverisateur.enable(!pulverisateur.isEnable());
			pulverisateur.saveValue(EEPROM_PULVE,cpt_PULVE.index());
			cpt_PULVE.setSelect(false);
		}
		else if ( cpt_PULVE.index() == PULVE_RETURN)
		{
			cpt_PULVE.setSelect(false);
			cpt_PULVE.setIndex(CYCLIC_DAY_ON);
			cpt_MENU.setSelect(false);
		}
	}
}
void pulve_saisi()
{
	unsigned int int_val = cpt_SECONDE.seconde();
	
	// affichage
	int increment = cpt_SECONDE.increment();
	switch (cpt_PULVE.index()) {
		case CYCLIC_DAY_ON:
			lcd.setCursor(0, 0);
			lcd.print("Day Time ON");
			break;
		
		case CYCLIC_DAY_OFF:
			lcd.setCursor(0, 0);
			lcd.print("Day Time OFF");
			break;
		
		case CYCLIC_NIGHT_ON:
			lcd.setCursor(0, 0);
			lcd.print("Night Time ON");
			break;
		
		case CYCLIC_NIGHT_OFF:
			lcd.setCursor(0, 0);
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
	
	// saisi
	keypad.read();
	cpt_SECONDE.run(keypad.key());
	if (cpt_SECONDE.isSelect())
	{
		pulverisateur.setValue(cpt_PULVE.index(), int_val);
		pulverisateur.saveValue(EEPROM_PULVE, cpt_PULVE.index());
		cpt_PULVE.setSelect(false);
	}
}

// #############
// ### TAPIS ###
// #############
void tapis_home()
{
	// affichage
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Thermostat Tapis");
	
	// saisi
	keypad.read();
	cpt_MENU.run(keypad.key());
}
void tapis_conf()
{
	// affichage
	switch (cpt_TAPIS.index()) {
		case THERMOSTAT_DAY:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Temperature Jour");
			break;
		
		case THERMOSTAT_NIGHT:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Temperature Nuit");
			break;
		
		case TAPIS_ENABLE:
			lcd.setCursor(0, 0);
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(tapis.isEnable() ? "Oui" : "Non");
			break;
		
		case TAPIS_RETURN:
			lcd.setCursor(0, 0);
			lcd.print("Retour");
			break;
		
		default:
			break;
	}
	
	// saisi
	keypad.read();
	cpt_TAPIS.run(keypad.key());
	if (cpt_TAPIS.isSelect())
	{
		if (cpt_TAPIS.index() < TAPIS_ENABLE)
		{
			cpt_INT.start(tapis.getValue(cpt_TAPIS.index()));
		}
		else if ( cpt_TAPIS.index() == TAPIS_ENABLE)
		{
			tapis.enable(!tapis.isEnable());
			tapis.saveValue(EEPROM_TAPIS, cpt_TAPIS.index());
			cpt_TAPIS.setSelect(false);
		}
		else if ( cpt_TAPIS.index() == TAPIS_RETURN)
		{
			cpt_TAPIS.setSelect(false);
			cpt_TAPIS.setIndex(THERMOSTAT_DAY);
			cpt_MENU.setSelect(false);
		}
	}
}
void tapis_saisi()
{
	unsigned int int_val = cpt_INT.value();
	
	// affichage
	switch (cpt_TAPIS.index())
	{
		case THERMOSTAT_DAY:
			lcd.setCursor(0, 0);
			lcd.print("Temperature Jour");
			break;
		
		case THERMOSTAT_NIGHT:
			lcd.setCursor(0, 0);
			lcd.print("Temperature Nuit");
			break;
		
		default:
			break;
	}
	lcd.setCursor(0, 1);
	if (int_val < 10) lcd.print("0");
	lcd.print(int_val);
	lcd.print((char)223);
	lcd.print("C");
	
	// saisi
	keypad.read();
	cpt_INT.run(keypad.key());
	if (cpt_INT.isSelect())
	{
		tapis.setValue(cpt_TAPIS.index(), int_val);
		tapis.saveValue(EEPROM_TAPIS, cpt_TAPIS.index());
		cpt_TAPIS.setSelect(false);
	}
}


// #############
// ### BRUMI ###
// #############
void brumi_home()
{
	// affichage
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Brumisateur");
	
	// saisi
	keypad.read();
	cpt_MENU.run(keypad.key());
}
void brumi_conf()
{
	// affichage
	switch (cpt_BRUMI.index()) {
		case HYGRO_DAY_MIN:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Hygro Min Jour");
			break;
		
		case HYGRO_DAY_MAX:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Hygro Max Jour");
			break;
		
		case HYGRO_NIGHT_MIN:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Hygro Min Nuit");
			break;
		
		case HYGRO_NIGHT_MAX:
			lcd.setCursor(0, 0);
			lcd.print("Configuration");
			lcd.setCursor(0, 1);
			lcd.print("Hygro Max Nuit");
			break;
		
		case BRUMI_ENABLE:
			lcd.setCursor(0, 0);
			lcd.print("Actif:");
			lcd.setCursor(0, 1);
			lcd.print(brumi.isEnable() ? "Oui" : "Non");
			break;
		
		case BRUMI_RETURN:
			lcd.setCursor(0, 0);
			lcd.print("Retour");
			break;
		
		default:
			break;
	}
	
	// saisi
	keypad.read();
	cpt_BRUMI.run(keypad.key());
	if (cpt_BRUMI.isSelect())
	{
		if (cpt_BRUMI.index() < BRUMI_ENABLE)
		{
			cpt_INT.start(brumi.getValue(cpt_BRUMI.index()));
		}
		else if ( cpt_BRUMI.index() == BRUMI_ENABLE)
		{
			brumi.enable(!brumi.isEnable());
			brumi.saveValue(EEPROM_BRUMI,cpt_BRUMI.index());
			cpt_BRUMI.setSelect(false);
		}
		else if ( cpt_BRUMI.index() == BRUMI_RETURN)
		{
			cpt_BRUMI.setSelect(false);
			cpt_BRUMI.setIndex(HYGRO_DAY_MIN);
			cpt_MENU.setSelect(false);
		}
	}
}
void brumi_saisi()
{
	unsigned int int_val = cpt_INT.value();
	
	// affichage
	switch (cpt_BRUMI.index())
	{
		case HYGRO_DAY_MIN:
			lcd.setCursor(0, 0);
			lcd.print("Hygro Min Jour");
			break;
		
		case HYGRO_DAY_MAX:
			lcd.setCursor(0, 0);
			lcd.print("Hygro Max Jour");
			break;
		
		case HYGRO_NIGHT_MIN:
			lcd.setCursor(0, 0);
			lcd.print("Hygro Min Nuit");
			break;
		
		case HYGRO_NIGHT_MAX:
			lcd.setCursor(0, 0);
			lcd.print("Hygro Max Nuit");
			break;
		
		default:
			break;
	}
	lcd.setCursor(0, 1);
	if (int_val < 10) lcd.print("0");
	lcd.print(int_val);
	lcd.print("%");
	
	// saisi
	keypad.read();
	cpt_INT.run(keypad.key());
	if (cpt_INT.isSelect())
	{
		brumi.setValue(cpt_BRUMI.index(), int_val);
		brumi.saveValue(EEPROM_BRUMI,cpt_BRUMI.index());
		cpt_BRUMI.setSelect(false);
	}
}


// #############
// ### CLOCK ###
// #############
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
	// affichage
	lcd.setCursor(0, 0);
	lcd.print("Configurer");
	lcd.setCursor(0, 1);
	lcd.print("Horloge");
	
	// saisi
	keypad.read();
	cpt_MENU.run(keypad.key());
}
void clock_conf()
{
	// affichage
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
	
	// saisi
	keypad.read();
	cpt_CLOCK.run(keypad.key());
	if (cpt_CLOCK.isSelect())
	{
		if (cpt_CLOCK.index() == CLOCK_DATE)
		{
			cpt_DATE.start(now.year(), now.month(), now.day());
		}
		else if (cpt_CLOCK.index() == CLOCK_HEURE)
		{
			cpt_HEURE.start((now.hour() * 60) + now.minute());
		}
		else if ( cpt_CLOCK.index() == CLOCK_RETURN)
		{
			cpt_CLOCK.setSelect(false);
			cpt_CLOCK.setIndex(CLOCK_DATE);
			cpt_MENU.setSelect(false);
		}
	}
}
void clock_saisi()
{
	switch (cpt_CLOCK.index())
	{
		case CLOCK_DATE:
			// affichage
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
		
			// saisi
			keypad.read();
			cpt_DATE.run(keypad.key());
			if (cpt_DATE.isSelect())
			{
				save_clock(cpt_CLOCK.index());
				cpt_CLOCK.setSelect(false);
			}
			break;
		
		case CLOCK_HEURE:
			// affichage
			lcd.setCursor(0, 0);
			if (cpt_HEURE.heure_select()) lcd.print("Heure");
			else lcd.print("Minute");
			lcd.setCursor(0, 1);
			if (cpt_HEURE.heure() < 10) lcd.print(0);
			lcd.print(cpt_HEURE.heure());
			lcd.print(":");
			if (cpt_HEURE.minute() < 10) lcd.print(0);
			lcd.print(cpt_HEURE.minute());
		
			// saisi
			keypad.read();
			cpt_HEURE.run(keypad.key());
			if (cpt_HEURE.isSelect())
			{
				save_clock(cpt_CLOCK.index());
				cpt_CLOCK.setSelect(false);
			}
			break;
		
		default:
			break;
	}
}

// ############
// ### MAIN ###
// ############
void configure_objects()
{
  lumiere.loadAll(EEPROM_LIGHT);
  pulverisateur.loadAll(EEPROM_PULVE);
  tapis.loadAll(EEPROM_TAPIS);
  brumi.loadAll(EEPROM_BRUMI);
  now = rtc.now();
  retro_start = now.unixtime();
}
void gestion_retro()
{
	// refresh retro timer
	if (keypad.key() != refresh_key)
	{
		retro_start = now.unixtime();
		refresh_key = keypad.key();
		lcd.clear();
	}

	// find new state
	bool working = false;
	if (retro_on)
	{
		if ((now.unixtime() - retro_start) >= RETRO_SECOND_ON) working = false;
		else working = true;
	}
	else
	{		
		if ((now.unixtime() - retro_start) <  RETRO_SECOND_ON) working = true;
		else working = false;
	}
	
	// switch on / off
	if(working != retro_on)
	{
		if(working)
		{
			analogWrite(RETRO_PIN, 128);
			lcd.clear();
		}
		else
		{
			analogWrite(RETRO_PIN, 0);
			lcd.clear();
			// retour à l'accueil
			cpt_MENU.setIndex(MENU_HOME);
			// reset tous les autres compteur
			cpt_LIGHT.setIndex(DAILY_ON);
			cpt_LIGHT.setSelect(false);
			cpt_PULVE.setIndex(CYCLIC_DAY_ON);
			cpt_PULVE.setSelect(false);
			cpt_TAPIS.setIndex(THERMOSTAT_DAY);
			cpt_TAPIS.setSelect(false);
			cpt_BRUMI.setIndex(HYGRO_DAY_MIN);
			cpt_BRUMI.setSelect(false);
			cpt_CLOCK.setIndex(CLOCK_DATE);
			cpt_CLOCK.setSelect(false);
		}
		retro_on = working;
	}  
}
void afficher_serial()
{
	Serial.print("*** ");
	if (now.hour() < 10)Serial.print(0);
	Serial.print(now.hour());
	Serial.print(":");
	if (now.minute() < 10)Serial.print(0);
	Serial.print(now.minute());
	Serial.print(":");
	if (now.second() < 10)Serial.print(0);
	Serial.print(now.second());
	Serial.println(" ***");
	Serial.print("Light:\t");
	Serial.print(lumiere.getValue(DAILY_ON));
	Serial.print("-");
	Serial.println(lumiere.getValue(DAILY_OFF));
	Serial.print("Pulve:\t");
	Serial.print(pulverisateur.getValue(CYCLIC_DAY_ON));
	Serial.print("-");
	Serial.print(pulverisateur.getValue(CYCLIC_DAY_OFF));
	Serial.print("-");
	Serial.print(pulverisateur.getValue(CYCLIC_NIGHT_ON));
	Serial.print("-");
	Serial.println(pulverisateur.getValue(CYCLIC_NIGHT_OFF));
	Serial.print("Tapis:\t");
	Serial.print(tapis.getValue(THERMOSTAT_DAY));
	Serial.print("-");
	Serial.println(tapis.getValue(THERMOSTAT_NIGHT));
	Serial.print("Brumi:\t");
	Serial.print(brumi.getValue(HYGRO_DAY_MIN));
	Serial.print("-");
	Serial.print(brumi.getValue(HYGRO_DAY_MAX));
	Serial.print("-");
	Serial.print(brumi.getValue(HYGRO_NIGHT_MIN));
	Serial.print("-");
	Serial.println(brumi.getValue(HYGRO_NIGHT_MAX));
}
void ihm()
{
	// gestion retro eclairage
	gestion_retro();
	
	// lcd keypad
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
	
		default:
			break;
	}
	
	// serial
	if (now.second() != last_sec)
	{
		afficher_serial();
		last_sec = now.second();
	}
}
void setup()
{
  Serial.begin(9600);
  Serial.println("****************");
  Serial.println("Setup");

  Serial.println("Init RTC");
  Wire.begin();
  rtc.begin();
  if (! rtc.isrunning())
  {
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  Serial.println("Init LCD");
  lcd.begin(16, 2);
  pinMode(RETRO_PIN, OUTPUT);

  Serial.println("Init DHT");
  dht.begin();

  Serial.println("Init OBJECTS");
  configure_objects();
}
void loop()
{
	now = rtc.now();
	
	mesurer_sondes();
	
	int nowInMinutes = (now.hour() * 60) + now.minute();
	lumiere.run(nowInMinutes);
	bool jour = lumiere.isWorking();
	
	pulverisateur.run(now.unixtime(), jour);
	
	if (alerte == false) tapis.run(temperature, jour);
	
	brumi.run(humA, jour);
	
	ihm();
}