#ifndef _StepLinearDriverInstruction_h
#define _StepLinearDriverInstruction_h


#include "IDriverInstruction.h"
class StepLinearDriverInstruction :
    public IDriverInstruction
{
private:
    uint32_t nextPulse;
    uint32_t pulseDelay;
    int32_t steps;
    uint8_t thisStep;
    bool dir;
    float sps;
public:
    StepLinearDriverInstruction(float rpm, int32_t steps);
    DriverInstructionResult Execute(StepperDriver* driver) override;
};


#endif // !_StepLinearDriverInstruction_h