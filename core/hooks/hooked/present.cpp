#include "../hooks.hpp"

std::once_flag flag;
long __stdcall hooks::present::hook(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect, HWND dest_window_override, RGNDATA* dirty_region) {
	std::call_once(flag, [&] { menu::initialize(); });
	static bool init_imgui{ ImGui_ImplDX9_Init(device) };
	device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
	IDirect3DVertexDeclaration9* vertexDeclaration;
	device->GetVertexDeclaration(&vertexDeclaration);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	menu::render();
	menu::playerlist();
	menu::exploitlist();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	device->SetVertexDeclaration(vertexDeclaration);
	vertexDeclaration->Release();

	return present::original(device, source_rect, dest_rect, dest_window_override, dirty_region);
}