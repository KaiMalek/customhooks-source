#include "../features.hpp"
#include "../../menu/variables.hpp"

int random(int min, int max) {
	static bool first = true;
	if (first) {
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void antiaim::base::run(c_usercmd* cmd) {
	if (!csgo::local_player)
		return;

	if (!variables::config::antiaim::antiaim)
		return;

	if (cmd->buttons & in_attack ||
		cmd->buttons & in_use ||
		csgo::local_player->move_type() == movetype_ladder ||
		csgo::local_player->move_type() == movetype_noclip)
		return;

	float yaw_base;
	vec3_t engine_angles;
	interfaces::engine->get_view_angles(engine_angles);
	yaw_base = engine_angles.y;

	// Do "Backwords" Feature
	// Do "Forwards" Feature

	switch (variables::config::antiaim::antiaim) {
	case 1: // DOWN
		cmd->viewangles = vec3_t(89.f, yaw_base + 180.f, 0.f);
		cmd->viewangles.y += random(-35, 35);
		break;
	case 2: // UP
		cmd->viewangles = vec3_t(89.f, yaw_base + 180.f, 0.f);
		break;
	case 3: // JITTER 
		cmd->viewangles = vec3_t(89.f, yaw_base + (cmd->command_number % 2 ? -90.f : 90.f), 0.f);
		break;
	case 4:// 180^
		cmd->viewangles = vec3_t(89.f, yaw_base + 180.f, 0.f);
		cmd->viewangles.y += random(-35, 35);
		cmd->viewangles = vec3_t(89.f, yaw_base + 180.f, 0.f);
		cmd->viewangles = vec3_t(89.f, yaw_base + (cmd->command_number % 2 ? -90.f : 90.f), 0.f);
		break;
	case 5: // 360 SPIN
		break;
	default: break;
	}
}

void antiaim::fakelag::do_fakelag(c_usercmd* user_cmd) {

}

void antiaim::fakeangles::run(c_usercmd* cmd, bool* send_packet) {

}

void antiaim::desync::run(c_usercmd* cmd) noexcept { 

}

void antiaim::legit::update_lowerbody_breaker()
{
	if (!variables::config::antiaim::legit_aa)
		return;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	float speed = csgo::local_player->velocity().length_2d_sqr();

	if (speed > 0.1)
		variables::config::antiaim::next_update = csgo::server_time() + 0.22;

	variables::config::antiaim::break_lby = false;

	if (variables::config::antiaim::next_update <= csgo::server_time()) {
		variables::config::antiaim::next_update = csgo::server_time() + 1.1;
		variables::config::antiaim::break_lby = true;
	}

	if (!(csgo::local_player->flags() & fl_onground))
		variables::config::antiaim::break_lby = false;
}

void antiaim::legit::legit_antiaim_run(c_usercmd* cmd, bool& send_packet)
{
	if (!variables::config::antiaim::legit_aa) 
		return;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	if (csgo::local_player->move_type() == movetype_ladder)
		return;

	if (cmd->buttons & in_attack)
		return;

	auto net_channel = interfaces::clientstate->net_channel;

	if (!net_channel)
		return;

	send_packet = net_channel->choked_packets >= 3;

	auto weapon = csgo::local_player->active_weapon();

	if (!weapon || weapon->is_nade())
		return;

	if (GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RBUTTON) || (GetAsyncKeyState(0x45)))
		return;

	if (variables::config::antiaim::break_lby) {
		send_packet = false;
		cmd->viewangles.y += 120.f;
	}
	else if (!send_packet)
		cmd->viewangles.y -= 120.f;

	cmd->viewangles.clamp();
}
