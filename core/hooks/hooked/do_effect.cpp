#include "../hooks.hpp"

int __fastcall hooks::do_effect::hook(void* ecx, void* edx, int a1) {
	return do_effect::original(ecx, edx, a1);
}