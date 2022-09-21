#include "../hooks.hpp"

void __fastcall hooks::file_check::hook(void* ecx, void* edx)
{
	return;
}

bool __fastcall hooks::file_system::hook(void* ecx, void* edx)
{
	return true;
}