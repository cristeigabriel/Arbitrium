#pragma once

#include <CSGO/defines.h>
#include <Shared/memory/memory.h>

class cHooking
{
public:
	using hookingGameOverlayRendererHookMethod = bool(__cdecl*)(void*, void*, void*, int);
	using hookingGameOverlayRendererUnhookmethod = void(__cdecl*)(void*, bool);

private:
	static hookingGameOverlayRendererHookMethod _hook;
	static hookingGameOverlayRendererUnhookmethod _unhook;

public:
	template <typename T>
	bool applyHook(LPVOID address)
	{
		return _hook(address, T::hooked, &T::original, 0);
	}

	void disableHook(LPVOID address)
	{
		_unhook(address, false);
	}

public:
	cHooking();

	bool initializer();

	~cHooking();
};

inline cHooking::hookingGameOverlayRendererHookMethod cHooking::_hook;
inline cHooking::hookingGameOverlayRendererUnhookmethod cHooking::_unhook;