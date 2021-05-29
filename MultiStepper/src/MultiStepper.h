/*
 Name:		MultiStepper.h
 Created:	5/27/2021 6:43:09 PM
 Author:	civel
 Editor:	http://www.visualmicro.com
*/

#ifndef _MultiStepper_h
#define _MultiStepper_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef MSTEP_MAX_COUNT
#define MSTEP_MAX_COUNT 5
#endif


#include "MultiStepperUtillities.h"
#include "Stepperdriver.h"
#include "StepLinearDriverInstruction.h"

class MultiStepperClass
{
private:
	StepperDriver* m_drivers[MSTEP_MAX_COUNT];
	size_t m_count;
public:
private:
public:
	MultiStepperClass();
	void AttachDriver(StepperDriver* driver);
	void UpdateDrivers();
};

extern MultiStepperClass MStep;

//You can also use MStep as a shortcut
#define MultiStepper MStep

#endif

