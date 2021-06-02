#ifndef _KeyframeInstruction_h
#define _KeyframeInstruction_h

#include "Keyframe.h"
#include "IDriverInstruction.h"
#include "TimeSync.h"

class KeyframeDriverInstruction : public IDriverInstruction
{
private:
    uint32_t nextPulse;
    uint32_t pulseDelay;
    int32_t steps;
    bool dir;
    Keyframe m_start;
    Keyframe m_end;
    TimeSync* m_sync;
private:
    int8_t Repeat(int8_t step, int8_t length);
public:
    KeyframeDriverInstruction(TimeSync* sync, Keyframe start, Keyframe end);
    DriverInstructionResult Execute(StepperDriver* driver) override;
};

#endif // !_KeyframeInstruction_h

