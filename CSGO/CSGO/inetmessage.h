#pragma once

#include "defines.h"

#include <Shared/memory/memory.h>

class INetMessage
{
	enum indices
	{
		GET_TYPE_INDEX = 7,
		GET_GROUP_INDEX = 8
	};
public:
	// Can't get these by signature, I'll count on whatever's passed that origins from baseclass
	int getType()
	{
		return memory::utilities::vFunc<int, indices::GET_TYPE_INDEX>(this);
	}

	int getGroup()
	{
		return memory::utilities::vFunc<int, indices::GET_GROUP_INDEX>(this);
	}
};