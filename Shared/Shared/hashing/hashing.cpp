#include "hashing.h"

hashing::hashType hashing::fnv1aRt(const char* key)
{
	const char* data = const_cast<char*>(key);
	auto hash = seed;

#ifdef RELEASE
	hash ^= __readfsdword(0x20);
#endif

	for (uint32_t i = 0; i < strlen(key); ++i)
	{
		const uint8_t value = data[i];
		hash = hash ^ value;
		hash *= prime;
	}

	return hash;
}

constexpr hashing::hashType hashing::fnv1aCt(const char* key, const hashType value)
{
	return !*key ? value : fnv1aCt(key + 1, (unsigned)(1ull *
		(value ^ (uint8_t)*key) * prime));
}