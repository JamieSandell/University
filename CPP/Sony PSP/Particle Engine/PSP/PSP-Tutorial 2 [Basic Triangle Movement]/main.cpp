#include "My_Triangle.h"
#include <moduleexport.h>
SCE_MODULE_INFO( Application, 0, 1, 1 );


int main()
{
	//sceGuDebugPrint(0, 30, 0x00ffffff, "SEED PSP PROJECT - LIGHTS AND MATERIALS TUTORIAL");
	My_Triangle * app = new My_Triangle();
	app->Begin();
	delete app;	
	return 0;
}