#include "../features.hpp"
#include "../../security/security-includes.h"

#define clamp(val, min, max) (((val) > (max)) ? (max) : (((val) < (min)) ? (min) : (val)))

#if RELEASE
#if BETA
#define VERSION crypt_str("customhooks [alpha] | ")
#else
#define VERSION crypt_str("customhooks [beta] | ")
#endif
#else
#define VERSION crypt_str("customhooks [alpha] | ")
#endif

#define VERSIONxx crypt_str("xx")

void visuals::watermark() { // rework the menu
	if (!variables::config::watermark)
		return;

	const bool connected = interfaces::engine->is_connected(); //is_connected check

	time_t t = std::time(nullptr); // time not used in the watermark for now
	tm tm = *std::localtime(&t);
	// time not used in the watermark for now
	std::ostringstream oss;
	oss << std::put_time(&tm, "%I:%M%p");
	auto time = oss.str();

	// x y screen check size
	int x, y;
	interfaces::engine->get_screen_size(x, y);
	// check if the local_player is connected to a lobby
	if (connected)
	{
		render::draw_filled_rect(x * 0.91, y * 0.01f, 170, 25, color(110, 110, 110, 255)); // outline AAAAaa 110 rgb

		render::draw_filled_rect(x * 0.912, y * 0.013f, 162, 19, color(0, 0, 0, 255)); // inner outline 0 rgba (black) 
		render::draw_filled_rect(x * 0.91, y * 0.01f + 25, 170, 2, color(0, 0, 0, 255)); // bottom line 
		render::draw_filled_rect(x * 0.91, y * -0.013f + 25, 170, 2, color(0, 0, 0, 255)); // top line 
		render::draw_filled_rect(x * 0.91, y * -0.013f + 25, 2, 25, color(0, 0, 0, 255)); // left line
		render::draw_filled_rect(x * 0.9975, y * -0.013f + 25, 2, 25, color(0, 0, 0, 255)); // right line
		auto tickrate = std::to_string((int)(1.0f / interfaces::globals->interval_per_tick));
		render::text(x * 0.917f, y * 0.016f, render::fonts::watermark_font, VERSION + tickrate + "  ticks", false, color(255, 255, 255));
	}
	else // if not 
	{
		auto xx = std::string("xx");

		render::draw_filled_rect(x * 0.91, y * 0.01f, 170, 25, color(110, 110, 110, 255)); // outline AAAAaa 110 rgb

		render::draw_filled_rect(x * 0.912, y * 0.013f, 162, 19, color(0, 0, 0, 255)); // inner outline 0 rgba (black) 
		render::draw_filled_rect(x * 0.91, y * 0.01f + 25, 170, 2, color(0, 0, 0, 255)); // bottom line 
		render::draw_filled_rect(x * 0.91, y * -0.013f + 25, 170, 2, color(0, 0, 0, 255)); // top line 
		render::draw_filled_rect(x * 0.91, y * -0.013f + 25, 2, 25, color(0, 0, 0, 255)); // left line
		render::draw_filled_rect(x * 0.9975, y * -0.013f + 25, 2, 25, color(0, 0, 0, 255)); // right line
		auto tickrate = std::to_string((int)(1.0f / interfaces::globals->interval_per_tick));
		render::text(x * 0.917f, y * 0.016f, render::fonts::watermark_font, VERSION + xx + "  ticks", false, color(255, 255, 255));
	}
}

void visuals::showimpacts()
{
	if (!csgo::local_player)
		return;

	convar* sv_showimpacts = interfaces::console->get_convar("sv_showimpacts");
	*(int*)((DWORD)&sv_showimpacts->callbacks + 0xC) = 0;

	if (variables::config::showimpacts)
		sv_showimpacts->set_value(1);

	if (!variables::config::showimpacts)
		sv_showimpacts->set_value(0);
}

void visuals::remove_3dsky()
{
	static auto mat_postprocess_enable = interfaces::console->get_convar("r_3dsky");
	mat_postprocess_enable->set_value(variables::config::remove_3dsky ? 0 : 1);
}

