#include "../hooks.hpp"

static bool __stdcall create_move(float input_sample_frametime, c_usercmd* cmd, bool& send_packet) {
	csgo::local_player = static_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	
	auto net_channel = interfaces::clientstate->net_channel;
	auto old_viewangles = cmd->viewangles;
	auto old_forwardmove = cmd->forwardmove;
	auto old_sidemove = cmd->sidemove;

	// features here
	visuals::remove_3dsky();
	visuals::disable_post_processing();
	visuals::recoil_crosshair();
	visuals::force_crosshair();
	visuals::fog();
	misc::movement::movement_related(cmd);
	misc::spam::spam_related();
	misc::dropknife();
	
	prediction::start(cmd); {

		antiaim::fakelag::do_fakelag(cmd);
		antiaim::base::run(cmd);
		antiaim::fakeangles::run(cmd, &send_packet);
		antiaim::legit::update_lowerbody_breaker();
		antiaim::legit::legit_antiaim_run(cmd, send_packet);

	} prediction::end();
	
	math::correct_movement(old_viewangles, cmd, old_forwardmove, old_sidemove);

	if (send_packet)
		csgo::angles = cmd->viewangles;

	csgo::send_packet = send_packet;

	cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
	cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
	cmd->upmove = std::clamp(cmd->upmove, -320.0f, 320.0f);

	cmd->viewangles.normalize();
	cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	cmd->viewangles.z = 0.0f;

	csgo::real_angles_vector = cmd->viewangles;

	return false;
}

static void __stdcall chl_create_move(int sequence_number, float input_sample_time, bool active, bool& send_packet)
{
	hooks::create_move_proxy::original(sequence_number, input_sample_time, active);

	c_usercmd* cmd = interfaces::input->get_user_cmd(0, sequence_number);
	if (!cmd || !cmd->command_number)
		return;

	c_verified_user_cmd* verified_cmd = interfaces::input->get_verified_cmd(sequence_number);
	if (!verified_cmd)
		return;

	bool create_move_active = create_move(input_sample_time, cmd, send_packet);

	verified_cmd->user_cmd = *cmd;
	verified_cmd->u_hash_crc = cmd->get_checksum();
}

__declspec(naked) void __stdcall hooks::create_move_proxy::hook(int sequence_number, float input_sample_time, bool active)
{
	__asm
	{
		push ebp
		mov  ebp, esp
		push ebx;
		push esp
			push dword ptr[active]
			push dword ptr[input_sample_time]
			push dword ptr[sequence_number]
			call chl_create_move
			pop  ebx
			pop  ebp
			retn 0Ch
	}
}