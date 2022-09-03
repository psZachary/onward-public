#pragma once
#include "kiero/imgui/imgui.h"
#include "style.h"
#include "cvar.h"
#include "icallable.h"

#define tab_item(name, index) if (ImGui::Button(name, ImVec2(120.f, 25.000f))) { cvar::menu::tab_index = index; } 

static void render() {

	

	if (cvar::menu::is_open) {
		style::menu_style();

		ImGui::SetNextWindowSize(ImVec2(395, 425));

		ImGui::Begin("Onward Internal", 0, ImGuiWindowFlags_NoResize);

		tab_item("Visuals", 0)
			ImGui::SameLine();
		tab_item("Weapon Mods", 1)
			ImGui::SameLine();
		tab_item("Misc", 2)

			ImGui::Separator();

		// visuals
		if (cvar::menu::tab_index == 0) {
			ImGui::Checkbox("Chams", &cvar::visuals::chams);
			if (cvar::visuals::chams) {
				ImGui::Checkbox("Team Color Chams", &cvar::visuals::team_color_chams);
				ImGui::Text("Chams Color");
				ImGui::ColorPicker3("      ", cvar::visuals::chams_color, ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueBar);
			}
			
			ImGui::Checkbox("Anti Flash", &cvar::visuals::anti_flash);
			ImGui::Checkbox("Bright Laser", &cvar::visuals::bright_laser);
		}


		if (cvar::menu::tab_index == 1) {

			ImGui::Text("Fire Rate Multiplier");
			ImGui::SliderFloat("   ", &cvar::weapon::fire_rate_multiplier, 0.5, 20);
			ImGui::Checkbox("No Kickback", &cvar::weapon::no_kickback);
			ImGui::Checkbox("No Recoil", &cvar::weapon::no_recoil);
			ImGui::Checkbox("No Spread", &cvar::weapon::no_spread);
			ImGui::Checkbox("Infinite Ammo", &cvar::weapon::infinite_ammo);
			ImGui::Checkbox("Firemode Override", &cvar::weapon::override_firemode);
			if (cvar::weapon::override_firemode) {
				ImGui::Combo("Firemode", &cvar::weapon::firemode, "Automatic\0Semi\0Burst");
			}
		}

		if (cvar::menu::tab_index == 2) {
			ImGui::Text("Movement Speed Multiplier");
			ImGui::SliderFloat("     ", &cvar::misc::movement_speed_multiplier, 0, 5);
			ImGui::Checkbox("Infinite Points", &cvar::misc::infinite_points);
			ImGui::Checkbox("Godmode", &cvar::misc::god_mode);
		}


		ImGui::GetBackgroundDrawList()->AddText(ImVec2(0, 0), IM_COL32(255, 255, 255, 255), "Press INSERT to open / close menu");

		ImGui::End();
	}
}