void visuals::disable_post_processing() noexcept
{
	static auto mat_postprocess_enable = interfaces::console->get_convar("mat_postprocess_enable");
	mat_postprocess_enable->set_value(variables::config::disable_post_processing ? 0 : 1);
}

void visuals::recoil_crosshair() noexcept 
{

	static auto cl_crosshair_recoil = interfaces::console->get_convar("cl_crosshair_recoil");
	cl_crosshair_recoil->set_value(variables::config::recoil_crosshair ? 1 : 0);
}

void visuals::force_crosshair() noexcept
{
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	static auto weapon_debug_spread_show = interfaces::console->get_convar("weapon_debug_spread_show");

	if (local_player && local_player->health() > 0) {
		weapon_debug_spread_show->set_value(local_player->is_scoped() || !variables::config::force_crosshair ? 0 : 3);
	}
}

void visuals::remove_scope() noexcept {
	if (!variables::config::remove_scope)
		return;

	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game())
		return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	if (local_player && !local_player->is_scoped())
		return;

	int w, h;
	interfaces::engine->get_screen_size(w, h);
	interfaces::surface->set_drawing_color(0, 0, 0, 255);
	interfaces::surface->draw_line(0, h / 2, w, h / 2);
	interfaces::surface->draw_line(w / 2, 0, w / 2, h);
}


bool visuals::get_playerbox(player_t* ent, box& in) {

	vec3_t origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	int left, top, right, bottom;

	origin = ent->abs_origin();
	min = ent->collideable()->mins() + origin;
	max = ent->collideable()->maxs() + origin;

	vec3_t points[] = {
		vec3_t(min.x, min.y, min.z),
		vec3_t(min.x, max.y, min.z),
		vec3_t(max.x, max.y, min.z),
		vec3_t(max.x, min.y, min.z),
		vec3_t(max.x, max.y, max.z),
		vec3_t(min.x, max.y, max.z),
		vec3_t(min.x, min.y, max.z),
		vec3_t(max.x, min.y, max.z)
	};
	if (!interfaces::debug_overlay->world_to_screen(points[3], flb) || !interfaces::debug_overlay->world_to_screen(points[5], brt)
		|| !interfaces::debug_overlay->world_to_screen(points[0], blb) || !interfaces::debug_overlay->world_to_screen(points[4], frt)
		|| !interfaces::debug_overlay->world_to_screen(points[2], frb) || !interfaces::debug_overlay->world_to_screen(points[1], brb)
		|| !interfaces::debug_overlay->world_to_screen(points[6], blt) || !interfaces::debug_overlay->world_to_screen(points[7], flt))
		return false;

	vec3_t arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	for (int i = 1; i < 8; i++) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}
	in.x = (int)left;
	in.y = (int)top;
	in.w = int(right - left);
	in.h = int(bottom - top);


	return true;
}

void visuals::draw_box(player_t* ent, box bbox)
{
	if (!(variables::config::draw_box)) return;

	render::draw_rect(bbox.x, bbox.y, bbox.w, bbox.h, color(255, 255, 255, 255)); // For Corner Boxes: render::draw_rect(bbox.x, bbox.y, bbox.w * 0.25, bbox.h * 0.25, color(255, 255, 255, 255));
	render::draw_rect(bbox.x - 1, bbox.y - 1, bbox.w + 2, bbox.h + 2, color(0, 0, 0, 170)); // For Corner Boxes: render::draw_rect(bbox.x - 1, bbox.y - 1, (bbox.w + 2) * 0.25, (bbox.h + 2) * 0.25, color(0, 0, 0, 170)); 
	render::draw_rect(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, color(0, 0, 0, 170)); // For Corner Boxes: render::draw_rect(bbox.x + 1, bbox.y + 1, (bbox.w - 2) * 0.25, (bbox.h - 2) * 0.25, color(0, 0, 0, 170));
}

