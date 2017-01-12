#include <ReadKey.h>

#define KEY_PIN 0

ReadKey keypad(KEY_PIN);

void setup()
{	
}

void loop()
{
	keypad.read();
	
	if(keypad.isPress())
	{
		switch(keypad.key())
		{
			case btnRIGHT:
				// btnRIGHT press
				break;
			case btnUP:
				// btnUP press
				break;
			case btnDOWN:
				// btnDOWN press
				break;
			case btnLEFT:
				// btnLEFT press
				break;
			case btnSELECT:
				// btnSELECT press
				break;
			default:
				break;
		}
	}
}