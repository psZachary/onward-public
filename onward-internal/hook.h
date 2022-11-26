#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <tuple>
#include "mathn.h"
#include "cvar.h"
#include "render.h"
#include "class.h"
#include "icallable.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

uintptr_t cached_local_wps = 0;

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    if (uMsg == WM_KEYDOWN) {
        if (wParam == cvar::menu::menu_toggle) {
            cvar::menu::is_open = !cvar::menu::is_open;
        }
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

#define failcheck(x) if (x != MH_OK) return std::tuple<int, MH_STATUS>(__LINE__, x)


using p_GetUpdatedOutlineColor = unity::color(__stdcall*)(uintptr_t);
p_GetUpdatedOutlineColor i_GetUpdatedOutlineColor = 0;
static unity::color h_GetUpdatedOutlineColor(uintptr_t _this) {
    if (cvar::visuals::chams) {
        unity::color color;

        if (cvar::visuals::team_color_chams) {
            auto ret = i_GetUpdatedOutlineColor(_this);

            // Mult by 255 for brightness 
            color.r = ret.r * 255;
            color.g = ret.g * 255;
            color.b = ret.b * 255;
        }
        else {
            // Mult by 255 for brightness 
            color.r = cvar::visuals::chams_color[0] * 255;
            color.g = cvar::visuals::chams_color[1] * 255;
            color.b = cvar::visuals::chams_color[2] * 255;
        }

        // Set alpha (brightness) really high
        color.a = 255;

        return color;
    }
    else {
        return i_GetUpdatedOutlineColor(_this);
    }
}




using p_GetUpdatedOutlineActive = bool(__stdcall*)(uintptr_t);
p_GetUpdatedOutlineActive i_GetUpdatedOutlineActive = 0;
static bool h_GetUpdatedOutlineActive(uintptr_t _this) {
    if (cvar::visuals::chams) {
        return true;
    }
    else {
        return i_GetUpdatedOutlineActive(_this);
    }
}

using p_GetFireMode = int(__stdcall*)(uintptr_t);
p_GetFireMode i_GetFireMode = 0;
static int h_GetFireMode(uintptr_t _this) {

    if (cvar::weapon::override_firemode) {
        //*(int*)(_this + 0x2C) = cvar::weapon::firemode;
        return cvar::weapon::firemode;
    }
    else {
        return i_GetFireMode(_this);
    }
}

using p_Pickup_Gun_Awake = void(__stdcall*)(uintptr_t);
p_Pickup_Gun_Awake i_Pickup_Gun_Awake = 0;
static void h_Pickup_Gun_Awake(uintptr_t _this) {
    uintptr_t weapon_so = *(uintptr_t*)(_this + 0x368);
    uintptr_t weapon_info = *(uintptr_t*)(weapon_so + 0x80);
    uintptr_t weapon = *(uintptr_t*)(_this + 0x370);
    uintptr_t weapon_data = *(uintptr_t*)(weapon + 0xD8);

    printf("Crashed on me! \n");
    if (cvar::weapon::infinite_ammo) {
        // works for RPG 
        *(int*)(weapon + 0xA4) = 9999;
        //*(int*)(weapon + 0xFC) = 99999;
    }
    printf("Crashed on me! 2 \n");

    if (cvar::weapon::no_kickback) {
        // 	public float RecoilKickBackMin; // 0xF0
        // public float RecoilKickBackMax; // 0xF4
        *(float*)(weapon_so + 0xF0) = 0.01f;
        *(float*)(weapon_so + 0xF4) = 0.01f;
    }
    printf("Crashed on me! 3 \n");

    if (cvar::weapon::no_spread) {
        // remove spread
        *(float*)(weapon_so + 0xE0) = 0;
    }
    printf("Crashed on me! 4 \n");

    if (cvar::weapon::no_recoil) {
        // removed recoil
        // 	public bool HasRecoil; // 0xEA
        *(bool*)(weapon_so + 0xEA) = 0;

        *(float*)(weapon_so + 0xD8) = 0;
    }

    printf("Crashed on me! 5 \n");

    //public int WeaponCost; // 0x40
    *(int*)(weapon_so + 0x40) = 0;
    printf("Crashed on me! 6 \n");

    // 	public float RateOfFire; // 0xD8
    *(float*)(weapon_so + 0xD8) *= cvar::weapon::fire_rate_multiplier;
    printf("Crashed on me! 7 \n");

    // 	public int MagazineCapacity; // 0x120
    // public int StartingMagCount; // 0x124
    printf("Crashed on me! 8 \n");

    if (cvar::weapon::infinite_ammo) {
        *(int*)(weapon_so + 0x120) = 9999;
        *(int*)(weapon_so + 0x124) = 9999;
    }



    //*(int*)(weapon_so + 0x104) = cvar::weapon::ammo_type;

    return i_Pickup_Gun_Awake(_this);
}


// Use for later
using p_WPSOnUpdate = void(__stdcall*)(uintptr_t);
p_WPSOnUpdate i_WPSOnUpdate = 0;
static void h_WPSOnUpdate(uintptr_t _this) {

    return i_WPSOnUpdate(_this);
}





using p_Get_Point_Cost = int(__stdcall*)(uintptr_t);
p_Get_Point_Cost i_Get_Point_Cost = 0;
static int h_Get_Point_Cost(uintptr_t _this) {
    if (cvar::misc::infinite_points) {
        return 0;
    }
    else return i_Get_Point_Cost(_this);
}


using p_GetCurrentHealth = float(__stdcall*)(uintptr_t);
p_GetCurrentHealth i_GetCurrentHealth = 0;
static float h_GetCurrentHealth(uintptr_t _this) {
    if (cached_local_wps && _this == cached_local_wps && cvar::misc::god_mode) {
        return 999999.f;
    }
    return i_GetCurrentHealth(_this);
}


using p_Movement_Update = vec3(__stdcall*)(uintptr_t _this, float move_speed);
p_Movement_Update i_Movement_Update = 0;
static vec3 h_Movement_Update(uintptr_t _this, float move_speed) {





    move_speed *= cvar::misc::movement_speed_multiplier;
    return i_Movement_Update(_this, move_speed);
}

using p_FlashMe = void(__stdcall*)(uintptr_t);
p_FlashMe i_FlashMe = 0;
static void h_FlashMe(uintptr_t _this) {
    if (cvar::visuals::anti_flash) {
        return;
    }
    else {
        return i_FlashMe(_this);
    }
}

using p_LaserStart = void(__stdcall*)(uintptr_t);
p_LaserStart i_LaserStart = 0;
static void h_LaserStart(uintptr_t _this) {
    if (cvar::visuals::bright_laser) {
        *(bool*)(_this + 0x48) = true;
        *(bool*)(_this + 0x38) = true;
        *(bool*)(_this + 0x25) = false;
        *(float*)(_this + 0x90) = 9999;
        *(float*)(_this + 0x94) = 0.01f;
        unity::color color;
        color.r = 0;
        color.a = 255;
        color.g = 255;
        color.b = 0;
        laser_set_line_color(_this, color);
    }
    return i_LaserStart(_this);
}

using p_TaserStart = void(__stdcall*)(uintptr_t);
p_TaserStart i_TaserStart = 0;
static void h_TaserStart(uintptr_t _this) {
    if (cvar::weapon::infinite_ammo) {
        *(int*)(_this + 0x3BC) = 9999;
    }
    return i_TaserStart(_this);
}


static std::tuple<int, MH_STATUS> initialize_hooks(uintptr_t mod) {
    auto stat = MH_Initialize();
    if (stat != MH_STATUS::MH_ERROR_ALREADY_INITIALIZED)
        failcheck(stat);

    // public class Pickup_Gun : Pickup (Awake)
    stat = MH_CreateHook((void*)(mod + 0x413590), &h_Pickup_Gun_Awake, reinterpret_cast<LPVOID*>(&i_Pickup_Gun_Awake));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x413590));
    failcheck(stat);

    // protected bool GetUpdatedOutlineActive() { }
    stat = MH_CreateHook((void*)(mod + 0x4D5530), &h_GetUpdatedOutlineActive, reinterpret_cast<LPVOID*>(&i_GetUpdatedOutlineActive));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x4D5530));
    failcheck(stat);

    // private Vector3 MovePlayer(float) { }
    stat = MH_CreateHook((void*)(mod + 0x4A2340), &h_Movement_Update, reinterpret_cast<LPVOID*>(&i_Movement_Update));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x4A2340));
    failcheck(stat);

    // public int GetConsumedPoints() { }
    stat = MH_CreateHook((void*)(mod + 0x5E3A10), &h_Get_Point_Cost, reinterpret_cast<LPVOID*>(&i_Get_Point_Cost));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x5E3A10));
    failcheck(stat);

    // public void FlashMe() { }
    stat = MH_CreateHook((void*)(mod + 0x3810D0), &h_FlashMe, reinterpret_cast<LPVOID*>(&i_FlashMe));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x3810D0));
    failcheck(stat);


    //protected Color GetUpdatedOutlineColor() { }
    stat = MH_CreateHook((void*)(mod + 0x4D5BE0), &h_GetUpdatedOutlineColor, reinterpret_cast<LPVOID*>(&i_GetUpdatedOutlineColor));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x4D5BE0));
    failcheck(stat);

    // public float get_CurrentHealth() { }
    stat = MH_CreateHook((void*)(mod + 0x38F9A0), &h_GetCurrentHealth, reinterpret_cast<LPVOID*>(&i_GetCurrentHealth));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x38F9A0));
    failcheck(stat);

    // public Firemode get_CurrentFiremode() { }
    stat = MH_CreateHook((void*)(mod + 0x41F940), &h_GetFireMode, reinterpret_cast<LPVOID*>(&i_GetFireMode));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x41F940));
    failcheck(stat);


    // public override void OnStart() { }public class Pickup_Taser : Pickup 
    stat = MH_CreateHook((void*)(mod + 0x4BAEB0), &h_TaserStart, reinterpret_cast<LPVOID*>(&i_TaserStart));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0x4BAEB0));
    failcheck(stat);

    // private void Start() { } public class BasicLaser_v2 : MonoBehaviour
    stat = MH_CreateHook((void*)(mod + 0xC8DEC0), &h_LaserStart, reinterpret_cast<LPVOID*>(&i_LaserStart));
    failcheck(stat);
    stat = MH_EnableHook((void*)(mod + 0xC8DEC0));
    failcheck(stat);


    return std::tuple<int, MH_STATUS>(0, MH_OK);
}

bool init = false;
static HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;
        }

        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    render();

    ImGui::Render();

    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
}

static void hook_dx11() {
    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11))
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
        }
        else {

        }
    } while (!init_hook);
}