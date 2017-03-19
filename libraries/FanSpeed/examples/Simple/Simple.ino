#include <DHT.h>
#include <DHT_U.h>
#include <FanSpeed.h>

#define DHT_PIN     2
#define DHTTYPE     DHT11
#define FAN_PIN     11

// DHT11
DHT dht(DHT_PIN, DHTTYPE);
float humA = 0;
float tempA = 0;

FanSpeed ventilo(FAN_PIN); // Declaration du thermostat sur la broche 13 de l'arduino
int last_speed = 0;
void mesurer()
{
  float tmp_hum = dht.readHumidity();
  float tmp_temp = dht.readTemperature();
  if (isnan(tmp_hum) || isnan(tmp_temp))
  {
    return;
  }
  humA  = tmp_hum;
  tempA = tmp_temp;
}
void setup()
{
  Serial.begin(9600);
  // definition des paramètres voulu
  ventilo.setValue(FAN_TEMP_DAY_MIN, 24);
  ventilo.setValue(FAN_TEMP_DAY_MAX, 26);
  ventilo.setValue(FAN_HUM_DAY_MIN, 80);
  ventilo.setValue(FAN_HUM_DAY_MAX, 90);
  ventilo.setValue(FAN_TEMP_NIGHT_MIN, 20);
  ventilo.setValue(FAN_TEMP_NIGHT_MAX, 22);
  ventilo.setValue(FAN_HUM_NIGHT_MIN, 90);
  ventilo.setValue(FAN_HUM_NIGHT_MAX, 100);

  // active le regulateur
  ventilo.enable();
}

void loop()
{
  mesurer();
  bool jour = true;
  ventilo.run(tempA, humA, jour);
  if (last_speed != ventilo.isWorking())
  {
    Serial.print("t: ");
    Serial.print(tempA);
    Serial.print(" h: ");
    Serial.print(humA);
    Serial.print(" s: ");
    Serial.println(ventilo.isWorking());
    last_speed = ventilo.isWorking();
  }
}
