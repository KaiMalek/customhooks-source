#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "imgui/imgui_internal.h"
#include "variables.hpp"

struct ImFont;
namespace menu {
    void initialize();
    void render();

    void playerlist();
    void exploitlist();

    void CustomColorPicker(const char* name, float* color, bool alpha);

    inline ImFont* menu_font = nullptr;

    namespace settings {
        inline bool open = false;
    }
};