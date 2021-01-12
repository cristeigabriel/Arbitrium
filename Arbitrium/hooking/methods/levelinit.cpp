#include <CSGO/include.h>

#include "../hooking.h"
#include "../prototypes.h"

void __fastcall prototypes::levelInit::hooked(void* ecx, void* edx, const char* mapName)
{
	original(ecx, edx, mapName);
}