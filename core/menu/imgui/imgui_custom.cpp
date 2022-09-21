#include "../menu.hpp"
#include "imgui_custom.h"


void menu::CustomColorPicker(const char* name, float* color, bool alpha)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::SameLine(0 + window->Size.x - 43 - 7 + 18.f);
	auto alphaSliderFlag = alpha ? ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoAlpha;

	ImGui::ColorEdit4(std::string{ "##" }.append(name).append("Picker").c_str(), color, alphaSliderFlag | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip);
}