void visuals::draw_name(player_t* entity, visuals::box bbox) {

	if (!variables::config::draw_name)
		return;


	float alpha[65] = { 255 };

	static float lastDormantTime[65] = { 0 }, lastNonDormantTime[65] = { 0 }; // 64 maxplayers so 1-65 as entindex
	float fadespeed = 1.0; // adding this so you can modify it, fadeout speed in seconds 1.0 = 1s 0.5 = 0.5s etc
	int eid = entity->index(); // calling it once would be a better option
	if (entity->dormant())
	{
		lastDormantTime[eid] = interfaces::globals->realtime;
		alpha[eid] = clamp((lastNonDormantTime[eid] - interfaces::globals->realtime) * (255.f / fadespeed), 0, 255);
	}
	else // you don't need an if here since its either true or false
	{
		lastNonDormantTime[eid] = interfaces::globals->realtime + fadespeed;
		alpha[eid] = clamp((interfaces::globals->realtime - lastDormantTime[eid]) * (255.f / fadespeed), 0, 255);
	}
	player_info_t info;

	interfaces::engine->get_player_info(entity->index(), &info);

	render::text(bbox.x + (bbox.w / 2), bbox.y - 15, render::fonts::watermark_font, info.name, true, color(255, 255, 255, alpha[eid]));
}

void visuals::draw_hp(player_t* entity, visuals::box bbox) {

	if (!variables::config::draw_hp)
		return;

	float alpha[65] = { 255 };

	static float lastDormantTime[65] = { 0 }, lastNonDormantTime[65] = { 0 }; // 64 maxplayers so 1-65 as entindex
	float fadespeed = 1.0; // adding this so you can modify it, fadeout speed in seconds 1.0 = 1s 0.5 = 0.5s etc
	int eid = entity->index(); // calling it once would be a better option
	if (entity->dormant())
	{
		lastDormantTime[eid] = interfaces::globals->realtime;
		alpha[eid] = clamp((lastNonDormantTime[eid] - interfaces::globals->realtime) * (255.f / fadespeed), 0, 255);
	}
	else // you don't need an if here since its either true or false
	{
		lastNonDormantTime[eid] = interfaces::globals->realtime + fadespeed;
		alpha[eid] = clamp((interfaces::globals->realtime - lastDormantTime[eid]) * (255.f / fadespeed), 0, 255);
	}

	int entity_health = entity->health();

	int hp_bar = bbox.h * (entity_health / 100.f);


	color hp_color = color(0, 0, 0, alpha[eid]);

	if (entity_health >= 51)
		hp_color = color(0, 255, 0, alpha[eid]);
	else if (entity_health <= 50 && entity_health > 10)
		hp_color = color(255, 205, 1, alpha[eid]);
	else if (entity_health <= 10)
		hp_color = color(255, 0, 0, alpha[eid]);

	render::draw_filled_rect(bbox.x - 7, bbox.y - 1, 4, bbox.h + 2, color(35, 35, 35, alpha[eid]));
	render::draw_filled_rect(bbox.x - 6, bbox.y + bbox.h - hp_bar, 2, hp_bar, hp_color);

	if (entity_health < 100)
		render::text(bbox.x - 8, bbox.y + bbox.h - hp_bar - 12, render::fonts::watermark_font, std::to_string(entity->health()), false, color(255, 255, 255, alpha[eid]));
}

void visuals::draw_weapon(player_t* entity, visuals::box bbox) {

	if (!variables::config::draw_weapon)
		return;

	float alpha[65] = { 255 };

	static float lastDormantTime[65] = { 0 }, lastNonDormantTime[65] = { 0 }; // 64 maxplayers so 1-65 as entindex
	float fadespeed = 1.0; // adding this so you can modify it, fadeout speed in seconds 1.0 = 1s 0.5 = 0.5s etc
	int eid = entity->index(); // calling it once would be a better option
	if (entity->dormant())
	{
		lastDormantTime[eid] = interfaces::globals->realtime;
		alpha[eid] = clamp((lastNonDormantTime[eid] - interfaces::globals->realtime) * (255.f / fadespeed), 0, 255);
	}
	else // you don't need an if here since its either true or false
	{
		lastNonDormantTime[eid] = interfaces::globals->realtime + fadespeed;
		alpha[eid] = clamp((interfaces::globals->realtime - lastDormantTime[eid]) * (255.f / fadespeed), 0, 255);
	}


	weapon_t* weapon = reinterpret_cast<weapon_t*>(entity->active_weapon());

	if (!weapon)
		return;

	std::string weapon_name = weapon->get_weapon_data()->weapon_name;

	weapon_name.erase(0, 7);
	std::transform(weapon_name.begin(), weapon_name.end(), weapon_name.begin(), tolower);

	if (variables::config::draw_ammo) {

		if (weapon->clip1_count() >= 0)
			render::text(bbox.x + (bbox.w / 2), bbox.y + (bbox.h + 6), render::fonts::watermark_font, weapon_name, true, color(255, 255, 255, alpha[eid]));
		else
			render::text(bbox.x + (bbox.w / 2), bbox.y + (bbox.h), render::fonts::watermark_font, weapon_name, true, color(255, 255, 255, alpha[eid]));
	}
	else
		render::text(bbox.x + (bbox.w / 2), bbox.y + (bbox.h), render::fonts::watermark_font, weapon_name, true, color(255, 255, 255, alpha[eid]));

}

