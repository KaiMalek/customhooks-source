#pragma once
#include "hooks.hpp"

HWND hooks::window;
WNDPROC hooks::wndproc_original = NULL;

bool hooks::initialize() {

	const auto present_target = reinterpret_cast<void*>(get_virtual(interfaces::directx, 17));
	const auto reset_target = reinterpret_cast<void*>(get_virtual(interfaces::directx, 16));
	const auto create_move_proxy_target = reinterpret_cast<void*>(get_virtual(interfaces::client, 22));
	const auto dme_target = reinterpret_cast<void*>(get_virtual(interfaces::model_render, 21));
	const auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));
	const auto view_model_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 35));
	const auto override_view_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 18));
	const auto sv_cheats_get_bool_target = reinterpret_cast<void*>(get_virtual(interfaces::console->get_convar("sv_cheats"), 13));
	const auto findmdl = reinterpret_cast<void*>(get_virtual(interfaces::mdl_cache, 10));
	const auto file_check_target = reinterpret_cast<void*>(utilities::pattern_scan(GetModuleHandleW(L"engine.dll"), "55 8B EC 81 EC ? ? ? ? 53 8B D9 89 5D F8 80"));
	const auto file_system_target = reinterpret_cast<void*>(get_virtual(**reinterpret_cast<void***>(utilities::pattern_scan(GetModuleHandleW(L"engine.dll"), "8B 0D ? ? ? ? 8D 95 ? ? ? ? 6A 00 C6") + 0x2), 128));
	const auto frame_stage_notify_target = reinterpret_cast<void*>(get_virtual(interfaces::client, 37));
	const auto do_effect_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 44));

	if (MH_Initialize() != MH_OK)
		throw std::runtime_error(("failed to initialize hooking system."));

	if (MH_CreateHook(present_target, &present::hook, reinterpret_cast<void**>(&present::original)) != MH_OK)
		throw std::runtime_error(("failed to initialize present."));

	if (MH_CreateHook(reset_target, &reset::hook, reinterpret_cast<void**>(&reset::original)) != MH_OK)
		throw std::runtime_error(("failed to initialize reset."));

	if (MH_CreateHook(create_move_proxy_target, &create_move_proxy::hook, reinterpret_cast<void**>(&create_move_proxy::original)) != MH_OK)
		throw std::runtime_error("failed to initialize create_move_proxy.");

	if (MH_CreateHook(view_model_target, &view_model::hook, reinterpret_cast<void**>(&view_model::original)) != MH_OK)
		throw std::runtime_error(("failed to initialize view_model."));

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse::original)) != MH_OK)
		throw std::runtime_error(("failed to initialize paint_traverse."));

	if (MH_CreateHook(dme_target, &dme::hook, reinterpret_cast<void**>(&dme::original)) != MH_OK)
		throw std::runtime_error("failed to initialize dme.");

	if (MH_CreateHook(override_view_target, &override_view::hook, reinterpret_cast<void**>(&override_view::original)) != MH_OK)
		throw std::runtime_error(("failed to initialize override_view."));

	if (MH_CreateHook(sv_cheats_get_bool_target, &sv_cheats_get_bool::hook, reinterpret_cast<void**>(&sv_cheats_get_bool::original)) != MH_OK)
		throw std::runtime_error(("failed to initialize sv_cheats."));

	if (MH_CreateHook(do_effect_target, &do_effect::hook, reinterpret_cast<void**>(&do_effect::original)) != MH_OK)
		throw std::runtime_error("failed to initialize do_effect.");

	if (MH_CreateHook(frame_stage_notify_target, &frame_stage_notify::hook, reinterpret_cast<void**>(&frame_stage_notify::original)) != MH_OK)
		throw std::runtime_error("failed to initialize frame_stage_notify.");

	if (MH_CreateHook(findmdl, &findmdl::hook, reinterpret_cast<void**>(&findmdl::original)))
		throw std::runtime_error("failed to initialize findmdl.");

	if (MH_CreateHook(file_system_target, &file_system::hook, reinterpret_cast<void**>(&file_system::original)) != MH_OK)
		throw std::runtime_error("failed to initialize file_check_target.");

	if (MH_CreateHook(file_check_target, &file_check::hook, reinterpret_cast<void**>(&file_check::original)) != MH_OK)
		throw std::runtime_error("failed to initialize file_check_target.");

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error(("failed to initialize hooks."));

	window = FindWindowW((L"Valve001"), NULL);

	if (!window)
		throw std::runtime_error(("failed to initialize game window."));

	wndproc_original = reinterpret_cast<WNDPROC>(SetWindowLongW(window, GWL_WNDPROC, reinterpret_cast<LONG>(wndproc)));
	interfaces::console->get_convar("sv_pure_allow_loose_file_loads")->set_value(0);

	std::printf(("[ debug ] [->] hooks intialized! \n"));
	return true;
}

void hooks::release() {
	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);

	SetWindowLongW(FindWindowW((L"Valve001"), NULL), GWL_WNDPROC, reinterpret_cast<LONG>(wndproc_original));
}

long __stdcall hooks::reset::hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters) {
	ImGui_ImplDX9_InvalidateDeviceObjects();

	auto result = reset::original(device, present_parameters);

	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}
