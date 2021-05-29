#include "StepLinearDriverInstruction.h"

StepLinearDriverInstruction::StepLinearDriverInstruction(float rpm, int32_t steps)
{
	this->rpm = rpm;
	this->dir = steps > 0;
	this->steps = this->dir ? steps : -steps;
    this->pulseDelay = 0;
}

DriverInstructionResult StepLinearDriverInstruction::Execute(StepperDriver* driver)
{
	if (pulseDelay == 0)
	{
		pulseDelay = 60L * 1000L * 1000L / driver->NumberOfSteps / rpm;
		/*digitalWrite(driver->Dir, dir);*/
#ifdef MSTEP_DEBUG
		MSTEP_DEBUG_STREAM.print("New instruction: delay: ");
		MSTEP_DEBUG_STREAM.println(pulseDelay);
#endif
		//delayMicroseconds(1);
	}
    if (pulseDelay == 0) pulseDelay = 1;

    uint32_t now = micros();
    // move only if the appropriate delay has passed:
    if (now >= nextPulse)
    {
        if (dir == 1)
        {
            thisStep++;
            if (thisStep == driver->NumberOfSteps) {
                thisStep = 0;
            }
        }
        else
        {
            if (thisStep == 0) {
                thisStep = driver->NumberOfSteps;
            }
            thisStep--;
        }
        if (driver->StepCompatibility == StepType::Sixteenth) thisStep %= 10;
        else thisStep %= 4;
		nextPulse = nextPulse == 0 ? now + pulseDelay : nextPulse + pulseDelay;
		/*if (driver->MS1 != NOT_A_PIN) digitalWrite(driver->MS1, bitRead(driver->StepCompatibility, 0));
		if (driver->MS2 != NOT_A_PIN) digitalWrite(driver->MS2, bitRead(driver->StepCompatibility, 1));
		if (driver->MS3 != NOT_A_PIN) digitalWrite(driver->MS3, bitRead(driver->StepCompatibility, 2));*/
        if (driver->StepCompatibility == StepType::Step)
        {
            switch (thisStep) {
            case 0:  // 01
                digitalWrite(driver->Step, LOW);
                digitalWrite(driver->Dir, HIGH);
                break;
            case 1:  // 11
                digitalWrite(driver->Step, HIGH);
                digitalWrite(driver->Dir, HIGH);
                break;
            case 2:  // 10
                digitalWrite(driver->Step, HIGH);
                digitalWrite(driver->Dir, LOW);
                break;
            case 3:  // 00
                digitalWrite(driver->Step, LOW);
                digitalWrite(driver->Dir, LOW);
                break;
            }
        }
        if (driver->StepCompatibility == StepType::Sixteenth)
        {
            switch (thisStep) {
            case 0:  // 01101
                digitalWrite(driver->Dir, LOW);
                digitalWrite(driver->Step, HIGH);
                digitalWrite(driver->MS1, HIGH);
                digitalWrite(driver->MS2, LOW);
                digitalWrite(driver->MS3, HIGH);
                break;
            case 1:  // 01001
                digitalWrite(driver->Dir, LOW);
                digitalWrite(driver->Step, HIGH);
                digitalWrite(driver->MS1, LOW);
                digitalWrite(driver->MS2, LOW);
                digitalWrite(driver->MS3, HIGH);
                break;
            case 2:  // 01011
                digitalWrite(driver->Dir, LOW);
                digitalWrite(driver->Step, HIGH);
                digitalWrite(driver->MS1, LOW);
                digitalWrite(driver->MS2, HIGH);
                digitalWrite(driver->MS3, HIGH);
                break;
            case 3:  // 01010
                digitalWrite(driver->Dir, LOW);
                digitalWrite(driver->Step, HIGH);
                digitalWrite(driver->MS1, LOW);
                digitalWrite(driver->MS2, HIGH);
                digitalWrite(driver->MS3, LOW);
                break;
            case 4:  // 11010
                digitalWrite(driver->Dir, HIGH);
                digitalWrite(driver->Step, HIGH);
                digitalWrite(driver->MS1, LOW);
                digitalWrite(driver->MS2, HIGH);
                digitalWrite(driver->MS3, LOW);
                break;
            case 5:  // 10010
                digitalWrite(driver->Dir, HIGH);
                digitalWrite(driver->Step, LOW);
                digitalWrite(driver->MS1, LOW);
                digitalWrite(driver->MS2, HIGH);
                digitalWrite(driver->MS3, LOW);
                break;
            case 6:  // 10110
                digitalWrite(driver->Dir, HIGH);
                digitalWrite(driver->Step, LOW);
                digitalWrite(driver->MS1, HIGH);
                digitalWrite(driver->MS2, HIGH);
                digitalWrite(driver->MS3, LOW);
                break;
            case 7:  // 10100
                digitalWrite(driver->Dir, HIGH);
                digitalWrite(driver->Step, LOW);
                digitalWrite(driver->MS1, HIGH);
                digitalWrite(driver->MS2, LOW);
                digitalWrite(driver->MS3, LOW);
                break;
            case 8:  // 10101
                digitalWrite(driver->Dir, HIGH);
                digitalWrite(driver->Step, LOW);
                digitalWrite(driver->MS1, HIGH);
                digitalWrite(driver->MS2, LOW);
                digitalWrite(driver->MS3, HIGH);
                break;
            case 9:  // 00101
                digitalWrite(driver->Dir, LOW);
                digitalWrite(driver->Step, LOW);
                digitalWrite(driver->MS1, HIGH);
                digitalWrite(driver->MS2, LOW);
                digitalWrite(driver->MS3, HIGH);
                break;
            }
        }
        thisStep = (thisStep + 1) % 10;
        steps--;
	}
	if (steps == 0) return DriverInstructionResult::Done;
	return DriverInstructionResult::Success;
}
