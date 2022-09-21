#pragma once
#include "imgui.h"

#define CustomColorSelect(x1,x2,x3) ImGui::SameLine(167.f); CustomColorPicker(x1, x2, x3); // We can find CustomColorPicker in imgui_custom.cpp file