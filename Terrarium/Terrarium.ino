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
#include <FanSpeed.h>
#include <RetroLcd.h>

#include <ReadKey.h>

#include <Compteur.h>
#include <CompteurDate.h>
#include <CompteurHeure.h>
#include <CompteurSeconde.h>
#include <CompteurBool.h>
#include <CompteurInt.h>
#include <CompteurFloat.h>

// Pins Assignment
#define LIGHT_PIN     2
#define PULVE_PIN     3
#define RETRO_PIN     10
#define VENTILO_PIN   11
#define TAPIS_PIN     12
#define ONE_WIRE_BUS  13
#define KEY_PIN       14
#define DHT_PIN       15
#define ECHO_PIN      16
#define TRIGGER_PIN   17

// Time between measure
#define TEMPERATURE_SECOND  5
#define DHT_SECOND          1
#define SONAR_SECOND        1

#define EEPROM_START	0
#define DHTTYPE			DHT22
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

// DHT22
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
FanSpeed ventilo(VENTILO_PIN);
RetroLcd retro(RETRO_PIN);

// COUNTER
Compteur menu(MENU_HOME, MENU_GENERAL);
Compteur sousMenu;

CompteurDate saisi_DATE;
CompteurHeure saisi_HEURE;
CompteurSeconde saisi_SECONDE;
CompteurBool saisi_BOOL;
CompteurInt saisi_INT;
CompteurFloat saisi_FLOAT;

// ### HOME ###
void home_menu()
{
  // Print Time
  lcd.setCursor(0, 0);
  if (now.hour() < 10) lcd.print(0);
  lcd.print(now.hour());
  lcd.print(':');
  if (now.minute() < 10) lcd.print(0);
  lcd.print(now.minute());
  lcd.print(':');
  if (now.second() < 10) lcd.print(0);
  lcd.print(now.second());

  // objects state
  // - = disable
  // 0 = enbale and off
  // 1 = enable and on
  lcd.setCursor(11, 0);
  if (lumiere.isEnable() == false) lcd.print("-");
  else lcd.print(lumiere.isWorking() ? 1 : 0);
  if (pulverisateur.isEnable() == false) lcd.print("-");
  else lcd.print(pulverisateur.isWorking() ? 1 : 0);
  if (reservoir.isEnable() == false) lcd.print("-");
  else lcd.print(reservoir.alert() ? 1 : 0);
  if (tapis.isEnable() == false) lcd.print("-");
  else lcd.print(tapis.isWorking() ? 1 : 0);
  if (ventilo.isEnable() == false) lcd.print("-");
  else lcd.print(ventilo.isWorking());

  // Sensors values
  lcd.setCursor(0, 1);
  lcd.print((int)temperature);
  lcd.print(" ");
  lcd.print((int)tempA);
  lcd.print(" ");
  lcd.print((int)humA);
  lcd.print(" ");
  // Empty water tank Alert
  if (reservoir.alert())
  {
    lcd.print("ALERTE");
  }
  else
  {
    if (cm < 10) lcd.print(0);
    lcd.print(cm);
    lcd.print("    ");
  }
}

