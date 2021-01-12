#include "entry.h"

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

uint32_t WINAPI gameRoutine(HINSTANCE instance)
{
#ifdef _DEBUG
	AllocConsole();

	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout); 
#endif

	globals::shouldRelease = false;

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
	
		if (!interfaces::initializer())
			throw std::runtime_error("Failed to initialize");

		if (!hooking::initializer())
			throw std::runtime_error("Failed to initialize");
	}
	catch (const std::exception& err)
	{
#ifdef _DEBUG
		puts(err.what());
		MessageBoxA(0, err.what(), "Initialization", 0);
#endif
		globals::shouldRelease = true;
	}

#ifdef COUNT_ALLOCATIONS
	printf("Allocations: %d\n", allocCount);
#endif

	while (!globals::shouldRelease)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	hooking::release();

	gAddresses.~addressesWrapper();
	gModules.~modulesWrapper();

#ifdef _DEBUG
	fclose(stdin);
	fclose(stdout);

	FreeConsole(); 
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