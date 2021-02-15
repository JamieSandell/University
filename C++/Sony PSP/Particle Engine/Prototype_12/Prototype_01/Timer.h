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
private:
	bool           resetted;
	bool           running;
	unsigned long  beg;
	unsigned long  end;
};