// ### LIGHT ###
void lumiere_home()
{
  lcd.setCursor(0, 0);
  lcd.print("Timer Lumiere");
}
void lumiere_conf()
{
  lcd.setCursor(0, 0);
  switch (sousMenu.index())
  {
    case DAILY_ON:
      lcd.print("Timer ON");
      break;

    case DAILY_OFF:
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
  switch (sousMenu.index())
  {
    case DAILY_ON:
      if (saisi_HEURE.selected()) lcd.print("Heure ON");
      else lcd.print("Minute ON");
      break;

    case DAILY_OFF:
      if (saisi_HEURE.selected()) lcd.print("Heure OFF");
      else lcd.print("Minute OFF");
      break;

    default:
      break;
  }
  lcd.setCursor(0, 1);
  if (saisi_HEURE.heure() < 10) lcd.print("0");
  lcd.print(saisi_HEURE.heure());
  lcd.print(":");
  if (saisi_HEURE.minute() < 10) lcd.print("0");
  lcd.print(saisi_HEURE.minute());
}

// ### RAINNING ###
void pulve_home()
{
  lcd.setCursor(0, 0);
  lcd.print("Timer Pulve");
}
void pulve_conf()
{
  lcd.setCursor(0, 0);
  switch (sousMenu.index()) {
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
  unsigned int int_val = saisi_SECONDE.seconde();
  int increment = saisi_SECONDE.increment();
  lcd.setCursor(0, 0);
  switch (sousMenu.index()) {
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

// ### TANK ###
void reservoir_home()
{
  lcd.setCursor(0, 0);
  lcd.print("Limite reservoir");
}
void reservoir_conf()
{
  lcd.setCursor(0, 0);
  switch (sousMenu.index()) {
    case RESERVOIR_LIMIT:
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
  lcd.print("Niveau limite");
  lcd.setCursor(0, 1);
  if (saisi_INT.value() < 10) lcd.print("0");
  lcd.print(saisi_INT.value());
}

// ### TEMP ###
void temp_home()
{
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
}
void temp_conf()
{
  lcd.setCursor(0, 0);
  switch (sousMenu.index())
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

    case TEMP_RETURN:
      lcd.print("Retour");
      break;

    default:
      break;
  }
}
void temp_saisi()
{
  lcd.setCursor(0, 0);
  if (saisi_FLOAT.selected()) lcd.print("Entier ");
  else lcd.print("Decimal ");
  switch (sousMenu.index())
  {
    case THERMO_DAY_MIN:
      lcd.print("Min Jour");
      break;

    case THERMO_DAY_MAX:
      lcd.print("Max Jour");
      break;

    case THERMO_NIGHT_MIN:
      lcd.print("Min Nuit");
      break;

    case THERMO_NIGHT_MAX:
      lcd.print("Max Nuit");
      break;

    default:
      break;
  }
  lcd.setCursor(0, 1);
  if (saisi_FLOAT.entier() < 10) lcd.print("0");
  lcd.print(saisi_FLOAT.entier());
  lcd.print(".");
  if (saisi_FLOAT.decimal() < 10) lcd.print("0");
  lcd.print(saisi_FLOAT.decimal());
}

// ### HUM ###
void hum_home()
{
  lcd.setCursor(0, 0);
  lcd.print("Humidite");
}
void hum_conf()
{
  lcd.setCursor(0, 0);
  switch (sousMenu.index())
  {
    case HUM_DAY_MIN:
      lcd.print("hum Min Jour");
      break;

    case HUM_DAY_MAX:
      lcd.print("hum Max Jour");
      break;

    case HUM_NIGHT_MIN:
      lcd.print("hum Min Nuit");
      break;

    case HUM_NIGHT_MAX:
      lcd.print("hum Max Nuit");
      break;

    case HUM_RETURN:
      lcd.print("Retour");
      break;

    default:
      break;
  }
}
void hum_saisi()
{
  lcd.setCursor(0, 0);
  if (saisi_FLOAT.selected()) lcd.print("Entier ");
  else lcd.print("Decimal ");
  switch (sousMenu.index())
  {
    case HUM_DAY_MIN:
      lcd.print("Hmin Jour");
      break;

    case HUM_DAY_MAX:
      lcd.print("Hmax Jour");
      break;

    case HUM_NIGHT_MIN:
      lcd.print("Hmin Nuit");
      break;

    case HUM_NIGHT_MAX:
      lcd.print("Hmax Nuit");
      break;

    default:
      break;
  }
  lcd.setCursor(0, 1);
  if (saisi_FLOAT.entier() < 10) lcd.print("0");
  lcd.print(saisi_FLOAT.entier());
  lcd.print(".");
  if (saisi_FLOAT.decimal() < 10) lcd.print("0");
  lcd.print(saisi_FLOAT.decimal());
}

// ### THERMO ###
void thermo_home()
{
  lcd.setCursor(0, 0);
  lcd.print("Thermostat");
}
void thermo_conf()
{
  lcd.setCursor(0, 0);
  switch (sousMenu.index())
  {
    case THERMO_HEAT:
      lcd.print("Chauffage Actif");
      lcd.setCursor(0, 1);
      lcd.print(tapis.isEnable() ? "Oui" : "Non");
      break;

    case THERMO_FAN:
      lcd.print("Ventilo Actif");
      lcd.setCursor(0, 1);
      lcd.print(ventilo.isEnable() ? "Oui" : "Non");
      break;

    case THERMO_RETURN:
      lcd.print("Retour");
      break;

    default:
      break;
  }
}

// ### CLOCK ###
void save_clock(int param)
{
  switch (param)
  {
    case CLOCK_DATE:
      rtc.adjust(DateTime(saisi_DATE.annee(), saisi_DATE.mois(), saisi_DATE.jour(), now.hour(), now.minute(), now.second()));
      break;

    case CLOCK_HEURE:
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), saisi_HEURE.heure(), saisi_HEURE.minute(), 0));
      break;

    default:
      break;
  }
}
void clock_home()
{
  lcd.setCursor(0, 0);
  lcd.print("Horloge");
}
void clock_conf()
{
  lcd.setCursor(0, 0);
  switch (sousMenu.index())
  {
    case CLOCK_DATE:
      lcd.print("Date");
      break;

    case CLOCK_HEURE:
      lcd.print("Heure");
      break;

    case CLOCK_RETURN:
      lcd.print("Retour");
      break;

    default:
      break;
  }
}
void clock_saisi()
{
  switch (sousMenu.index())
  {
    case CLOCK_DATE:
      lcd.setCursor(0, 0);
      switch (saisi_DATE.selected())
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
      lcd.print(saisi_DATE.annee());
      lcd.print("/");
      if (saisi_DATE.mois() < 10) lcd.print(0);
      lcd.print(saisi_DATE.mois());
      lcd.print("/");
      if (saisi_DATE.jour() < 10) lcd.print(0);
      lcd.print(saisi_DATE.jour());
      break;

    case CLOCK_HEURE:
      lcd.setCursor(0, 0);
      if (saisi_HEURE.selected()) lcd.print("Heure");
      else lcd.print("Minute");
      lcd.setCursor(0, 1);
      if (saisi_HEURE.heure() < 10) lcd.print(0);
      lcd.print(saisi_HEURE.heure());
      lcd.print(":");
      if (saisi_HEURE.minute() < 10) lcd.print(0);
      lcd.print(saisi_HEURE.minute());
      break;

    default:
      break;
  }
}

// ### GENERAL ###
void resetArduino()
{
  // reset lumiere
  if (lumiere.getValue(DAILY_ON) != 0)
  {
    lumiere.setValue(DAILY_ON, 0);
    lumiere.saveValue(DAILY_ON);
  }
  if (lumiere.getValue(DAILY_OFF) != 0)
  {
    lumiere.setValue(DAILY_OFF, 0);
    lumiere.saveValue(DAILY_OFF);
  }
  if (lumiere.isEnable())
  {
    lumiere.enable(false);
    lumiere.saveValue(DAILY_ENABLE);
  }
  // reset pulverisateur
  if (pulverisateur.getValue(CYCLIC_DAY_ON) != 0)
  {
    pulverisateur.setValue(CYCLIC_DAY_ON, 0);
    pulverisateur.saveValue(CYCLIC_DAY_ON);
  }
  if (pulverisateur.getValue(CYCLIC_DAY_OFF) != 0)
  {
    pulverisateur.setValue(CYCLIC_DAY_OFF, 0);
    pulverisateur.saveValue(CYCLIC_DAY_OFF);
  }
  if (pulverisateur.getValue(CYCLIC_NIGHT_ON) != 0)
  {
    pulverisateur.setValue(CYCLIC_NIGHT_ON, 0);
    pulverisateur.saveValue(CYCLIC_NIGHT_ON);
  }
  if (pulverisateur.getValue(CYCLIC_NIGHT_OFF) != 0)
  {
    pulverisateur.setValue(CYCLIC_NIGHT_OFF, 0);
    pulverisateur.saveValue(CYCLIC_NIGHT_OFF);
  }
  if (pulverisateur.isEnable())
  {
    pulverisateur.enable(false);
    pulverisateur.saveValue(CYCLIC_ENABLE);
  }
  // reset reservoir
  if (reservoir.getValue() != 0)
  {
    reservoir.setValue(0);
    reservoir.saveValue(RESERVOIR_LIMIT);
  }
  if (reservoir.isEnable())
  {
    reservoir.enable(false);
    reservoir.saveValue(RESERVOIR_ENABLE);
  }
  // reset tapis
  if (tapis.getValue(THERMO_DAY_MIN) != 0)
  {
    tapis.setValue(THERMO_DAY_MIN, 0);
    tapis.saveValue(THERMO_DAY_MIN);
  }
  if (tapis.getValue(THERMO_DAY_MAX) != 0)
  {
    tapis.setValue(THERMO_DAY_MAX, 0);
    tapis.saveValue(THERMO_DAY_MAX);
  }
  if (tapis.getValue(THERMO_NIGHT_MIN) != 0)
  {
    tapis.setValue(THERMO_NIGHT_MIN, 0);
    tapis.saveValue(THERMO_NIGHT_MIN);
  }
  if (tapis.getValue(THERMO_NIGHT_MAX) != 0)
  {
    tapis.setValue(THERMO_NIGHT_MAX, 0);
    tapis.saveValue(THERMO_NIGHT_MAX);
  }
  if (tapis.isEnable())
  {
    tapis.enable(false);
    tapis.saveValue(THERMO_ENABLE);
  }
  // reset ventilo
  if (ventilo.getValue(FAN_TEMP_DAY_MIN) != 0)
  {
    ventilo.setValue(FAN_TEMP_DAY_MIN, 0);
    ventilo.saveValue(FAN_TEMP_DAY_MIN);
  }
  if (ventilo.getValue(FAN_TEMP_DAY_MAX) != 0)
  {
    ventilo.setValue(FAN_TEMP_DAY_MAX, 0);
    ventilo.saveValue(FAN_TEMP_DAY_MAX);
  }
  if (ventilo.getValue(FAN_HUM_DAY_MIN) != 0)
  {
    ventilo.setValue(FAN_HUM_DAY_MIN, 0);
    ventilo.saveValue(FAN_HUM_DAY_MIN);
  }
  if (ventilo.getValue(FAN_HUM_DAY_MAX) != 0)
  {
    ventilo.setValue(FAN_HUM_DAY_MAX, 0);
    ventilo.saveValue(FAN_HUM_DAY_MAX);
  }
  if (ventilo.getValue(FAN_TEMP_NIGHT_MIN) != 0)
  {
    ventilo.setValue(FAN_TEMP_NIGHT_MIN, 0);
    ventilo.saveValue(FAN_TEMP_NIGHT_MIN);
  }
  if (ventilo.getValue(FAN_TEMP_NIGHT_MAX) != 0)
  {
    ventilo.setValue(FAN_TEMP_NIGHT_MAX, 0);
    ventilo.saveValue(FAN_TEMP_NIGHT_MAX);
  }
  if (ventilo.getValue(FAN_HUM_NIGHT_MIN) != 0)
  {
    ventilo.setValue(FAN_HUM_NIGHT_MIN, 0);
    ventilo.saveValue(FAN_HUM_NIGHT_MIN);
  }
  if (ventilo.getValue(FAN_HUM_NIGHT_MAX) != 0)
  {
    ventilo.setValue(FAN_HUM_NIGHT_MAX, 0);
    ventilo.saveValue(FAN_HUM_NIGHT_MAX);
  }
  if (ventilo.isEnable())
  {
    ventilo.enable(false);
    ventilo.saveValue(FAN_ENABLE);
  }
  // reset retro lcd
  if (retro.getValue(RETRO_TIME) != 15)
  {
    retro.setValue(RETRO_TIME, 15);
    retro.saveValue(RETRO_TIME);
  }
  if (retro.getValue(RETRO_BRIGHT) != 3)
  {
    retro.setValue(RETRO_BRIGHT, 3);
    retro.saveValue(RETRO_BRIGHT);
  }
}
void general_home()
{
  lcd.setCursor(0, 0);
  lcd.print("General");
}
void general_conf()
{
  lcd.setCursor(0, 0);
  switch (sousMenu.index())
  {
    case RETRO_TIME:
      lcd.print("Duree Retro Lcd");
      break;

    case RETRO_BRIGHT:
      lcd.print("Intensite Retro");
      break;

    case GENERAL_RESET:
      lcd.print("Reinitialiser");
      lcd.setCursor(0, 1);
      lcd.print("Parametres");
      break;

    case GENERAL_RETURN:
      lcd.print("Retour");
      break;

    default:
      break;
  }
}
void general_saisi()
{
  switch (sousMenu.index())
  {
    case RETRO_TIME:
      lcd.setCursor(0, 0);
      lcd.print("Duree Retro Lcd");
      lcd.setCursor(0, 1);
      if (saisi_SECONDE.seconde() < 10000) lcd.print("0");
      if (saisi_SECONDE.seconde() < 1000) lcd.print("0");
      if (saisi_SECONDE.seconde() < 100) lcd.print("0");
      if (saisi_SECONDE.seconde() < 10)lcd.print("0");
      lcd.print(saisi_SECONDE.seconde());
      if (saisi_SECONDE.increment() == 1) lcd.setCursor(15, 1);
      else if (saisi_SECONDE.increment() == 60) lcd.setCursor(14, 1);
      else if (saisi_SECONDE.increment() == 3600) lcd.setCursor(12, 1);
      lcd.print(saisi_SECONDE.increment());
      break;

    case RETRO_BRIGHT:
      lcd.setCursor(0, 0);
      lcd.print("Intensite Retro");
      lcd.setCursor(0, 1);
      if (saisi_INT.value() < 100) lcd.print("0");
      if (saisi_INT.value() < 10) lcd.print("0");
      lcd.print(saisi_INT.value());
      break;

    case GENERAL_RESET:
      lcd.setCursor(0, 0);
      lcd.print("Etes vous sure?");
      lcd.setCursor(0, 1);
      lcd.print(saisi_BOOL.value() ? "Oui" : "Non");
      break;

    default:
      break;
  }
}

// ### MAIN FUNCTION ###
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

  ventilo.setEEPROM(loc);
  ventilo.loadAll();
  loc = ventilo.getNextEEPROM();

  retro.setEEPROM(loc);
  retro.loadAll();
}
void measure()
{
  // DS18B20
  if ((now.unixtime() - last_temperature) >= TEMPERATURE_SECOND)
  {
    sensors.requestTemperatures();
    float temp_temperature = sensors.getTempCByIndex(0);
    if (temp_temperature > 0) temperature = temp_temperature;
    last_temperature = now.unixtime();
  }

  // DHT22
  if ((now.unixtime() - last_humidity) >=  DHT_SECOND)
  {
    float tmp_hum = dht.readHumidity();
    float tmp_temp = dht.readTemperature();
    if (isnan(tmp_hum) || isnan(tmp_temp))
    {
      return;
    }
    humA  = tmp_hum;
    tempA = tmp_temp;
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
void runObjects()
{
  // Daily Timer
  int nowInMinutes = (now.hour() * 60) + now.minute();
  lumiere.run(nowInMinutes);
  bool jour = lumiere.isWorking();
  // Cyclic Timer with Tank Alert
  if (reservoir.alert() == false) pulverisateur.run(now.unixtime(), jour);
  else if (pulverisateur.isWorking()) pulverisateur.stop();
  // Thermostat
  tapis.run(temperature, jour);
  // Fan Speed
  ventilo.run(tempA, humA, jour);
}
void nav_menu()
{
  if (keypad.isPress())
  {
    // Get key from keypad
    int key = keypad.key();
    // Main Menu
    if (menu.isSelect() == false)
    {
      // Menu increment or select
      menu.run(key);
      // Initialize sub-menu if selected
      if (menu.isSelect())
      {
        switch (menu.index())
        {
          case MENU_HOME:
            menu.setSelect(false);
            break;

          case MENU_LIGHT:
            sousMenu = Compteur(DAILY_ON, DAILY_RETURN);
            break;

          case MENU_PULVE:
            sousMenu = Compteur(CYCLIC_DAY_ON, CYCLIC_RETURN);
            break;

          case MENU_RESERVOIR:
            sousMenu = Compteur(RESERVOIR_LIMIT, RESERVOIR_RETURN);
            break;

          case MENU_TEMP:
            sousMenu = Compteur(THERMO_DAY_MIN, TEMP_RETURN);
            break;

          case MENU_HUM:
            sousMenu = Compteur(HUM_DAY_MIN, HUM_RETURN);
            break;

          case MENU_THERMO:
            sousMenu = Compteur(THERMO_HEAT, THERMO_RETURN);
            break;

          case MENU_CLOCK:
            sousMenu = Compteur(CLOCK_DATE, CLOCK_RETURN);
            break;

          case MENU_GENERAL:
            sousMenu = Compteur(RETRO_TIME, GENERAL_RETURN);
            break;

          default :
            break;
        }
      }
    }
    // Sub-Menu
    else
    {
      // Sub-Menu Increment
      if (sousMenu.isSelect() == false)
      {
        // Sun-Menu increment or select
        sousMenu.run(key);
        // Action on Sub-Menu
        if (sousMenu.isSelect())
        {
          switch (menu.index())
          {
            case MENU_LIGHT:
              // switch enable - disable
              if (sousMenu.index() == DAILY_ENABLE)
              {
                lumiere.enable(!lumiere.isEnable());
                lumiere.saveValue(DAILY_ENABLE);
                sousMenu.setSelect(false);
              }
              // Going back
              else if (sousMenu.index() == DAILY_RETURN)
              {
                sousMenu.setSelect(false);
                menu.setSelect(false);
              }
              // Initialize Input-Menu
              else saisi_HEURE.start(lumiere.getValue(sousMenu.index()));
              break;

            case MENU_PULVE:
              // switch enable - disable
              if (sousMenu.index() == CYCLIC_ENABLE)
              {
                pulverisateur.enable(!pulverisateur.isEnable());
                pulverisateur.saveValue(CYCLIC_ENABLE);
                sousMenu.setSelect(false);
              }
              // Going back
              else if (sousMenu.index() == CYCLIC_RETURN)
              {
                sousMenu.setSelect(false);
                menu.setSelect(false);
              }
              // Initialize Input-Menu
              else saisi_SECONDE.start(pulverisateur.getValue(sousMenu.index()));
              break;

            case MENU_RESERVOIR:
              // Initialize Input-Menu
              if (sousMenu.index() == RESERVOIR_LIMIT)
              {
                saisi_INT = CompteurInt(0, (MAX_DISTANCE - 1) );
                saisi_INT.start(reservoir.getValue());
              }
              // switch enable - disable
              else if (sousMenu.index() == RESERVOIR_ENABLE)
              {
                reservoir.enable(!reservoir.isEnable());
                reservoir.saveValue(RESERVOIR_ENABLE);
                sousMenu.setSelect(false);
              }
              // Going back
              else if (sousMenu.index() == RESERVOIR_RETURN)
              {
                sousMenu.setSelect(false);
                menu.setSelect(false);
              }
              break;

            case MENU_TEMP:
              // Going back
              if (sousMenu.index() == TEMP_RETURN)
              {
                sousMenu.setSelect(false);
                menu.setSelect(false);
              }
              // Initialize Input-Menu
              else
			  {
				  float tempValue = tapis.getValue(sousMenu.index());
				  if(tempValue == 0) saisi_FLOAT.start(20);
				  else saisi_FLOAT.start(tempValue);
			  }
              break;

            case MENU_HUM:
              // Going back
              if (sousMenu.index() == HUM_RETURN)
              {
                sousMenu.setSelect(false);
                menu.setSelect(false);
              }
              // Initialize Input-Menu
              else
			  {
				  float tempValue = 0;
				  switch(sousMenu.index())
				  {
					  case HUM_DAY_MIN:
						tempValue = ventilo.getValue(FAN_HUM_DAY_MIN);
						break;
					  case HUM_DAY_MAX:
						tempValue = ventilo.getValue(FAN_HUM_DAY_MAX);
						break;
					  case HUM_NIGHT_MIN:
						tempValue = ventilo.getValue(FAN_HUM_NIGHT_MIN);
						break;
					  case HUM_NIGHT_MAX:
						tempValue = ventilo.getValue(FAN_HUM_NIGHT_MAX);
						break;
					  default:
						break;
				  }
				  if(tempValue == 0) saisi_FLOAT.start(80);
				  else saisi_FLOAT.start(tempValue);
			  }
              break;

            case MENU_THERMO:
              // switch enable - disable
              if ( sousMenu.index() == THERMO_HEAT)
              {
                tapis.enable(!tapis.isEnable());
                tapis.saveValue(THERMO_ENABLE);
                sousMenu.setSelect(false);
              }
              // switch enable - disable
              else if ( sousMenu.index() == THERMO_FAN)
              {
                ventilo.enable(!ventilo.isEnable());
                ventilo.saveValue(FAN_ENABLE);
                sousMenu.setSelect(false);
              }
              // Going back
              else if (sousMenu.index() == THERMO_RETURN)
              {
                sousMenu.setSelect(false);
                menu.setSelect(false);
              }
              break;

            case MENU_CLOCK:
              // Initialize Input-Menu for Date
              if (sousMenu.index() == CLOCK_DATE) saisi_DATE.start(now.year(), now.month(), now.day());
              // Initialize Input-Menu for Time
              else if (sousMenu.index() == CLOCK_HEURE) saisi_HEURE.start((now.hour() * 60) + now.minute());
              // Going back
              else if (sousMenu.index() == CLOCK_RETURN)
              {
                sousMenu.setSelect(false);
                menu.setSelect(false);
              }
              break;

            case MENU_GENERAL:
              // Initialize Input-Menu
              if (sousMenu.index() == RETRO_TIME) saisi_SECONDE.start(retro.getValue(RETRO_TIME));
              // Initialize Input-Menu
              else if (sousMenu.index() == RETRO_BRIGHT)
              {
                saisi_INT = CompteurInt(0, 8);
                saisi_INT.start(retro.getValue(RETRO_BRIGHT));

              }
              // Initialize Input-Menu
              else if (sousMenu.index() == GENERAL_RESET) saisi_BOOL.start(false);
              // Going back
              else if (sousMenu.index() == GENERAL_RETURN)
              {
                sousMenu.setSelect(false);
                menu.setSelect(false);
              }
              break;

            default:
              break;
          }
        }
      }
      // Input-Menu
      else
      {
        switch (menu.index())
        {
          case MENU_LIGHT:
            // Input increment
            saisi_HEURE.run(key);
            // Save setting
            if (saisi_HEURE.isSelect())
            {
              // Save if not the same
              if (saisi_HEURE.time() != lumiere.getValue(sousMenu.index()) )
              {
                lumiere.setValue(sousMenu.index(), saisi_HEURE.time());
                lumiere.saveValue(sousMenu.index());
              }
              // Back to Sub-Menu
              sousMenu.setSelect(false);
            }
            break;

          case MENU_PULVE:
            // Input increment
            saisi_SECONDE.run(key);
            // Save setting
            if (saisi_SECONDE.isSelect())
            {
              // Save if not the same
              if (saisi_SECONDE.seconde() != pulverisateur.getValue(sousMenu.index()) )
              {
                pulverisateur.setValue(sousMenu.index(), saisi_SECONDE.seconde());
                pulverisateur.saveValue(sousMenu.index());
              }
              // Back to Sub-Menu
              sousMenu.setSelect(false);
            }
            break;

          case MENU_RESERVOIR:
            // Input increment
            saisi_INT.run(key);
            // Save setting
            if (saisi_INT.isSelect())
            {
              // Save if not the same
              if (saisi_INT.value() != reservoir.getValue() )
              {
                reservoir.setValue(saisi_INT.value());
                reservoir.saveValue(RESERVOIR_LIMIT);
              }
              // Back to Sub-Menu
              sousMenu.setSelect(false);
            }
            break;

          case MENU_TEMP:
            // Input increment
            saisi_FLOAT.run(key);
            // Save setting
            if (saisi_FLOAT.isSelect())
            {
              // Save if not the same
              if (saisi_FLOAT.value() != tapis.getValue(sousMenu.index()) )
              {
                tapis.setValue(sousMenu.index(), saisi_FLOAT.value());
                tapis.saveValue(sousMenu.index());
                ventilo.setValue(sousMenu.index(), saisi_FLOAT.value());
                ventilo.saveValue(sousMenu.index());
              }
              // Back to Sub-Menu
              sousMenu.setSelect(false);
            }
            break;

          case MENU_HUM:
            // Input increment
            saisi_FLOAT.run(key);
            // Save setting
            if (saisi_FLOAT.isSelect())
            {
			  switch(sousMenu.index())
			  {
				  case HUM_DAY_MIN:
				    // Save if not the same
					if (saisi_FLOAT.value() != ventilo.getValue(FAN_HUM_DAY_MIN) )
					{
					  ventilo.setValue(FAN_HUM_DAY_MIN, saisi_FLOAT.value());
					  ventilo.saveValue(FAN_HUM_DAY_MIN);
					}
					break;
				  case HUM_DAY_MAX:
				    // Save if not the same
					if (saisi_FLOAT.value() != ventilo.getValue(FAN_HUM_DAY_MAX) )
					{
					  ventilo.setValue(FAN_HUM_DAY_MAX, saisi_FLOAT.value());
					  ventilo.saveValue(FAN_HUM_DAY_MAX);
					}
					break;
				  case HUM_NIGHT_MIN:
				    // Save if not the same
					if (saisi_FLOAT.value() != ventilo.getValue(FAN_HUM_NIGHT_MIN) )
					{
					  ventilo.setValue(FAN_HUM_NIGHT_MIN, saisi_FLOAT.value());
					  ventilo.saveValue(FAN_HUM_NIGHT_MIN);
					}
					break;
				  case HUM_NIGHT_MAX:
				    // Save if not the same
					if (saisi_FLOAT.value() != ventilo.getValue(FAN_HUM_NIGHT_MAX) )
					{
					  ventilo.setValue(FAN_HUM_NIGHT_MAX, saisi_FLOAT.value());
					  ventilo.saveValue(FAN_HUM_NIGHT_MAX);
					}
					break;
				  default:
					break;
			  }
              // Back to Sub-Menu
              sousMenu.setSelect(false);
            }
            break;

          case MENU_CLOCK:
            switch (sousMenu.index())
            {
              case CLOCK_DATE:
                // Input increment
                saisi_DATE.run(key);
                // Save setting and Back to Sub-Menu
                if (saisi_DATE.isSelect())
                {
                  save_clock(sousMenu.index());
                  sousMenu.setSelect(false);
                }
                break;

              case CLOCK_HEURE:
                // Input increment
                saisi_HEURE.run(key);
                // Save setting and Back to Sub-Menu
                if (saisi_HEURE.isSelect())
                {
                  save_clock(sousMenu.index());
                  sousMenu.setSelect(false);
                }
                break;

              default:
                break;
            }
            break;

          case MENU_GENERAL:
            switch (sousMenu.index())
            {
              case RETRO_TIME:
                // Input increment
                saisi_SECONDE.run(key);
                // Save setting
                if (saisi_SECONDE.isSelect())
                {
                  // Save if not the same
                  if (saisi_SECONDE.seconde() != retro.getValue(sousMenu.index()) )
                  {
                    retro.setValue(sousMenu.index(), saisi_SECONDE.seconde());
                    retro.saveValue(sousMenu.index());
                  }
                  // Back to Sub-Menu
                  sousMenu.setSelect(false);
                }
                break;

              case RETRO_BRIGHT:
                // Input increment
                saisi_INT.run(key);
                // Apply value
                retro.setValue(sousMenu.index(), saisi_INT.value());
                // Save setting
                if (saisi_INT.isSelect())
                {
                  retro.setValue(sousMenu.index(), saisi_INT.value());
                  retro.saveValue(sousMenu.index());
                  // Back to Sub-Menu
                  sousMenu.setSelect(false);
                }
                break;

              case GENERAL_RESET:
                // Input increment
                saisi_BOOL.run(key);
                // Save setting
                if (saisi_BOOL.isSelect())
                {
                  // Reset if True
                  if (saisi_BOOL.value()) resetArduino();
                  // Back to Sub-Menu
                  sousMenu.setSelect(false);
                }
                break;

              default:
                break;
            }
            break;

          default:
            break;
        }
      }
    }
  }
}
void print_lcd()
{
  // clear lcd on key press
  if (keypad.isPress()) lcd.clear();
  // Going Home and stop retro light
  bool last_working = retro.isWorking();
  retro.run(now.unixtime(), keypad.isPress());
  if (retro.isWorking() != last_working)
  {
    if (retro.isWorking() == false)
    {
      lcd.clear();
      menu.setIndex(MENU_HOME);
      menu.setSelect(false);
      sousMenu.setSelect(false);
    }
  }
  // LCD Print
  switch (menu.index())
  {
    case MENU_HOME:
      home_menu();
      break;

    case MENU_LIGHT:
      if (menu.isSelect() == false) lumiere_home();
      else if (sousMenu.isSelect() == false) lumiere_conf();
      else lumiere_saisi();
      break;

    case MENU_PULVE:
      if (menu.isSelect() == false) pulve_home();
      else if (sousMenu.isSelect() == false) pulve_conf();
      else pulve_saisi();
      break;

    case MENU_RESERVOIR:
      if (menu.isSelect() == false) reservoir_home();
      else if (sousMenu.isSelect() == false) reservoir_conf();
      else reservoir_saisi();
      break;

    case MENU_TEMP:
      if (menu.isSelect() == false) temp_home();
      else if (sousMenu.isSelect() == false) temp_conf();
      else temp_saisi();
      break;

    case MENU_HUM:
      if (menu.isSelect() == false) hum_home();
      else if (sousMenu.isSelect() == false) hum_conf();
      else hum_saisi();
      break;

    case MENU_THERMO:
      if (menu.isSelect() == false) thermo_home();
      else if (sousMenu.isSelect() == false) thermo_conf();
      break;

    case MENU_CLOCK:
      if (menu.isSelect() == false) clock_home();
      else if (sousMenu.isSelect() == false) clock_conf();
      else clock_saisi();
      break;

    case MENU_GENERAL:
      if (menu.isSelect() == false) general_home();
      else if (sousMenu.isSelect() == false) general_conf();
      else general_saisi();
      break;

    default:
      break;
  }
}

// ### MAIN ###
void setup()
{
  // Initialize LCD
  lcd.begin(16, 2);
  digitalWrite(RETRO_PIN, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome on");
  lcd.setCursor(0, 1);
  lcd.print("Terraduino");
  lcd.setCursor(12, 1);
  lcd.print("v0.5");
  delay(5000);
  lcd.clear();
  digitalWrite(RETRO_PIN, LOW);
  // Initialize RTC
  Wire.begin();
  rtc.begin();
  if (! rtc.isrunning()) rtc.adjust(DateTime(__DATE__, __TIME__));
  // Initialize DHT22
  dht.begin();
  // Load OBJECTS
  loadObjects();
}
void loop()
{
  // Read sensors
  measure();
  // Get Time
  now = rtc.now();
  // Read keypad
  keypad.read();
  // Run OBJECTS
  runObjects();
  // Menu Browsing
  nav_menu();
  // Print LCD
  print_lcd();
}
