#pragma once

#include <CSGO/defines.h>
#include <Shared/memory/memory.h>

namespace interfaces
{
	static CHLClient* client;
	static ClientModeShared* clientModeShared;
	static CGlobalVarsBase* globalVars;
	static CCSGO_HudChat* csgoHudChat;
	static CHudChat* hudChat;

	bool initializer();
};