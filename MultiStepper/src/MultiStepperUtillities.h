#ifndef _MultiStepperUtillities_h
#define _MultiStepperUtillities_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

//#define MSTEP_DEBUG


#ifdef MSTEP_DEBUG

#ifndef MSTEP_DEBUG_STREAM
#define MSTEP_DEBUG_STREAM Serial
#endif // !MSTEP_DEBUG_STREAM


#endif // MSTEP_DEBUG

enum StepType
{
	Smallest,
	Step,
	Half,
	Quarter,
	Eigth,
	Sixteenth
};

typedef uint8_t pin_t;
//enum StepFlags
//{
//	Full		= 0b000,
//	Half		= 0b001,
//	Quater		= 0b010,
//	Eight		= 0b011,
//	Sixteenth	= 0b111,
//};
/*StepFlags GetStepFlag(StepType compatibility, StepType request)
{
	if (request == StepType::Smallest) request = compatibility;
	switch (request)
	{
	case StepType::Step:
		return StepFlags::Full;
	case StepType::Half:
		return StepFlags::Half;
	case StepType::Quarter:
		return StepFlags::Quater;
	case StepType::Eigth:
		return StepFlags::Eight;
	case StepType::Sixteenth:
		return StepFlags::Sixteenth;
	default:
		break;
	}
}*/


#endif // !_MultiStepperUtillities_h