void visuals::draw_ammo(player_t* entity, visuals::box bbox) {

	if (!variables::config::draw_ammo)
		return;


	float alpha[65] = { 255 };

	static float lastDormantTime[65] = { 0 }, lastNonDormantTime[65] = { 0 }; // 64 maxplayers so 1-65 as entindex
	float fadespeed = 1.0; // adding this so you can modify it, fadeout speed in seconds 1.0 = 1s 0.5 = 0.5s etc
	int eid = entity->index(); // calling it once would be a better option
	if (entity->dormant())
	{
		lastDormantTime[eid] = interfaces::globals->realtime;
		alpha[eid] = clamp((lastNonDormantTime[eid] - interfaces::globals->realtime) * (255.f / fadespeed), 0, 255);
	}
	else // you don't need an if here since its either true or false
	{
		lastNonDormantTime[eid] = interfaces::globals->realtime + fadespeed;
		alpha[eid] = clamp((interfaces::globals->realtime - lastDormantTime[eid]) * (255.f / fadespeed), 0, 255);
	}

	weapon_t* weapon = reinterpret_cast<weapon_t*>(entity->active_weapon());

	if (!weapon)
		return;

	int weapon_ammo = weapon->clip1_count();

	if (weapon_ammo < 0)
		return;

	int weapon_ammo_bar = weapon_ammo * bbox.w / weapon->get_weapon_data()->weapon_max_clip;

	render::draw_filled_rect(bbox.x - 1, bbox.y + bbox.h + 3, bbox.w + 2, 4, color(0, 0, 0, alpha[eid]));
	render::draw_filled_rect(bbox.x, bbox.y + bbox.h + 4, weapon_ammo_bar, 2, color(255, 0, 0, alpha[eid]));

	if (!(weapon_ammo <= weapon->get_weapon_data()->weapon_max_clip / 4)) return;

	render::text((bbox.x + 10) + weapon_ammo_bar - 6, bbox.y + bbox.h - 2, render::fonts::watermark_font, std::to_string(weapon_ammo), true, color(255, 255, 255, alpha[eid]));

}

// Player ESP/Player Visuals

