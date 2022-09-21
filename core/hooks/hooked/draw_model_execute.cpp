#include "../hooks.hpp"

void __fastcall hooks::dme::hook(void* thisptr, void* edx, void* ctx, void* state, const model_render_info_t& info, matrix_t* custom_bone_to_world)
{
	original(thisptr, ctx, state, info, custom_bone_to_world);
}