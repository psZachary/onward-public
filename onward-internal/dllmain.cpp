#include <iostream>
#include <Windows.h>
#include "main.h"

int __stdcall DllMain(HINSTANCE__* hmod, unsigned long long  call_reason, void* reserved)
{
    if (call_reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hmod);

        // I don't think you need to createthread but it doesn't hurt so why not
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
    }
    return TRUE;
}

