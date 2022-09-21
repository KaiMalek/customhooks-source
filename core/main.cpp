#include <windows.h>

#include "../dependencies/utilities/csgo.hpp"
#include "features/features.hpp"
#include "../core/security/security-includes.h"
#include "../core/hooks/hooked/events.hpp"

unsigned long WINAPI initialize(void* instance) {
	while (!GetModuleHandleA("serverbrowser.dll"))
		Sleep(2000);

#ifdef _DEBUG
	console::initialize("csgo-cheat console");
#endif

	try {
		interfaces::initialize();
		variables::create_directory();
		render::initialize();
		hooks::initialize();
		event_listener.initialize();
		skinchanger::animfix_hook();
	}

	catch (const std::runtime_error & error) {
		MessageBoxA(nullptr, error.what(), "custommhooks error!", MB_OK | MB_ICONERROR);
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
	}

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	
	//wait for paint_traverse::hook to be called and restore input.
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
}

unsigned long WINAPI release() {
	hooks::release();
#ifdef _DEBUG
	console::release();
#endif

	return TRUE;
}

std::int32_t WINAPI DllMain(const HMODULE instance [[maybe_unused]], const unsigned long reason, const void* reserved [[maybe_unused]] ) {
	DisableThreadLibraryCalls(instance);

	VMP_BEGINMUTILATION("main")
#ifdef _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		if (auto handle = CreateThread(nullptr, NULL, initialize, instance, NULL, nullptr))
			CloseHandle(handle);

		break;
	}

	case DLL_PROCESS_DETACH: {
		release();
		break;
	}
	}
	return true;
	VMP_END
}
