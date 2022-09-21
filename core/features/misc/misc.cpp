#include "../features.hpp"
#include "engine_prediction.hpp"
#include <windows.h>
#include <shellapi.h>

void misc::movement::bunny_hop(c_usercmd* cmd) {

	if (!variables::config::bhop)
		return;

	auto move_type = csgo::local_player->move_type();

	if (move_type == movetype_ladder)
		return;

	if (!(csgo::local_player->flags() & fl_onground))
		cmd->buttons &= ~in_jump;
};

template<class T, class U>
inline T clamp_value(T in, U low, U high) {

	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

static vec_t normalize_yaw(vec_t ang) {

	while (ang < -180.0f)
		ang += 360.0f;
	while (ang > 180.0f)
		ang -= 360.0f;
	return ang;
}

void misc::movement::strafer(c_usercmd* user_cmd) {

	if (!variables::config::strafer)
		return;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	if (!interfaces::inputsystem->is_button_down(button_code_t::KEY_SPACE))
		return;

	if (interfaces::inputsystem->is_button_down(button_code_t::KEY_S) || interfaces::inputsystem->is_button_down(button_code_t::KEY_D) || interfaces::inputsystem->is_button_down(button_code_t::KEY_A) || interfaces::inputsystem->is_button_down(button_code_t::KEY_W))
		return;

	if (csgo::local_player->move_type() == movetype_noclip || csgo::local_player->move_type() == movetype_ladder)
		return;

	if (!(csgo::local_player->flags() & fl_onground))
	{
		if (user_cmd->mousedx > 1 || user_cmd->mousedx < -1)
			user_cmd->sidemove = user_cmd->mousedx < 0.f ? -450.0f : 450.0f;
		else
		{
			user_cmd->forwardmove = std::clamp(10000.f / csgo::local_player->velocity().length_2d(), -450.f, 450.f);
			user_cmd->sidemove = user_cmd->command_number % 2 == 0 ? -450.f : 450.f;
		}
	}
}

void misc::movement::skate(c_usercmd* cmd) {

	if (!variables::config::skate)
		return;

	if (csgo::local_player && csgo::local_player->move_type() != movetype_ladder)
		cmd->buttons ^= in_forward | in_back | in_moveleft | in_moveright;
}

void send_clan_tag(const char* sz_clanTag, const char* sz_identifier = "") {

	using send_clan_tag_fn = void(__fastcall*)(const char*, const char*);
	static auto o_send_clantag = reinterpret_cast<send_clan_tag_fn>(utilities::pattern_scan("engine.dll", "53 56 57 8B DA 8B F9 FF 15"));

	if (o_send_clantag != nullptr)
		o_send_clantag(sz_clanTag, sz_identifier);
}

void misc::spam::clan_tag() {

	if (variables::config::clan_tag) {
		static int counter = 0;
		static std::string clantag = "  customhooks  ";
		if (++counter > 30) {
			rotate(clantag.begin(), clantag.begin() + 1, clantag.end());
			send_clan_tag(clantag.c_str());
			counter = 0;
		}
	}
}

void misc::visual::panorama_blur()
{
	if (variables::config::disable_blur)
	interfaces::console->get_convar("@panorama_disable_blur")->set_value(1);
	else {
		interfaces::console->get_convar("@panorama_disable_blur")->set_value(0);
	}
}

void misc::visual::debuginfo()
{
	if (variables::config::debuginfodump)
		interfaces::console->get_convar("cl_pdump")->set_value(1);
	else {
		interfaces::console->get_convar("cl_pdump")->set_value(-1);
	}
}

void misc::visual::jiggledebug()
{
	if (variables::config::jiggledebuginfo)
		interfaces::console->get_convar("cl_jiggle_bone_debug")->set_value(1);
	else {
		interfaces::console->get_convar("cl_jiggle_bone_debug")->set_value(0);
	}
}

void misc::movement::movement_related(c_usercmd* cmd) {

	bunny_hop(cmd);

	strafer(cmd);

	skate(cmd);
}

void misc::spam::spam_related() {

	clan_tag();
}

void misc::dropknife()
{
	if (!variables::config::dropknife)
		return;

	interfaces::console->get_convar("mp_drop_knife_enable")->set_value(1);
}

void misc::view_model_offsets() {
	if (!variables::config::visuals_view_model_changer_enable)
		return;

	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
		return;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	const auto view_model = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(csgo::local_player->view_model()));

	if (!view_model)
		return;

	vec3_t forward{}, right{}, up{};
	math::angle_vectors_alternative(view_model->abs_angles(), &forward, &right, &up);

	view_model->set_abs_origin(view_model->abs_origin() + forward * variables::config::visuals_viewmodel_z + up * variables::config::visuals_viewmodel_y + right * variables::config::visuals_viewmodel_x);
}

#define sig_player_by_index "85 C9 7E 32 A1"
#define sig_draw_server_hitboxes "55 8B EC 81 EC ? ? ? ? 53 56 8B 35 ? ? ? ? 8B D9 57 8B CE" 

void misc::draw_server_hitbox() {
	if (!variables::config::server_hitb)
		return;

	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
		return;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	if (!interfaces::input->b_camera_in_third_person)
		return;

	auto get_player_by_index = [](int index) -> player_t* {
		typedef player_t* (__fastcall* player_by_index)(int);
		static auto player_index = reinterpret_cast<player_by_index>(utilities::pattern_scan("server.dll", sig_player_by_index));

		if (!player_index)
			return false;

		return player_index(index);
	};

	static auto fn = reinterpret_cast<uintptr_t>(utilities::pattern_scan("server.dll", sig_draw_server_hitboxes));
	auto duration = -1.f;
	PVOID entity = nullptr;

	entity = get_player_by_index(csgo::local_player->index());

	if (!entity)
		return;

	__asm {
		pushad
		movss xmm1, duration
		push 0 // 0 - colored, 1 - blue
		mov ecx, entity
		call fn
		popad
	}
}

