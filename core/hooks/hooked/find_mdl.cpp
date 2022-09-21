#include "../hooks.hpp"

unsigned long __stdcall hooks::findmdl::hook(const char* path) noexcept
{
	if (strstr(path, "knife_default_ct.mdl"))
		return findmdl::original(interfaces::mdl_cache, "models/weapons/v_minecraft_pickaxe.mdl");
	else if (strstr(path, "knife_default_t.mdl"))
		return findmdl::original(interfaces::mdl_cache, "models/weapons/v_minecraft_pickaxe.mdl");

	return findmdl::original(interfaces::mdl_cache, path);
}
