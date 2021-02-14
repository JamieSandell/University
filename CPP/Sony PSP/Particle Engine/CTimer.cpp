//**************************************************************************
//		PSPGU Tutorial: 'Lesson6' - CTimer.cpp
//**************************************************************************
#include "CTimer.h"

CTimer::CTimer( void )
{
	sceRtcGetCurrentTick( &timeLastAsk );
	tickResolution = sceRtcGetTickResolution();
	
	frames = 0; // for calculating the frames per second
   
   sceRtcGetCurrentTick(&previous);
res = sceRtcGetTickResolution();
}

double CTimer::GetDeltaTime( void )
{
	sceRtcGetCurrentTick( &timeNow );
	double dt = ( timeNow - timeLastAsk ) / ((float) tickResolution );
	timeLastAsk = timeNow;

	return dt;
}

int CTimer::GetFramesPerSec( void )
{
    sceRtcGetCurrentTick( &now );
    if( ((now - previous)/((float)res)) >= 1.0f ) {
      previous = now;
      int temp = frames;
      frames = 0;
      return temp;
   }
   return frames;
}

void CTimer::IncreaseFramesPerSec( void )
{
     frames++;
}
