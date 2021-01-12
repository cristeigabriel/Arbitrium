#pragma once

#include <CSGO/defines.h>
#include <CSGO/enums.h>

#define PROTOTYPE_SIGNATURES(...) \
struct signatures \
{ \
	static LPVOID __VA_ARGS__; \
};

#define DECLARE_SIGNATURES(...) \
inline LPVOID __VA_ARGS__;

#define PROTOTYPE_FUNCTION(functionName, functionPrototype) \
struct functionName \
{ \
	using fn = functionPrototype; \
	static fn hooked; \
	static fn* original; \
}; \
inline functionName::fn* functionName::original;

namespace prototypes
{
	PROTOTYPE_SIGNATURES
	(
		sendNetMsg,
		levelInit,
		createMove,
		frameStageNotify
	);

	DECLARE_SIGNATURES
	(
		signatures::sendNetMsg,
		signatures::levelInit,
		signatures::createMove,
		signatures::frameStageNotify
	);

	PROTOTYPE_FUNCTION(sendNetMsg, bool(__fastcall)(void*, void*, INetMessage&, bool, bool));
	PROTOTYPE_FUNCTION(levelInit, void(__fastcall)(void*, void*, const char*));
	PROTOTYPE_FUNCTION(createMove, bool(__stdcall)(float, CUserCmd*));
	PROTOTYPE_FUNCTION(frameStageNotify, void(__stdcall)(clientFrameStages));
}