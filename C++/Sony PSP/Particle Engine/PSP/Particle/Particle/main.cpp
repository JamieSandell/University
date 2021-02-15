#include "My_Particle.h"
#include <moduleexport.h>
SCE_MODULE_INFO( Application, 0, 1, 1 );


int main()
{
	//sceGuDebugPrint(0, 30, 0x00ffffff, "SEED PSP PROJECT - LIGHTS AND MATERIALS TUTORIAL");
	My_Particle * app = new My_Particle();
	app->Begin();
	delete app;	
	return 0;
}