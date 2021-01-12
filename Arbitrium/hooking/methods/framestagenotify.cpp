#include <CSGO/include.h>

#include "../hooking.h"
#include "../prototypes.h"

void __stdcall prototypes::frameStageNotify::hooked(clientFrameStages stage)
{
	original(stage);
}