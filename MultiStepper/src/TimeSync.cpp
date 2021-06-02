#include "TimeSync.h"

TimeSync::TimeSync()
{
}

void TimeSync::Start()
{
    m_startMicros = micros();
}

uint32_t TimeSync::CurrentMicros()
{
    return micros() - m_startMicros;
}
