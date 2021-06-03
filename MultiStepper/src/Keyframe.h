#ifndef _Keyframe_h
#define _Keyframe_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


struct Keyframe
{
	uint16_t ChannelID;
	uint32_t MS;
	int32_t Steps;
	void Print()
	{
		Serial.println(4);
		Serial.print("ID: ");
		Serial.print(ChannelID);
		Serial.print(" MS: ");
		Serial.print(MS);
		Serial.print(" Steps: ");
		Serial.println(Steps);
	}
};

#endif // !_Keyframe_h

