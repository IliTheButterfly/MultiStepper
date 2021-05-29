#ifndef _IDriverInstruction_h
#define _IDriverInstruction_h

#include "Stepperdriver.h"

enum DriverInstructionResult
{
	Success,
	Done,
};

class IDriverInstruction
{
protected:

public:
	virtual DriverInstructionResult Execute(StepperDriver* driver) = 0;
};


#endif // !_IDriverInstruction_h