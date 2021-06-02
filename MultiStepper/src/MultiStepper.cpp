/*
 Name:		MultiStepper.cpp
 Created:	5/27/2021 6:43:09 PM
 Author:	civel
 Editor:	http://www.visualmicro.com
*/

#include "MultiStepper.h"

MultiStepperClass::MultiStepperClass()
{
	//m_drivers = (StepperDriver**)malloc(MSTEP_MAX_COUNT * sizeof(StepperDriver*));
	m_count = 0;
}

void MultiStepperClass::AttachCallback(instructionCB_t callback)
{
	m_callback = callback;
}

void MultiStepperClass::AttachDriver(StepperDriver* driver)
{
#ifdef MSTEP_DEBUG
	MSTEP_DEBUG_STREAM.print("Attaching Driver: ");
	MSTEP_DEBUG_STREAM.print(this->m_count);
	MSTEP_DEBUG_STREAM.println("...\t");
	delay(500);
#endif
	this->m_drivers[m_count] = driver;
#ifdef MSTEP_DEBUG
	MSTEP_DEBUG_STREAM.println("Attached driver");
#endif


	pinMode(driver->Dir, OUTPUT);
	pinMode(driver->Step, OUTPUT);
	if (driver->MS1 != NOT_A_PIN) pinMode(driver->MS1, OUTPUT);
	if (driver->MS2 != NOT_A_PIN) pinMode(driver->MS2, OUTPUT);
	if (driver->MS3 != NOT_A_PIN) pinMode(driver->MS3, OUTPUT);

#ifdef MSTEP_DEBUG
	MSTEP_DEBUG_STREAM.println("Initialized");
#endif

	this->m_count++;
}

void MultiStepperClass::UpdateDrivers()
{
	for (size_t i = 0; i < m_count; i++)
	{
		if (m_drivers[i]->Instruction != nullptr)
		{
			auto result = m_drivers[i]->Instruction->Execute(m_drivers[i]);
			if (result == DriverInstructionResult::Done) m_drivers[i]->SetInstruction(nullptr);
			if (m_callback != nullptr)
			{
				m_callback(i, result);
			}
		}
	}
}


MultiStepperClass MStep;