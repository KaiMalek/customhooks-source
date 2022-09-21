#include "../hooks.hpp"

void __stdcall hooks::frame_stage_notify::hook(int frame_stage)
{
	
	animations::animation_fix(frame_stage);
	misc::draw_server_hitbox();

	switch (frame_stage) {
	case FRAME_UNDEFINED:
		break;
	case FRAME_START:
		break;
	case FRAME_NET_UPDATE_START:
		break;
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		if (variables::config::skinchanger) {
			skinchanger::run();
		}
		if (variables::config::glove_changer) {
			glovechanger::run();
		}
		break;
	case FRAME_NET_UPDATE_POSTDATAUPDATE_END:
		break;
	case FRAME_NET_UPDATE_END:
		break;
	case FRAME_RENDER_START:
		if (interfaces::input->b_camera_in_third_person && interfaces::engine->is_connected() && variables::config::antiaim::antiaim)
		{
			interfaces::prediction->set_local_view_angles(csgo::real_angles_vector);
		}
		break;
	case FRAME_RENDER_END:
		break;
	default: break;
	}
	
	frame_stage_notify::original(interfaces::client, frame_stage);
}