void visuals::draw_info(player_t* entity, visuals::box bbox) {

	static int offset;
	offset = 0;

	float alpha[65] = { 255 };

	static float lastDormantTime[65] = { 0 }, lastNonDormantTime[65] = { 0 }; // 64 maxplayers so 1-65 as entindex
	float fadespeed = 1.0; // adding this so you can modify it, fadeout speed in seconds 1.0 = 1s 0.5 = 0.5s etc
	int eid = entity->index(); // calling it once would be a better option
	if (entity->dormant())
	{
		lastDormantTime[eid] = interfaces::globals->realtime;
		alpha[eid] = clamp((lastNonDormantTime[eid] - interfaces::globals->realtime) * (255.f / fadespeed), 0, 255);
	}
	else // you don't need an if here since its either true or false
	{
		lastNonDormantTime[eid] = interfaces::globals->realtime + fadespeed;
		alpha[eid] = clamp((interfaces::globals->realtime - lastDormantTime[eid]) * (255.f / fadespeed), 0, 255);
	}


	player_info_t info;
	interfaces::engine->get_player_info(entity->index(), &info);

	if (variables::config::draw_bot_check && info.fakeplayer) {
		render::text(bbox.x + bbox.w + 5, bbox.y, render::fonts::watermark_font, "bot", false, color(255, 255, 255, alpha[eid]));
		offset += 11;
	}

	if (variables::config::draw_zoom_check) {
		if (entity->is_scoped()) {
			render::text(bbox.x + bbox.w + 5, bbox.y + offset, render::fonts::watermark_font, "zoom", false, color(255, 255, 255, alpha[eid]));
			offset += 11;
		}
	}

	if (variables::config::draw_money) {
		std::string money = std::to_string(entity->money()) + "$";
		render::text(bbox.x + bbox.w + 5, bbox.y + offset, render::fonts::watermark_font, money, false, color(255, 200, 0, alpha[eid]));
		offset += 11;
	}

	if (variables::config::draw_hk) {

		if (entity->armor() > 0 && !entity->has_helmet())
			render::text(bbox.x + bbox.w + 5, bbox.y + offset, render::fonts::watermark_font, "k", false, color(255, 255, 255, alpha[eid]));
		else if (entity->armor() > 0 && entity->has_helmet())
			render::text(bbox.x + bbox.w + 5, bbox.y + offset, render::fonts::watermark_font, "hk", false, color(255, 255, 255, alpha[eid]));
	}

	if (variables::config::draw_is_flashed && entity->not_flashed() > 75.0) {
		render::text(bbox.x + (bbox.w / 2), bbox.y - 25, render::fonts::watermark_font, "flashed", true, color(255, 255, 255, alpha[eid]));
	}
}

std::string clean_item_name(std::string name) {
	std::string Name = name;

	auto weapon_start = Name.find("CWeapon");
	if (weapon_start != std::string::npos)
		Name.erase(Name.begin() + weapon_start, Name.begin() + weapon_start + 7);

	if (Name[0] == '_')
		Name.erase(Name.begin());

	if (Name[0] == 'C') //optional for dropped weapons - designer
		Name.erase(Name.begin());

	return Name;
}

void visuals::grenades_draw(entity_t* entity) {

	if (!variables::config::draw_projectile)
		return;

	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
		return;

	if (!csgo::local_player)
		return;

	if (!entity)
		return;

	vec3_t origin = entity->origin(), w2s;

	if (math::world_to_screen(origin, w2s)) {

		auto class_id = entity->client_class()->class_id;

		switch (class_id) {

		case cbasecsgrenadeprojectile: {

			const model_t* model = entity->model();

			if (!model)
				return;

			studio_hdr_t* hdr = interfaces::model_info->get_studio_model(model);

			if (!hdr)
				return;

			std::string name = hdr->name_char_array;

			if (name.find("incendiarygrenade") != std::string::npos || name.find("fraggrenade") != std::string::npos) {

				render::text(w2s.x, w2s.y, render::fonts::watermark_font, "FRAG", true, color(255, 255, 255));

				break;
			}

			render::text(w2s.x, w2s.y, render::fonts::watermark_font, "FLASH", true, color(255, 255, 255));

		}
									 break;
		case cmolotovprojectile:
		case cinferno: {

			render::text(w2s.x, w2s.y, render::fonts::watermark_font, "FIRE", true, color(255, 255, 255));

		}
					 break;
		case csmokegrenadeprojectile: {
			render::text(w2s.x, w2s.y, render::fonts::watermark_font, "SMOKE", true, color(255, 255, 255));
		}
									break;
		case cdecoyprojectile: {
			render::text(w2s.x, w2s.y, render::fonts::watermark_font, "DECOY", true, color(255, 255, 255));
		}
							 break;
		default: break;
		}
	}

}

void visuals::radar(player_t* entity) {

	if (!entity
		|| !csgo::local_player
		|| !entity->is_alive()
		|| entity == csgo::local_player
		|| entity->dormant())
		return;

	entity->spotted() = variables::config::radar_spotted ? 1 : 0;
}

