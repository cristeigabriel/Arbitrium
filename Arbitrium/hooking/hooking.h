#pragma once

#include <CSGO/defines.h>
#include <Shared/memory/memory.h>

namespace hooking
{
	using hookingGameOverlayRendererHookMethod = bool(__cdecl*)(void*, void*, void*, int);
	using hookingGameOverlayRendererUnhookmethod = void(__cdecl*)(void*, bool);
	
	static hookingGameOverlayRendererHookMethod _hook;
	static hookingGameOverlayRendererUnhookmethod _unhook;

	template <typename T>
	static bool applyHook(LPVOID address)
	{
		return _hook(address, T::hooked, &T::original, 0);
	}

	static void disableHook(LPVOID address)
	{
		_unhook(address, false);
	}

	bool initializer();
	void release();
};
