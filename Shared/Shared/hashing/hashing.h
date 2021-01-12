#pragma once

#include <cstdint>
#include <string.h>

// Can't find original author, regardless, credits go to whoever that is.
namespace hashing
{
	using hashType = uint32_t;

	constexpr uint32_t seed = 0x45C3370D;
	constexpr uint32_t prime = 0x1000193;

	template <typename T, T val>
	struct constantHolder
	{
		enum valueHolder : T
		{
			value = val
		};
	};

	hashType fnv1aRt(const char* key);
	extern constexpr hashType fnv1aCt(const char* key, const hashType value = seed);
}

#define strHashCT(x) hashing::constantHolder<decltype(x), x>valueHolder::value
#define strHashRT(x) hashing::fnv1aRt(x)