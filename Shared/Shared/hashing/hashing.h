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
		enum class valueHolder : T
		{
			value = val
		};
	};
#define constant(value) ((decltype(value))constantHolder<decltype(value), value>::valueHolder::value)

	hashType fnv1aRt(const char* key);
	constexpr hashType fnv1aCt(const char* key, const hashType value = seed);
}

#define strHashCT(x) constant(hashing::fnv1aCt(x))
#define strHashRT(x) hashing::fnv1aRt(x)