void visuals::spectator_list_draw() {

	if (!variables::config::draw_spectators)
		return;

	if (!csgo::local_player)
		return;

	auto text_y_offset = 5; // yea
	int screen[2]{};

	interfaces::engine->get_screen_size(screen[0], screen[1]);

	player_t* spec_player = csgo::local_player->is_alive() ? csgo::local_player : reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(csgo::local_player->observer_target()));

	if (!spec_player)
		return;

	for (int i = 1; i <= interfaces::globals->max_clients; ++i) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		if (!entity || entity->dormant() || entity->is_alive() || reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(entity->observer_target())) != spec_player || entity == csgo::local_player)
			continue;
		player_info_t player_info;

		interfaces::engine->get_player_info(i, &player_info); // bypasing ipv88 and connecting localling to the masterlloser mainfraim

		if (wchar_t name[128]; MultiByteToWideChar(CP_UTF8, 0, player_info.name, -1, name, 128)) {
			int text_width, text_height;
			interfaces::surface->get_text_size(render::fonts::watermark_font, name, text_width, text_height);
			render::text(screen[0] - text_height - 3, text_y_offset, render::fonts::watermark_font, name, false, color(255, 255, 255, 255));
			text_y_offset += text_height + 3;
		}
	}
}

void visuals::player_esp_render(player_t* entity) {

	if (!entity
		|| !csgo::local_player
		|| !entity->is_alive()
		|| entity == csgo::local_player
		|| entity->team() == csgo::local_player->team())
		return;

	box bbox;
	if (!visuals::get_playerbox(entity, bbox))
		return;

	visuals::radar(entity);

	if (variables::config::visible_check && csgo::local_player->can_see_player_pos(entity, entity->get_hitbox_position(hitbox_chest))) {

		draw_name(entity, bbox);

		draw_info(entity, bbox);

		draw_box(entity, bbox);

		draw_ammo(entity, bbox);

		draw_weapon(entity, bbox);

		draw_hp(entity, bbox);

	}
	else if (!variables::config::visible_check) {

		draw_name(entity, bbox);

		draw_info(entity, bbox);

		draw_box(entity, bbox);

		draw_ammo(entity, bbox);

		draw_weapon(entity, bbox);

		draw_hp(entity, bbox);

	}
}

void visuals::player_loop()
{
	for (int i = 1; i <= interfaces::globals->max_clients; ++i) {

		player_t* entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		player_esp_render(entity);

		radar(entity);
	}
}

void visuals::world_loop() {

	for (int i = 1; i <= interfaces::entity_list->get_highest_index(); ++i) {

		entity_t* entity = reinterpret_cast<entity_t*>(interfaces::entity_list->get_client_entity(i));

		grenades_draw(entity);
	}
}

std::string song_title = "";

static HWND spotify_hwnd = nullptr;
static float last_hwnd_time = 0.f;
int text_width = 0;

void visuals::spotify()
{
	if (variables::config::spotify)
	{
		if ((!spotify_hwnd || spotify_hwnd == INVALID_HANDLE_VALUE) && last_hwnd_time < interfaces::globals->realtime + 2.f) {
			for (HWND hwnd = GetTopWindow(0); hwnd; hwnd = GetWindow(hwnd, GW_HWNDNEXT)) {

				last_hwnd_time = interfaces::globals->realtime;

				if (!(IsWindowVisible)(hwnd))
					continue;

				int length = (GetWindowTextLengthW)(hwnd);
				if (length == 0)
					continue;

				WCHAR filename[300];
				DWORD pid;
				(GetWindowThreadProcessId)(hwnd, &pid);

				const auto spotify_handle = (OpenProcess)(PROCESS_QUERY_INFORMATION, FALSE, pid);
				(K32GetModuleFileNameExW)(spotify_handle, nullptr, filename, 300);

				std::wstring sane_filename{ filename };

				(CloseHandle)(spotify_handle);

				if (sane_filename.find((L"Spotify.exe")) != std::string::npos)
					spotify_hwnd = hwnd;
			}
		}
		else if (spotify_hwnd && spotify_hwnd != INVALID_HANDLE_VALUE) {
			WCHAR title[300];

			if (!(GetWindowTextW)(spotify_hwnd, title, 300)) {
				spotify_hwnd = nullptr;
			}
			else {
				std::wstring sane_title{ title };
				std::string Title = " ";
				std::string Song(sane_title.begin(), sane_title.end());
				Title += Song;
				if (sane_title.find((L"-")) != std::string::npos) {
					song_title = Title;
				}
				else if (sane_title.find((L"Advertisement")) != std::string::npos) {

					song_title = "advertisement";
				}
				else if (sane_title.find((L"Spotify")) != std::string::npos) {

					song_title = "stopped / not playing";
				}
				else {

					song_title = "advertisement";
				}

			}
		}
		int x, y;
		interfaces::engine->get_screen_size(x, y);

		setlocale(LC_ALL, "");
		render::text(x * 0.01f, y * 0.01f, render::fonts::watermark_font, song_title, false, color(255, 255, 255));
	}
}

