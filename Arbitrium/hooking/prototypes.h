#pragma once

#include <CSGO/defines.h>

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
		createMove
	);

	DECLARE_SIGNATURES
	(
		signatures::createMove
	);

	PROTOTYPE_FUNCTION(createMove, bool(__stdcall)(float, CUserCmd*));
}