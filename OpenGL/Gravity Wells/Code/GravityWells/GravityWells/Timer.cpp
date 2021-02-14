#include "Timer.h"

Timer::Timer(void)
{
	_timeOld = 0.0f;
	_frames = 0;
	_start = (float)timeGetTime();
	_fpsTimer = 0.0f;
	_fps = 0;;
	_updateTimer = 0.0f;
	_timePassed = 1000;
}

Timer::~Timer(void)
{
}
