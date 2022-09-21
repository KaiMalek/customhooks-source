#pragma once
#include "../../source-sdk/misc/color.hpp"
#include "../security/security-includes.h"
#include "imgui/imgui_custom.h"
#include "../../dependencies/json/json.hpp"

namespace variables {
	inline std::string directory_path_lua;

	void create_directory() noexcept;
	void update_configs() noexcept;
	void create_file(const std::string_view name) noexcept;
	void delete_file(const std::size_t index) noexcept;
	void save(const std::size_t index) noexcept;
	void load(const std::size_t index) noexcept;

	namespace config {
		inline bool playerlistmenu = false;
		inline bool exploitlistmenu = false;
		// - Legit

		namespace aimbot {

		}

		namespace antiaim {
			inline int antiaim = 0;

			inline bool legit_aa = false;
			inline bool break_lby = false;
			inline int next_update = 0;
		}

		namespace chams {
			inline int chams_type = 0;

			inline int chams_weapon_type = 0;
			inline bool weapon_wireframe = false;
			inline bool draw_weapon_chams_on_top = false;

			inline int chams_arm_type = 0;
			inline bool arm_wireframe = false;

			inline int chams_sleeve_type = 0;
			inline bool sleeve_wireframe = false;

			inline bool chams = false;
			inline bool chams_xqz = false;
			inline bool team_check_chams = false;
			inline bool local_chams = false;
			inline bool wireframe = false;

			inline bool sleeve_chams = false;
			inline bool arms_chams = false;
			inline bool weapon_chams = false;
			inline bool glove_chams = false;

			inline float f_chams_clr[4] = { 1.f, 1.f, 1.f, 1.f };
			inline color chams_clr = color(255, 105, 180);
			inline float f_chams_local_clr[4] = { 1.f, 1.f, 1.f, 1.f };
			inline color chams_local_clr = color(255, 105, 180);
			inline float f_chams_team_clr[4] = { 1.f, 1.f, 1.f, 1.f };
			inline color chams_team_clr = color(255, 105, 180);
			inline float f_sleeve_chams[4] = { 1.f, 1.f, 1.f, 1.f };
			inline color sleeve_chams_clr = color(255, 105, 255);
			inline float f_arms_chams[4] = { 1.f, 1.f, 1.f, 1.f };
			inline color arms_chams_clr = color(255, 105, 255);
			inline float f_weapon_chams[4] = { 1.f, 1.f, 1.f, 1.f };
			inline color weapon_chams_clr = color(255, 105, 255);
			inline float f_glove_chams[4] = { 1.f, 1.f, 1.f, 1.f };
			inline color glove_chams_clr = color(255, 105, 255);
			inline float f_xqz_clr[4] = { 1.f, 1.f, 1.f, 1.f };
			inline color xqz_clr = color(255, 105, 255);
		}

		inline float night_darkness;

		//ESP
		inline bool radar_spotted = false;
		inline bool draw_box = false;
		inline bool draw_name = false;
		inline bool draw_hp = false;
		inline bool draw_weapon = false;
		inline bool draw_ammo = false;
		inline bool draw_bot_check = false;
		inline bool draw_money = false;
		inline bool draw_zoom_check = false;
		inline bool draw_hk = false;
		inline bool draw_is_flashed = false;
		inline bool draw_projectile = false;
		inline bool visible_check = false;

		//World
		inline bool fogenable = false;
		inline ImVec4 fogcolor = ImVec4(0, 0, 0, 1);
		inline int fogend = 0;
		inline int fogstart = 0;
		inline float fogmaxdensity = 0.9f;

		//local_player
		inline bool server_hitb = false;

		// Misc -
		inline float logger_clr[4]{ 0.37f, 0.41f, 0.75f, 1.0f };
		inline bool misc_event_logger[2] = { false, false };

		//Movement

		inline bool bhop = false;
		inline bool skate = false;
		inline bool strafer = false;

		//OtherStuff
		inline bool watermark = true;
		inline float menu_color[4] = { 0 / 255.f, 143 / 255.f, 255 / 255.f, 255 / 255.f }; // R G B A  ||  255 250 50 255

		inline bool clan_tag = false;
		inline bool blackout = true;
		inline bool disable_blur = false;

		inline bool showimpacts = false;
		inline bool remove_3dsky = false;
		inline bool disable_post_processing = false;
		inline bool force_crosshair = false;
		inline bool remove_scope = false;
		inline bool recoil_crosshair = false;
		inline bool dropknife = false;

		inline bool draw_spectators = false;
		inline bool spotify = false;
		inline bool indicators = false;

		//Changer -

		inline 	float visuals_view_model_fov = 0.f;
		inline bool visuals_view_model_changer_enable = false;
		inline 	float visuals_viewmodel_x = 1.f;
		inline 	float visuals_viewmodel_y = 1.f;
		inline 	float visuals_viewmodel_z = -1.f;

		//Skin Changer
		inline bool enabled = false;
		inline bool skinchanger = false;
		inline int knife_model = 0;
		inline int knife_skin = 0;

		inline bool glove_changer = false;
		inline int glove_model = 0;
		inline int hydra_skin = 0;
		inline int bloodhound_skin = 0;
		inline int driver_skin = 0;
		inline int handwrap_skin = 0;
		inline int moto_skin = 0;
		inline int specialist_skin = 0;
		inline int sport_skin = 0;

		// exploits + info
		inline bool netchannels = false;
		inline bool debuginfodump = false;
		inline bool jiggledebuginfo = false;
		inline bool mmregionenable = 0;
		inline int mmregion = 0;
	}

	inline std::vector<std::string> configs;
}