#pragma once
#include <Windows.h>

#pragma comment( lib, "winmm.lib" ) 

class Timer
{
public:
	Timer(void);
	~Timer(void);

	inline float GetDeltaTime(void){
		float timeNow = (float)timeGetTime() / 1000.0f;
		_timeOld = timeNow - (1.0f/50.0f);

		float delta = timeNow - _timeOld;
		_timeOld = timeNow;

		return delta;
	};
	inline int GetFPS(void){
		_frames++;

		if ((float)timeGetTime()-_fpsTimer>1000){
			_fpsTimer = (float)timeGetTime();
			_fps = _frames;
			_frames = 0;
		}
		return _fps;
	};
	inline bool HasTimePassed(void){
		if ((float)timeGetTime()-_timePassed>1000){
			_timePassed = (float)timeGetTime();
			return true;
		}
		return false;
	};
	inline bool UpdateRate(void){
		if ((float)timeGetTime()-_updateTimer>1000/50){
			_updateTimer = (float)timeGetTime();
			return true;
		}
		return false;
	};

private:
	float _timeOld;
	int _frames;
	float _fpsTimer;
	int _fps;
	float _lastTime;
	float _start;
	float _updateTimer;
	float _timePassed;
};