void visuals::fog()
{
	interfaces::console->get_convar("fog_enable")->set_value(false);
	interfaces::console->get_convar("fog_enableskybox")->set_value(false);
	interfaces::console->get_convar("fog_override")->set_value(false);
	interfaces::console->get_convar("fog_end")->set_value(false);
	interfaces::console->get_convar("fog_start")->set_value(false);
	interfaces::console->get_convar("fog_maxdensity")->set_value(false);
	interfaces::console->get_convar("fog_colorskybox")->set_value(false);
	interfaces::console->get_convar("fog_endskybox")->set_value(false);
	interfaces::console->get_convar("fog_startskybox")->set_value(false);
	interfaces::console->get_convar("fog_maxdensityskybox")->set_value(false);
	interfaces::console->get_convar("fog_colorskybox")->set_value(false);
	interfaces::console->get_convar("fog_enable")->set_value(variables::config::fogenable);
	interfaces::console->get_convar("fog_enableskybox")->set_value(variables::config::fogenable);
	interfaces::console->get_convar("fog_override")->set_value(variables::config::fogenable);
	if (variables::config::fogenable) {
		interfaces::console->get_convar("fog_end")->set_value((float)variables::config::fogend);
		interfaces::console->get_convar("fog_start")->set_value((float)variables::config::fogstart);
		interfaces::console->get_convar("fog_maxdensity")->set_value(variables::config::fogmaxdensity);
		interfaces::console->get_convar("fog_color")->set_value((std::to_string((float)(variables::config::fogcolor.x * 255)) + " " + std::to_string((float)(variables::config::fogcolor.y * 255)) + " " + std::to_string((float)(variables::config::fogcolor.z * 255))).c_str());
		interfaces::console->get_convar("fog_endskybox")->set_value((float)variables::config::fogend);
		interfaces::console->get_convar("fog_startskybox")->set_value((float)variables::config::fogstart);
		interfaces::console->get_convar("fog_maxdensityskybox")->set_value(variables::config::fogmaxdensity);
		interfaces::console->get_convar("fog_colorskybox")->set_value((std::to_string((float)(variables::config::fogcolor.x * 255)) + " " + std::to_string((float)(variables::config::fogcolor.y * 255)) + " " + std::to_string((float)(variables::config::fogcolor.z * 255))).c_str());
	}
}

// fix font
void visuals::networkchannelinfo() {
	if (!variables::config::netchannels)
		return;

	auto choke = interfaces::clientstate->net_channel->choked_packets;
	const bool connected = interfaces::engine->is_connected(); //is_connected check

	int x, y;
	interfaces::engine->get_screen_size(x, y);

	auto tickrate = std::to_string((int)(1.0f / interfaces::globals->interval_per_tick));
	if (connected) {
		render::text(x * 0.917f, y * 0.6f, render::fonts::indicators, tickrate + " TICKS", false, color(255, 255, 255));
	}
	else {
		auto xx = std::string("XX");
		render::text(x * 0.917f, y * 0.6f, render::fonts::indicators, xx + " TICKS", false, color(255, 255, 255));
	}
}

void visuals::indicators() {
	if (!variables::config::indicators)
		return;

	const bool connected = interfaces::engine->is_connected(); //is_connected check

	int x, y;
	interfaces::engine->get_screen_size(x, y);

	if (connected) {
		render::text(x * 0.917f, y * 0.6f, render::fonts::indicators, "PING", false, color(0, 255, 0));
	}
	else {
		auto xx = std::string("XX");
		render::text(x * 0.917f, y * 0.6f, render::fonts::indicators, "PING", false, color(200, 0, 0));
	}
}