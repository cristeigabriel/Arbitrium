#include <CSGO/include.h>

#include "../hooks.h"
#include "../prototypes.h"

bool __stdcall prototypes::createMove::hooked(float sampleTime, CUserCmd* cmd)
{
	if (!cmd || !cmd->commandNumber)
		return original(sampleTime, cmd);

	cmd->buttons |= cmdButtons::IN_BULLRUSH;

	return false;
}