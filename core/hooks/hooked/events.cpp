#include "../hooks.hpp"
#include "events.hpp"

event_manager event_listener;

void event_manager::fire_game_event(i_game_event* event) {
	logger::events(event);
}

bool event_manager::initialize() {
	debug_id = EVENT_DEBUG_ID_INIT;
	interfaces::event_manager->add_listener(this, ("player_hurt"), false);;
	interfaces::event_manager->add_listener(this, ("player_death"), false);
	interfaces::event_manager->add_listener(this, ("round_start"), false);
	interfaces::event_manager->add_listener(this, ("item_purchase"), false);

	if (!interfaces::event_manager->find_listener(this, ("player_hurt")) || !interfaces::event_manager->find_listener(this, ("player_death")) ||
		!interfaces::event_manager->find_listener(this, ("round_start")) || !interfaces::event_manager->find_listener(this, ("item_purchase"))) {
		throw std::runtime_error(("failed to initialize events. (add_listener?)"));
		return false;
	}
	interfaces::engine->execute_cmd("[alpha] event listener intialized! \n");
	return true;
}

bool event_manager::release() {
	interfaces::event_manager->remove_listener(this);

	return true;
}