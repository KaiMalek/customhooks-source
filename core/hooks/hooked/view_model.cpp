#include "../hooks.hpp"

float __fastcall hooks::view_model::hook() {
	if (csgo::local_player && csgo::local_player->is_alive())
		return view_model::original() + variables::config::visuals_view_model_fov;
	else
		return view_model::original();
}
