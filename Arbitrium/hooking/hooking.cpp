#include "hooking.h"
#include "prototypes.h"
#include "../main/entry.h"

cHooking::cHooking()
{

}

bool cHooking::initializer()
{
	_hook = gAddresses.findRelToAbs<hookingGameOverlayRendererHookMethod>("gameoverlayrenderer.dll",
		{ 0xE8, -1, -1, -1, -1, 0x83, 0xC4, 0x10, 0xEB, 0x21 },
		1
		);

	if (!_hook)
		return false;

	_unhook = gAddresses.findRelToAbs<hookingGameOverlayRendererUnhookmethod>("gameoverlayrenderer.dll",
		{ 0xE8, -1, -1, -1, -1, 0x83, 0xC4, 0x08, 0xFF, 0x15, -1, -1, -1, -1 },
		1
		);

	if (!_unhook)
		return false;

	// #STR: "game_newmap", "mapname", "LevelInit"
	// ClientModeShared LevelInit 55 8B EC 83 E4 F8 83 EC 20 56 57 8B F9 8B 4F 18 
	prototypes::signatures::levelInit = gAddresses.find<LPVOID>("client.dll",
		{ 0x55, 0x8B, 0xEC, 0x83, 0xE4, 0xF8, 0x83, 0xEC, 0x20, 0x56, 0x57, 0x8B, 0xF9, 0x8B, 0x4F, 0x18 }
	);

	if (!prototypes::signatures::levelInit)
		return false;

	// Function above LevelInit's
	// ClientModeShared CreateMove 55 8B EC 8B 0D ? ? ? ? 85 C9 75 06 
	prototypes::signatures::createMove = gAddresses.find<LPVOID>("client.dll",
		{ 0x55, 0x8B, 0xEC, 0x8B, 0x0D, -1, -1, -1, -1, 0x85, 0xC9, 0x75, 0x06 }
	);

	if (!prototypes::signatures::createMove)
		return false;

	if (!applyHook<prototypes::levelInit>(prototypes::signatures::levelInit))
		return false;

	if (!applyHook<prototypes::createMove>(prototypes::signatures::createMove))
		return false;

	return true;
}

cHooking::~cHooking()
{

}