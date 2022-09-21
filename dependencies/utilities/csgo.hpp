#pragma once
#include <windows.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <array>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <intrin.h>
#include <filesystem>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Lua-5.3.5.lib")

#include "../../core/menu/imgui/imgui.h"
#include "../../core/menu/imgui/imgui_impl_dx9.h"
#include "../../core/menu/imgui/imgui_impl_win32.h"

#include "../utilities/singleton.hpp"
#include "../utilities/fnv.hpp"
#include "../utilities/utilities.hpp"
#include "../../dependencies/minhook/minhook.h"
#include "../interfaces/interfaces.hpp"
#include "../../source-sdk/sdk.hpp"
#include "../../core/hooks/hooks.hpp"
#include "../../dependencies/math/math.hpp"
#include "../../dependencies/utilities/renderer/renderer.hpp"
#include "../../dependencies/utilities/console/console.hpp"
#include "../utilities/csgo.hpp"
#include "../../core/security/xorstr.h"

#include "../json/json.hpp"
//interfaces
#define sig_client_state XorStr("A1 ? ? ? ? 8B 80 ? ? ? ? C3")
#define sig_directx XorStr("A1 ? ? ? ? 50 8B 08 FF 51 0C")
#define sig_input XorStr("B9 ? ? ? ? F3 0F 11 04 24 FF 50 10")
#define sig_glow_manager XorStr("0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00")
#define sig_player_move_helper XorStr("8B 0D ? ? ? ? 8B 46 08 68")
#define sig_weapon_data XorStr("8B 35 ? ? ? ? FF 10 0F B7 C0")

//misc
#define sig_apply_clan_tag XorStr("53 56 57 8B DA 8B F9 FF 15")
#define sig_cam_think XorStr("85 C0 75 30 38 86")
#define sig_set_angles XorStr("55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1")
#define sig_prediction_random_seed XorStr("8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04")

namespace csgo {
	extern player_t* local_player;
	extern bool send_packet;
	extern vec3_t angles;
	inline vec3_t real_angles_vector;
    float server_time(c_usercmd* = nullptr);
	extern c_usercmd* cmd;
}