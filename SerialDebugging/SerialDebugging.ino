/*
 Name:		SerialDebugging.ino
 Created:	6/2/2021 1:03:27 PM
 Author:	civel
*/

// the setup function runs once when you press reset or power the board
#include <SoftwareSerial.h>
SoftwareSerial SWSerial(2, 3);
void setup()
{
	Serial.begin(115200);
	SWSerial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	SWSerial.listen();
	if (SWSerial.available())
	{
		delay(500);
		while (SWSerial.available())
		{
			int b = SWSerial.read();
			if (b != -1) Serial.write(b);
		}
	}
}
