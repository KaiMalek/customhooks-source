#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/variables.hpp"
#include "misc/engine_prediction.hpp"
#include "../hooks/hooks.hpp"

namespace misc {
	namespace movement {
		void bunny_hop(c_usercmd* cmd);
		void skate(c_usercmd* cmd);
		void strafer(c_usercmd* user_cmd);
		void movement_related(c_usercmd* cmd);
	};
	namespace visual {
		void panorama_blur();
		void debuginfo();
		void jiggledebug();
	}

	namespace spam {
		void clan_tag();
		void spam_related();
	};
	void dropknife();
	void view_model_offsets();
	void draw_server_hitbox();
}

struct sequence_object_t {
	sequence_object_t(int iInReliableState, int iOutReliableState, int iSequenceNr, float flCurrentTime)
		: iInReliableState(iInReliableState), iOutReliableState(iOutReliableState), iSequenceNr(iSequenceNr), flCurrentTime(flCurrentTime) { }

	int iInReliableState;
	int iOutReliableState;
	int iSequenceNr;
	float flCurrentTime;
};

namespace logger {
	void events(i_game_event* event);
}

namespace notification_system {
	struct notify_t {
		std::string text;
		float time;
		color _color;
		notify_t(std::string _text, color __color) {
			text = _text;
			_color = __color;
			time = interfaces::globals->cur_time;
		}
	};

	inline std::vector<notify_t> notify_list;

	void draw();
	void notify(std::string text, color _color);
}

struct fake_state_t {
	bool m_should_update_fake = false;
	std::array< animation_layer, 13 > m_fake_layers;
	std::array< float, 24 > m_fake_poses;
	anim_state* m_fake_state = nullptr;
	float m_fake_rotation = 0.f;
	bool init_fake_anim = false;
	float m_fake_spawntime = 0.f;
	float m_fake_delta = 0.f;
	matrix_t m_fake_matrix[128];
	matrix_t m_fake_position_matrix[128];
	bool m_got_fake_matrix = false;
	float m_real_y_ang = 0.f;
};
extern fake_state_t fake_state;

namespace animations {
	void animation_fix(int stage);
	void manage_local_fake_animstate();
}

namespace visuals {
	void watermark();
	void remove_scope() noexcept;
	void force_crosshair() noexcept;
	void recoil_crosshair() noexcept;
	void disable_post_processing() noexcept;
	void remove_3dsky();
	void showimpacts();
	void radar(player_t* entity);

	struct box {
		int x, y, w, h;
		box() = default;
		box(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	static bool is_checked = false;
	bool get_playerbox(player_t* ent, box& in);
	void draw_box(player_t* entity, visuals::box bbox);
	void draw_info(player_t* entity, visuals::box bbox);
	void draw_name(player_t* entity, visuals::box bbox);
	void draw_hp(player_t* entity, visuals::box bbox);
	void draw_ammo(player_t* entity, visuals::box bbox);
	void draw_weapon(player_t* entity, visuals::box bbox);
	void grenades_draw(entity_t* entity);
	void spectator_list_draw();
	void player_esp_render(player_t* entity);
	void player_loop();
	void world_loop();
	void spotify();
	void fog();
	void networkchannelinfo();
	void indicators();
	void custom_materials();
}

namespace skinchanger {
	void run();
	void animfix_hook();
	void animfix_unhook();
}

namespace glovechanger {
	bool apply_glove_model(attributable_item_t* glove, const char* model);
	bool apply_glove_skin(attributable_item_t* glove, int item_definition_index, int paint_kit, int model_index, int entity_quality, float fallback_wear);
	void run();
}

namespace antiaim {
	namespace base {
		void run(c_usercmd* cmd);
	}

	namespace fakelag {
		void do_fakelag(c_usercmd* user_cmd);
	}

	namespace fakeangles {
		void run(c_usercmd* cmd, bool* send_packet);
	}

	namespace desync {
		void run(c_usercmd* cmd) noexcept;
	}

	namespace legit {
		void update_lowerbody_breaker();
		void legit_antiaim_run(c_usercmd* cmd, bool& send_packet);
	}
}

namespace resolver {
	void backup();
	void restore();
}