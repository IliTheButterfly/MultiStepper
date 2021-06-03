#include "TimeSync.h"

TimeSync::TimeSync()
{
}

void TimeSync::Start()
{
    m_startMicros = micros();
    Started = true;
}

void TimeSync::Stop()
{
    Started = false;
}

uint32_t TimeSync::CurrentMicros()
{
    return micros() - m_startMicros;
}
