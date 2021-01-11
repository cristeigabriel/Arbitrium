#include "console.h"

#include <cstdio>

cConsole::cConsole()
{
	AllocConsole();

    consoleWindow = GetConsoleWindow();

    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    static LONG_PTR style = GetWindowLongPtrA(consoleWindow, GWL_STYLE);
    SetWindowLongA(consoleWindow, GWL_STYLE, style & ~WS_SIZEBOX & ~WS_SYSMENU);

    printf("Console object created\n");
}

cConsole::~cConsole()
{
    fclose(stdin);
    fclose(stdout);

    FreeConsole();
    PostMessageW(consoleWindow, WM_CLOSE, NULL, NULL);
    Beep(10, 1000);
}