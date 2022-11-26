#include <iostream>
#include <Windows.h>
#include "min/include/MinHook.h"
#include "hook.h"
#include "icallable.h"
#include "class.h"

int main() {

    hook_dx11();

    uintptr_t mod = (uintptr_t)GetModuleHandleA("GameAssembly.dll");

    initialize_callables(mod);

    auto [line, status] = initialize_hooks(mod);

    if (status != MH_OK) {
        printf("error %i loading hooks on line: %i\n", status, line);
        Sleep(5000);
        exit(0);
    }

    
   

    return 0;
}