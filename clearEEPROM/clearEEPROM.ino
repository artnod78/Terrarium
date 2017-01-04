#include <EEPROM.h>

void setup()
{
  for (int j = 0; j < 511; j++)
  {
    EEPROM.write(j, 0);
  }
}

void loop()
{
  while (1)
  {
    delay(1);
  }
}

