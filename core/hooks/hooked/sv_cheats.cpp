#include "../hooks.hpp"

bool __fastcall hooks::sv_cheats_get_bool::hook(PVOID convar, int edx) {
	static auto cam_think = utilities::pattern_scan("client.dll", sig_cam_think);

	if (!convar)
		return false;

	if ((_ReturnAddress()) == cam_think && csgo::local_player && csgo::local_player->is_alive())
		return true;
	else
		return sv_cheats_get_bool::original(convar);
}