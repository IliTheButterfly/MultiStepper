# MultiStepper
## Introduction
MultiStepper is a versatile stepper driver library for Arduino that allows for multiple stepper drivers to be used simultaneously.

## Instantiating a ```StepperDriver```
TO instantiate a ```StepperDriver```, you must provide the pins it will be connected to:
```cpp
StepperDriver* Motor = new StepperDriver(
    numberOfSteps, //Normally 200
    stepPin,
    dirPin,
    microStep1Pin
    microStep2Pin
    microStep3Pin);
```

Then, you need to attach it to ```MultiStepper``` (```MStep```):
```cpp
void setup()
{
    MStep.AttachDriver(Motor);
    // Your code here
}
```

## Setting up a callback
If you want to be notified when an instruction ends, you need to attach a callback:
```cpp
void InstructionCallback(uint16_t channelID, DriverInstructionResult result)
{
    // Manage next instruction here
}
```
Then call this:
```cpp
MStep.AttachCallback(InstructionCallback);
```

## Updating the ```StepperDrivers```
After that, you need to call ```MStep.UpdateDrivers()``` as often as possible:
```cpp
void loop()
{
    MStep.UpdateDrivers();
}
```

## Using an Instruction
Now for the fun part, setting up instructions. For now there is only one Instruction available:
```cpp
void setup()
{
    // Initialization here

    IDriverInstruction* instruction = new LinearDriverInstruction(rpm, steps);
    Motor->SetInstruction(instruction);
    // Do not delete 'instruction'. 'SetInstruction()' deletes the previous instruction on change
}
```

## User defined Instructions
```cpp
class MyDriverInstruction : IDriverInstruction
{
private:
	int m_stepsLeft;
	bool m_dir;
	bool m_firstRun = true;
	uint32_t m_delay;
	uint32_t m_nextStepTime;
public:
	MyDriverInstruction(int steps, uint32_t delay)
	{
		m_stepsLeft = abs(steps);
		m_dir = m_stepsLeft > 0;
		m_delay = delay;
	}

	virtual DriverInstructionResult Execute(StepperDriver* driver) override
	{
		// If instruction is done, inform MStep
		if (m_stepsLeft <= 0) return DriverInstructionResult::Done;

		// Run this once
		if (m_firstRun)
		{
			// Setting direction
			digitalWrite(driver->Dir, m_dir);
			m_firstRun = false;

			// Setting microstep
			if (driver->StepCompatibility == StepType::Sixteenth)
				driver->SetMicroStepPins(MicroStep::MSSixteenth /*Micro step*/);

			// Set the delay
			m_nextStepTime = millis() + m_delay;
		}
		else // If we're not on first run, we can check if we need to step
		{
			// Do we step now?
			if (millis() < m_nextStepTime) return Success; // No? wWe yield
			// Yes? We set the next step time
			m_nextStepTime += m_delay;
			// Using '+= m_delay' instead of '= millis() + m_delay' will ensure an 
			// absolute speed regardless of execution time.
		}

		// Stepping
		digitalWrite(driver->Step, HIGH);
		delayMicroseconds(1); // Delay could be different for your motor driver
		digitalWrite(driver->Step, LOW);

		// Inform MStep the instruction is not done yet
		return DriverInstructionResult::Success;
	}
};
```
This is a template for a driver instruction. The rest is up to you.
