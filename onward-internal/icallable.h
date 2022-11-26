#pragma once
#include "class.h"
#include <Windows.h>
#include "kiero/imgui/imgui.h"




using p_GetMainCamera = uintptr_t(__cdecl*)();
static p_GetMainCamera get_main_camera = 0;

//using p_DrawLine = uintptr_t(__cdecl*)(uintptr_t, unity::vector, unity::vector, ImColor);
//static p_DrawLine draw_line = 0;

/*

		_
	   (_)
 ____   _   ____   ____  _____   ____
|  _ \ | | / _  | / _  || ___ | / ___)
| | | || |( (_| |( (_| || ____|| |
|_| |_||_| \___ | \___ ||_____)|_|
		  (_____|(_____|


*/
using p_GetComponentTransform = uintptr_t(__cdecl*)(uintptr_t);
static p_GetComponentTransform get_component_transform = 0;

using p_TransformGetPosition = unity::vector(__cdecl*)(uintptr_t);
static p_TransformGetPosition get_transform_position = 0;


using p_DrawLine = void(__cdecl*)(float, unity::vector, unity::vector);
static p_DrawLine draw_line = 0;

using p_LaserSetLineColor = void(__cdecl*)(uintptr_t, unity::color);
static p_LaserSetLineColor laser_set_line_color = 0;

void initialize_callables(uintptr_t mod) {
	// public static Camera get_main() { }
	//get_main_camera = (p_GetMainCamera)(mod + 0x169D9D0);
	// private static void DrawLine(float thickness, Vector3 start, Vector3 end) { }
	//draw_line = (p_DrawLine)(mod + 0x182CD90);
	// private void SetLineColor(Color c) { }
	laser_set_line_color = (p_LaserSetLineColor)(mod + 0xC8DBC0);

	//public Transform get_transform() { }
	//get_component_transform = (p_GetComponentTransform)(mod + 0x16A1600);

	// public Vector3 get_position() { } : Transform 
	//get_transform_position = (p_TransformGetPosition)(mod + 0x1780F80);



}