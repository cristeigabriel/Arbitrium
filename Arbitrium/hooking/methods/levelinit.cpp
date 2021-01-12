#include <CSGO/include.h>

#include "../hooking.h"
#include "../prototypes.h"

void __fastcall prototypes::levelInit::hooked(void* ecx, void* edx, const char* mapName)
{
	// TODO: Call FileCRCCheck bypass hook here
	
	original(ecx, edx, mapName);
}