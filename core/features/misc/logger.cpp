#include "../features.hpp"

void logger::events(i_game_event* event) {
	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
		return;

	if (!event || !csgo::local_player)
		return;

	auto get_name = utilities::fnv::hash(event->get_name());

	if (get_name == utilities::fnv::hash("player_hurt")) {
		if (!variables::config::misc_event_logger[0])
			return;

		if (!csgo::local_player->is_alive())
			return;

		auto userid = interfaces::engine->get_player_for_user_id(event->get_int("userid"));

		if (!userid)
			return;

		auto attacker = interfaces::entity_list->get_client_entity(interfaces::engine->get_player_for_user_id(event->get_int("attacker")));

		if (!attacker || attacker != csgo::local_player)
			return;

		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(userid));

		if (!entity)
			return;

		player_info_t info;
		interfaces::engine->get_player_info(entity->index(), &info);

		auto hitbox = event->get_int("hitgroup");
		auto damage = event->get_int("dmg_health");
		auto health = event->get_int("health");

		if (!damage || !health && health != 0)
			return;

		const auto hitgroup_to_name = [](int hit_group) {
			switch (hit_group) {
			case hitgroup_head:
				return "head";
			case hitgroup_leftleg:
				return "left leg";
			case hitgroup_rightleg:
				return "right leg";
			case hitgroup_stomach:
				return "stomach";
			case hitgroup_leftarm:
				return "left arm";
			case hitgroup_rightarm:
				return "right arm";
			default:
				return "body";
			}
		};

		auto hit_group = hitgroup_to_name(hitbox);

		if (!hit_group)
			return;

		std::string name = info.name;

		if (name.empty())
			return;

		if (name.length() > 15)
			name = name.substr(0, 15) + "...";

		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		notification_system::notify((std::stringstream{ } << "hit " << name.c_str() << " in the " << hit_group << " for " << damage << " damage (" << health << " health remaining).").str().c_str(), color::white(variables::config::logger_clr[3] * 255.f));
	}

	if (get_name == utilities::fnv::hash("item_purchase")) {
		if (!variables::config::misc_event_logger[1])
			return;

		auto userid = interfaces::engine->get_player_for_user_id(event->get_int("userid"));

		if (!userid)
			return;

		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(userid));

		if (!entity)
			return;

		auto team = event->get_int("team");
		auto weapon = event->get_string("weapon");

		if (!team || !weapon)
			return;

		if (csgo::local_player->team() == event->get_int("team"))
			return;

		player_info_t info;
		interfaces::engine->get_player_info(entity->index(), &info);

		std::string name = info.name;

		if (name.empty())
			return;

		if (name.length() > 15)
			name = name.substr(0, 15) + "...";

		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		notification_system::notify((std::stringstream{ } << name.c_str() << " bought " << weapon << ".").str().c_str(), color::white(variables::config::logger_clr[3] * 255.f));
	}
}

void notification_system::draw() {
	const auto stay_time = 5.f;

	for (auto i = 0; i < notify_list.size(); i++) {
		if (notify_list.empty())
			continue;

		auto notify = notify_list[i];

		if ((interfaces::globals->cur_time > notify.time + stay_time) || (notify_list.size() > 15)) {
			notify_list.erase(notify_list.begin() + i);
			i--;
			continue;
		}

		render::text(10, 10 + (i * 15), render::fonts::watermark_font, ("[customhooks]"), false, color(variables::config::logger_clr[0] * 255.f, variables::config::logger_clr[1] * 255.f, variables::config::logger_clr[2] * 255.f, variables::config::logger_clr[3] * 255.f));
		render::text(95, 10 + (i * 15), render::fonts::watermark_font, notify.text.c_str(), false, notify._color);
	}
}

void notification_system::notify(std::string text, color _color) {
	if (text.empty())
		return;

	notify_list.push_back(notify_t(text, _color));

	interfaces::console->console_color_printf({ static_cast<unsigned char>(variables::config::logger_clr[0] * 255.f),
		static_cast<unsigned char>(variables::config::logger_clr[1] * 255.f),
		static_cast<unsigned char>(variables::config::logger_clr[2] * 255.f), 255 }, ("[customhooks] "));

	interfaces::console->console_printf(text.append(" \n").c_str());

}