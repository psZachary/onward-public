#pragma once
#include "kiero/imgui/imgui.h"
#include <Windows.h>

namespace cvar {
	namespace menu {
		static bool is_open = true;
		static int tab_index = 0;
		static DWORD menu_toggle = VK_INSERT;
	}
	namespace weapon {
		static bool no_kickback = false;
		static bool no_spread = false;
		static bool no_recoil = false;
		static float fire_rate_multiplier = 1.f;
		static bool infinite_ammo = false;
		static int ammo_type = 1;
		static bool override_firemode = false;
		static int firemode = 0;
		
	}
	namespace visuals {
		static bool chams = false;
		static bool team_color_chams = false;
		static float* chams_color = new float[3];
		static bool anti_flash = false;
		static bool bright_laser = false;
	}
	namespace misc {
		static float movement_speed_multiplier = 1;
		static bool infinite_points = false;
		static bool god_mode = false;
	}
}