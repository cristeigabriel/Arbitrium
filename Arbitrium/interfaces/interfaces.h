#pragma once

#include <CSGO/defines.h>
#include <Shared/memory/memory.h>

class cInterfaces : public memory::memoryWrapper
{
public:
	CHLClient* client;
	ClientModeShared* clientModeShared;
	CGlobalVarsBase* globalVars;
	CCSGO_HudChat* csgoHudChat;
	CHudChat* hudChat;

public:
	cInterfaces();

	bool initializer();
	
	~cInterfaces();
};