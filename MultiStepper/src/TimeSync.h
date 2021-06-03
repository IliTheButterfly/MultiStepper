#ifndef _TimeSync_h
#define _TimeSync_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class TimeSync
{
private:
	uint32_t m_startMicros;
public:
	bool Started;
public:
	TimeSync();
	void Start();
	void Stop();
	uint32_t CurrentMicros();
};

#endif // !_TimeSync_h

