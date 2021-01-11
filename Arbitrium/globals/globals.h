#pragma once

#include <Shared/memory/memory.h>

class cGlobals
{
public:
	bool shouldRelease;

public:
	cGlobals();

	bool initializer();

	~cGlobals();
};