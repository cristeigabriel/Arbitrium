#include "entry.h"

#include "../console/console.h"

#include <string>

#ifdef COUNT_ALLOCATIONS
static uint32_t allocCount = 0;

void* operator new(size_t size)
{
	++allocCount;
	return malloc(size);
}
#endif

memory::modulesWrapper gModules;
memory::addressesWrapper gAddresses;

cGlobals gGlobals;
cInterfaces gInterfaces;
cHooking gHooking;

uint32_t WINAPI gameRoutine(HINSTANCE instance)
{
#ifdef _DEBUG
	cConsole console;
#endif

	try
	{
		gModules.initializer<7>(
			{
					"client.dll",
					"engine.dll",
					"gameoverlayrenderer.dll",
					"vguimatsurface.dll",
					"vgui2.dll",
					"shaderapidx9.dll",
					"serverbrowser.dll"
			});

		gAddresses.initializer(gModules);

		if (!gGlobals.initializer())
			throw std::runtime_error("Failed to initialize");
	
		if (!gInterfaces.initializer())
			throw std::runtime_error("Failed to initialize");

		if (!gHooking.initializer())
			throw std::runtime_error("Failed to initialize");
	}
	catch (const std::exception& err)
	{
#ifdef _DEBUG
		puts(err.what());
		MessageBoxA(0, err.what(), "Initialization", 0);
#endif
		gGlobals.shouldRelease = true;
	}

#ifdef COUNT_ALLOCATIONS
	printf("Allocations: %d\n", allocCount);
#endif

	while (!gGlobals.shouldRelease)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	gHooking.~cHooking();

	gInterfaces.~cInterfaces();

	gGlobals.~cGlobals();

	gAddresses.~addressesWrapper();
	gModules.~modulesWrapper();

#ifdef _DEBUG
	console.~cConsole();
#endif

	FreeLibraryAndExitThread((HMODULE)instance, EXIT_SUCCESS);

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call != DLL_PROCESS_ATTACH)
		return false;

	if (const HANDLE threadHandle = CreateThread(nullptr, NULL, LPTHREAD_START_ROUTINE(gameRoutine), hModule, NULL, nullptr))
		CloseHandle(threadHandle);

	DisableThreadLibraryCalls(hModule);

	return TRUE;
}