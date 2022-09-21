#include "../hooks.hpp"

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force) {
	auto panel_to_draw = fnv::hash(interfaces::panel->get_panel_name(panel));
	static unsigned int _hud_zoom_panel = 0, _panel = 0;

	PCHAR panel_char = (PCHAR)interfaces::panel->get_panel_name(panel);
	if (strstr(panel_char, "HudZoom")) {
		_hud_zoom_panel = panel;
	}

	if (interfaces::engine->is_connected() && interfaces::engine->is_in_game()) {
		if (variables::config::remove_scope && panel == _hud_zoom_panel)
			return;
	}

	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):

		visuals::watermark(); // stuff rendering here
		misc::visual::panorama_blur();
		misc::visual::debuginfo();
		misc::visual::jiggledebug();
		visuals::showimpacts();
		visuals::remove_scope();
		visuals::world_loop();
		notification_system::draw();
		visuals::player_loop();
		visuals::spectator_list_draw();
		visuals::networkchannelinfo();
		visuals::indicators();
		visuals::spotify();

		break;
	case fnv::hash("FocusOverlayPanel"):
		interfaces::panel->set_keyboard_input_enabled(panel, menu::settings::open);
		interfaces::panel->set_mouse_input_enabled(panel, menu::settings::open);
		break;
	}

	paint_traverse::original(interfaces::panel, panel, force_repaint, allow_force);
}