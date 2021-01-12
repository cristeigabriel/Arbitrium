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

	// Function above LevelInit's
	// LevelInit: ; #STR: "game_newmap", "mapname", "LevelInit"
	// IBaseClientDLL CreateMove 55 8B EC 8B 0D ? ? ? ? 85 C9 75 06 
	prototypes::signatures::createMove = gAddresses.find<LPVOID>("client.dll",
		{ 0x55, 0x8B, 0xEC, 0x8B, 0x0D, -1, -1, -1, -1, 0x85, 0xC9, 0x75, 0x06 }
	);

	if (!prototypes::signatures::createMove)
		return false;

	if (!applyHook<prototypes::createMove>(prototypes::signatures::createMove))
		return false;

	return true;
}

cHooking::~cHooking()
{

}