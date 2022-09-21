#include "../hooks.hpp"

void __fastcall hooks::override_view::hook(void* _this, void* _edx, view_setup_t* setup) {
	misc::view_model_offsets();
	override_view::original(interfaces::clientmode, _this, setup);
}
