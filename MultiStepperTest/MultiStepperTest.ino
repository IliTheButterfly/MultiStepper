/*
 Name:		MultiStepperTest.ino
 Created:	5/27/2021 6:45:08 PM
 Author:	civel
*/

#define MSTEP_DEBUG
#include "MultiStepper.h"

StepperDriver* Motor1 = new StepperDriver(200, 2, 3, 4, 5, 6);

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(115200);
	MStep.AttachDriver(Motor1);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	static int hit = 0;
	if (hit++ == 500 && Serial.available())
	{
		int32_t steps = Serial.parseInt();
		uint32_t speed = Serial.parseInt();
		Serial.print("Moving: ");
		Serial.print(steps);
		Serial.print("steps at speed: ");
		Serial.println(speed);
		Motor1->SetInstruction(new StepLinearDriverInstruction(speed, steps));
		hit = 0;
	}
	MStep.UpdateDrivers();
}
