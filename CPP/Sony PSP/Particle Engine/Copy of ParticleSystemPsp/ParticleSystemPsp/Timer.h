#pragma once #include <time.h>
class Timer
{
public:
	Timer(void);
	~Timer(void);
	float GetRunTime();
	float GetCreationTime();
	float Tick();
	void ResetTimer();
private:
	clock_t _ticksSinceStart;
	clock_t _oldTick;
	clock_t _ticksSinceCreation;
	clock_t _timeofCreation;
};