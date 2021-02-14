#include "Timer.h"
Timer::Timer(void)
{
	_ticksSinceStart = clock();
	_oldTick = clock();
	_ticksSinceCreation = clock();
	_timeofCreation = clock();
}
Timer::~Timer(void)
{

}
float Timer::GetRunTime() // returns the amount of time in seconds that has elapsed since the program
// started.
{
	_ticksSinceStart = clock();
	return ((float)_ticksSinceStart/(float)CLOCKS_PER_SEC);
}
float Timer::Tick() // returns the amount of time in seconds that has elapsed since the last time that
// this same function was called.
{
	_ticksSinceStart = clock();
	float dt = ((float)(_ticksSinceStart-_oldTick)/(float)CLOCKS_PER_SEC);
	_oldTick = _ticksSinceStart;
	return dt;
}

float Timer::GetCreationTime()
{
   _ticksSinceCreation = clock();
   float dt = ((float)(_ticksSinceCreation - _timeofCreation) / (float)CLOCKS_PER_SEC);
   return dt;
}

void Timer::ResetTimer()
{
	_ticksSinceStart = clock();
	_oldTick = clock();
	_ticksSinceCreation = clock();
	_timeofCreation = clock();
}