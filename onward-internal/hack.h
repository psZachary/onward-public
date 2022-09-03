#pragma once
#include <Windows.h>

class hack {
public:
	DWORD rva;
	DWORD addition;
	DWORD byte;
	DWORD len;
	hack(DWORD rva, DWORD addition, DWORD byte, DWORD len) {
		this->rva = rva;
		this->addition = addition;
		this->byte = byte;
		this->len = len;
	}
};

// public class Pickup_Gun : Pickup // TypeDefIndex: 10926
// public void Recoil() { }
static hack* no_recoil;


static void initialize_hacks() {
	no_recoil = new hack(0x6737D0, 0x24F, 0x90, 5);
}

static void patch_recoil() {
	DWORD oldprotect = 0;
	VirtualProtect((void*)((uintptr_t)GetModuleHandleA("GameAssembly.dll") + no_recoil->rva + no_recoil->addition), 5, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset((void*)((uintptr_t)GetModuleHandleA("GameAssembly.dll") + no_recoil->rva + no_recoil->addition), no_recoil->byte, no_recoil->len);
}



