#pragma once #include <time.h>
//#include <conio.h>


//////////////////////////////////////////
// class declaration:


class Timer {
public:
	Timer(void);
	~Timer(void);
	void           start();
	void           stop();
	void           reset();
	bool           isRunning();
	unsigned long  getTime();
	bool           isOver(unsigned long seconds);
	float GetDt();
private:
	bool           resetted;
	bool           running;
	unsigned long  beg;
	unsigned long  end;
	float dt;
	clock_t _ticksSinceStart;
	clock_t _oldTick;
};
