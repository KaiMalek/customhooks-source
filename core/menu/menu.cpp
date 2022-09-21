#include "menu.hpp"
#include "styles.h"
#include "imgui/imgui_custom.h"
#include "../security/security-includes.h"
#include "extra.h"

#define GROUPBOX_FIRST_POSITION 14, 133
#define GROUPBOX_SECOND_POSITION 338,133
#define GROUPBOX_SIZE 308, 359

void menu::initialize() {
    ImGui::CreateContext();
    ImGui_ImplWin32_Init(hooks::window);

    ImGui::StyleColorsDark();
}

#if RELEASE
#if BETA
#define VERSION ("[alpha]")
#else
#define VERSION ("[beta] ")
#endif
#else
#define VERSION ("-insecure [alpha]")
#define VERSION2 ("         [alpha]")
#endif

void update_colors()
{
    variables::config::chams::chams_clr = color(variables::config::chams::f_chams_clr[0] * 255, variables::config::chams::f_chams_clr[1] * 255, variables::config::chams::f_chams_clr[2] * 255, variables::config::chams::f_chams_clr[3] * 255);
    variables::config::chams::chams_local_clr = color(variables::config::chams::f_chams_local_clr[0] * 255, variables::config::chams::f_chams_local_clr[1] * 255, variables::config::chams::f_chams_local_clr[2] * 255, variables::config::chams::f_chams_local_clr[3] * 255);
    variables::config::chams::chams_team_clr = color(variables::config::chams::f_chams_team_clr[0] * 255, variables::config::chams::f_chams_team_clr[1] * 255, variables::config::chams::f_chams_team_clr[2] * 255, variables::config::chams::f_chams_team_clr[3] * 255);
    variables::config::chams::xqz_clr = color(variables::config::chams::f_xqz_clr[0] * 255, variables::config::chams::f_xqz_clr[1] * 255, variables::config::chams::f_xqz_clr[2] * 255, variables::config::chams::f_xqz_clr[3] * 255);
    variables::config::chams::sleeve_chams_clr = color(variables::config::chams::f_sleeve_chams[0] * 255, variables::config::chams::f_sleeve_chams[1] * 255, variables::config::chams::f_sleeve_chams[2] * 255, variables::config::chams::f_sleeve_chams[3] * 255);
}

void menu::render() {
    SetupStyles();
    utilities::console_printing();

    static int tab = 0;
    static int visuals_tab = 0;

    auto& style = ImGui::GetStyle();
    const auto& io = ImGui::GetIO();

    static float alpha = 0.f;

    if (variables::config::blackout)
    {
        const auto& draw_list = ImGui::GetBackgroundDrawList();
        draw_list->AddRectFilled(ImVec2{ 0.f, 0.f }, io.DisplaySize, ImColor{ 0.f, 0.f, 0.f, alpha });
    }

    if (!menu::settings::open)
    {
        alpha = std::fmax(alpha - io.DeltaTime * 3.0f, 0.f);
        style.Alpha = std::fmax(style.Alpha - io.DeltaTime * 6.0f, 0.f);
        return;
    }

    alpha = std::fmin(alpha + io.DeltaTime * 3.0f, 0.5f);
    style.Alpha = std::fmin(style.Alpha + io.DeltaTime * 6.0f, 1.f);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.20f, 0.20f, 0.20f, 1.00f));
    ImGui::SetNextWindowSize(ImVec2{ 520.f, 570.f }, ImGuiCond_Once);
    ImGui::Begin("title", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleColor();

    ImVec2 pos = ImGui::GetWindowSize();
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.08f, 0.08f, 0.08f, 1.00f));

    ImGui::SetCursorPosX(-3);
    ImGui::SetCursorPosY(4);

    ImGui::BeginChild("FirstChild", ImVec2(ImGui::GetContentRegionAvail().x * 2, ImGui::GetContentRegionAvail().y * 2 - 554), false);
    {
        ImGui::PopStyleColor();

        ImVec2 startPos = ImGui::GetCursorScreenPos();
        ImVec2 endPos = ImVec2(startPos.x + 1000.f, startPos.y);
        ImGui::GetWindowDrawList()->AddLine(startPos, endPos, ImColor(variables::config::menu_color[0], variables::config::menu_color[1], variables::config::menu_color[2]), 3.f);

        ImGui::SetCursorPosX(12);
        ImGui::SetCursorPosY(10);
        if (ImGui::Button(XorStr("Aimbot"), { 82, 23 })) // 84
        {
            tab = 0;
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(96);
        if (ImGui::Button(XorStr("Anti Aim"), { 82, 23 }))
        {
            tab = 1;
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(180);
        if (ImGui::Button(XorStr("Visuals"), { 82, 23 }))
        {
            tab = 2;
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(264);
        if (ImGui::Button(XorStr("Misc"), { 82, 23 }))
        {
            tab = 3;
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(348);
        if (ImGui::Button(XorStr("Changer"), { 82, 23 }))
        {
            tab = 4;
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(432);
        if (ImGui::Button(XorStr("Settings"), { 82, 23 }))
        {
            tab = 5;
        }

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15f, 0.15f, 0.15f, 1.00f));
        ImGui::SetCursorPosX(20);
        ImGui::SetCursorPosY(40);
        ImGui::BeginChild("FirstChild", ImVec2(486, 515), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        {
            ImGui::PopStyleColor();
            switch (tab)
            {
            case 0:
                ImGui::SetCursorPosX(5);
                ImGui::SetCursorPosY(5);
                ImGui::BeginChild(XorStr("LegitAimbot"), ImVec2(236, 505), true);
                {

                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::SetCursorPosX(245);
                ImGui::BeginChild(XorStr("Rage Aimbot"), ImVec2(236, 505), true);
                {

                }
                ImGui::EndChild();
                break;
            case 1:
                ImGui::SetCursorPosX(5);
                ImGui::SetCursorPosY(5);
                ImGui::BeginChild(XorStr("Legit Antiaim"), ImVec2(236, 505), true);
                {

                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::SetCursorPosX(245);
                ImGui::BeginChild(XorStr("Rage Antiaim"), ImVec2(236, 505), true);
                {
                    ImGui::Combo(XorStr("Antiaim"), &variables::config::antiaim::antiaim, "None\0Down Jitter\0Down Backwards\0Down 180^\0Testing\0");
                    ImGui::Checkbox(XorStr("Show Hit Box"), &variables::config::server_hitb);
                }
                ImGui::EndChild();
                break;
            case 2:
                ImGui::SetCursorPosX(5);
                ImGui::SetCursorPosY(5);
                ImGui::BeginChild(XorStr("Entity Visuals"), ImVec2(236, 505), true);
                {
                    ImGui::Checkbox(XorStr("Visible Check"), &variables::config::visible_check);
                    ImGui::Checkbox(XorStr("Visible Only"), &variables::config::radar_spotted);
                    ImGui::Checkbox(XorStr("Box"), &variables::config::draw_box);
                    ImGui::Checkbox(XorStr("Name"), &variables::config::draw_name);
                    ImGui::Checkbox(XorStr("Weapon"), &variables::config::draw_weapon);
                    ImGui::Checkbox(XorStr("Ammo"), &variables::config::draw_ammo);
                    ImGui::Checkbox(XorStr("HP"), &variables::config::draw_hp);
                    ImGui::Checkbox(XorStr("Armor"), &variables::config::draw_hk);
                    ImGui::Checkbox(XorStr("Money"), &variables::config::draw_money);
                    ImGui::Checkbox(XorStr("Bot Check"), &variables::config::draw_bot_check);
                    ImGui::Checkbox(XorStr("Zoom Check"), &variables::config::draw_zoom_check);
                    ImGui::Checkbox(XorStr("Flash Check"), &variables::config::draw_is_flashed);
                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::SetCursorPosX(245);
                ImGui::BeginChild(XorStr("Cham Visuals"), ImVec2(236, 245), true);
                {
                    if (ImGui::Button(XorStr("Enemy"), { 68,20 })) // 84
                    {
                        visuals_tab = 0;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(XorStr("Team"), { 68,20 })) // 84
                    {
                        visuals_tab = 1;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(XorStr("Local"), { 68,20 })) // 84
                    {
                        visuals_tab = 2;
                    }

                    switch (visuals_tab)
                    {
                    case 0:

                        break;
                    case 1:

                        break;
                    case 2:

                        break;
                    }
                }
                ImGui::EndChild();
                ImGui::SetCursorPosX(245);
                ImGui::BeginChild(XorStr("World Visuals"), ImVec2(236, 255), true);
                {
                    ImGui::Checkbox(XorStr("Enable Fog"), &variables::config::fogenable);
                    ImGui::SliderFloat(XorStr("Density"), &variables::config::fogmaxdensity, 0.0f, 1.0f, "%.2f");
                    ImGui::SliderInt(XorStr("Start"), &variables::config::fogstart, 0, 1000);
                    ImGui::SliderInt(XorStr("End"), &variables::config::fogend, 0, 2000);
                }
                ImGui::EndChild();
                break;
            case 3:
                ImGui::SetCursorPosX(5);
                ImGui::SetCursorPosY(5);
                ImGui::BeginChild(XorStr("Misc Performace/Visuals"), ImVec2(236, 505), true);
                {
                    //Performance
                    ImGui::Checkbox(XorStr("Disable 3dsky"), &variables::config::remove_3dsky);
                    ImGui::Checkbox(XorStr("Disable Post-P"), &variables::config::disable_post_processing);
                    //Removals
                    ImGui::Checkbox(XorStr("Remove Scope"), &variables::config::remove_scope);
                    //Gun/Hud Stuff
                    ImGui::Checkbox(XorStr("Clan Tag"), &variables::config::clan_tag);
                    ImGui::Checkbox(XorStr("Show Impacts"), &variables::config::showimpacts);
                    ImGui::Checkbox(XorStr("Force Crosshair"), &variables::config::force_crosshair);
                    ImGui::Checkbox(XorStr("Recoil Crosshair"), &variables::config::recoil_crosshair);
                    ImGui::MultiCombo(XorStr("Logs"), loggerforlogs, variables::config::misc_event_logger, 2);
                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::SetCursorPosX(245);
                ImGui::BeginChild(XorStr("Misc 'Better Game'"), ImVec2(236, 505), true);
                {
                    //Movement
                    ImGui::Checkbox(XorStr("Bunny Hop"), &variables::config::bhop);
                    ImGui::Checkbox(XorStr("Auto Strafe"), &variables::config::strafer);
                    ImGui::Checkbox(XorStr("Leg Slide"), &variables::config::skate);
                    ImGui::Checkbox(XorStr("Projectiles"), &variables::config::draw_projectile);
                    //Viewmodel 
                    ImGui::SliderFloat(XorStr("viewmodel fov"), &variables::config::visuals_view_model_fov, 0.f, 60.f);
                    ImGui::Checkbox(XorStr("viewmodel"), &variables::config::visuals_view_model_changer_enable);
                    ImGui::SliderFloat(XorStr("X"), &variables::config::visuals_viewmodel_x, -15.0f, 15.0f);
                    ImGui::SliderFloat(XorStr("Y"), &variables::config::visuals_viewmodel_y, -15.0f, 15.0f);
                    ImGui::SliderFloat(XorStr("Z"), &variables::config::visuals_viewmodel_z, -15.0f, 15.0f);
                }
                ImGui::EndChild();
                break;
            case 4:
                ImGui::SetCursorPosX(5);
                ImGui::SetCursorPosY(5);
                ImGui::BeginChild(XorStr("Knife/Glove Changers"), ImVec2(236, 505), true);
                {
                    ImGui::Checkbox(XorStr("Enable Knife Models"), &variables::config::skinchanger);
                    ImGui::Combo(XorStr("Knifes"), &variables::config::knife_model, "Default\0Bayonet\0Flip Knife\0Gut Knife\0Karambit\0M9 Bayo\0Huntsman Knife\0Falchion Knife\0Bowie Knife\0Butterfly Knife\0Shadow Daggers\0Ursus Knife\0Navaja Knife\0Stiletto Knife\0Talon Knife\0Nomad Knife\0Skeleton Knife\0Survival Knife\0Paracord Knife\0Classic Knife");
                    switch (variables::config::knife_model)
                    {
                    case 1:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Lore\0Gamma Doppler\0Autotronic\0Black Laminate\0Freehand\0Bright Water\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 2:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Lore\0Gamma Doppler\0Autotronic\0Black Laminate\0Freehand\0Bright Water\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 3:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Lore\0Gamma Doppler\0Autotronic\0Black Laminate\0Freehand\0Bright Water\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 4:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Lore\0Gamma Doppler\0Autotronic\0Black Laminate\0Freehand\0Bright Water\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 5:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Lore\0Gamma Doppler\0Autotronic\0Black Laminate\0Freehand\0Bright Water\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 6:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 7:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 8:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 9:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 10:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 11:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 12:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 13:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 14:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 15:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 16:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 17:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 18:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    case 19:
                        ImGui::Combo(XorStr("K Skins"), &variables::config::knife_skin, "Vanilla\0Marble Fade\0Tiger Tooth\0Doppler\0Ultraviolet\0Damascus Steel\0Rust Coat\0Fade\0Slaughter\0Case Hardened\0Crimson Web\0Blue Steel\0Night\0Safari Mesh\0Forest DDPAT\0Stained\0Scorched\0Boreal Forest\0Urban Masked");
                        break;
                    }
                    ImGui::Checkbox(XorStr("Enable Glove Models"), &variables::config::glove_changer);
                    ImGui::Combo(XorStr("Gloves"), &variables::config::glove_model, "Default\0Bloodhound\0Sport\0Driver\0Hand Wraps\0Moto\0Specialist\0Hydra");
                    switch (variables::config::glove_model)
                    {
                    case 1:
                        ImGui::Combo(XorStr("G Skins"), &variables::config::bloodhound_skin, "Snakebite\0Guerrilla\0Charred\0Bronzed");
                        break;
                    case 2:
                        ImGui::Combo(XorStr("G Skins"), &variables::config::sport_skin, "Vice\0Amphibious\0Omega\0Bronze Morph\0Pandora's Box\0Superconductor\0Hedge Maze\0Arid");
                        break;
                    case 3:
                        ImGui::Combo(XorStr("G Skins"), &variables::config::driver_skin, "King Snake\0Imperial Plaid\0Overtake\0Racing Green\0Crimson Weave\0Diamondback\0Lunar Weave\0Convoy\0Black Tie");
                        break;
                    case 4:
                        ImGui::Combo(XorStr("G Skins"), &variables::config::handwrap_skin, "Cobalt Skulls\0Overprint\0Arboreal\0Duct Tape\0Slaughter\0Badlands\0Leather\0Spruce DDPAT");
                        break;
                    case 5:
                        ImGui::Combo(XorStr("G Skins"), &variables::config::moto_skin, "POW!\0Turtle\0Polygon\0Transport\0Spearmint\0Boom!\0Cool Mint\0Eclipse");
                        break;
                    case 6:
                        ImGui::Combo(XorStr("G Skins"), &variables::config::specialist_skin, "Fade\0Crimson Web\0Mogul\0Buckshot\0Crimson Kimono\0Emerald Web\0Foundation\0Forest DDPAT");
                        break;
                    case 7:
                        ImGui::Combo(XorStr("G Skins"), &variables::config::hydra_skin, "Emerald\0Mangrove\0Case Hardened\0Rattler");
                        break;
                    }
                    if (ImGui::Button(XorStr("Force Update"), { 220,20 }))
                        interfaces::clientstate->full_update();
                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::SetCursorPosX(245);
                ImGui::BeginChild("Account Changers", ImVec2(236, 505), true);
                {
                    if (ImGui::Button(XorStr("Unlock Achievements"), ImVec2{ 217.f, 19.f }))
                    {
                        const auto& user_stats = interfaces::engine->getsteamcontext()->steam_user_stats;
                        user_stats->request_current_stats();
                        for (std::uint32_t i = 0u; i < user_stats->achievements_count(); ++i)
                        {
                            user_stats->set_achievement(user_stats->get_achievement_name(i));
                        }
                        user_stats->store_stats();
                    }
                    if (ImGui::Button(XorStr("Lock Achievements"), ImVec2{ 217.f, 19.f }))
                    {
                        const auto& user_stats = interfaces::engine->getsteamcontext()->steam_user_stats;
                        user_stats->request_current_stats();
                        for (std::uint32_t i = 0u; i < user_stats->achievements_count(); ++i)
                        {
                            user_stats->clear_achievement(user_stats->get_achievement_name(i));
                        }
                        user_stats->store_stats();
                    }
                    ImGui::Checkbox("Enable Knife Drop", &variables::config::dropknife);
                    if (ImGui::Button("Ghost Knife", { 220,20 }))
                    {
                        interfaces::engine->execute_cmd("give weapon_knife_ghost;ent_fire weapon_knife addoutput “classname weapon_knifegg”\n");
                    }
                    if (ImGui::Button("Golden Knife", { 220,20 }))
                    {
                        interfaces::engine->execute_cmd("give weapon_knifegg; ent_fire weapon_knife addoutput “classname weapon_knifegg”\n");
                    }
                    if (variables::config::mmregionenable && !interfaces::engine->is_connected() && !interfaces::engine->is_in_game())
                        *force_relay_cluster_value = data_center_list[variables::config::mmregion];
                    ImGui::Checkbox(XorStr("Enable Region Changer"), &variables::config::mmregionenable);
                    ImGui::Combo(XorStr("Default"), &variables::config::mmregion, region, IM_ARRAYSIZE(region));
                }
                ImGui::EndChild();
                break;
            case 5:
                ImGui::SetCursorPosX(5);
                ImGui::SetCursorPosY(5);
                ImGui::BeginChild("Configs", ImVec2(236, 486), true);
                {
                    static int config_index = -1;
                    static char buffer[20];

                    ImGui::SetNextItemWidth(220.f);
                    ImGui::InputTextWithHint("##cfg_name", "Enter Config Name", buffer, 10);

                    static ImGuiTextFilter configs_filter;
                    configs_filter.Draw("##cfg_filter", 220.f);

                    ImGui::SetNextItemWidth(220.f);
                    if (ImGui::BeginListBox("##config_listbox"))
                    {
                        const auto& configs_vector = variables::configs;
                        for (std::size_t i = 0u; i < configs_vector.size(); ++i)
                        {
                            const auto& config_name = configs_vector[i].data();
                            if (configs_filter.PassFilter(config_name))
                            {
                                if (ImGui::Selectable(config_name, i == config_index))
                                {
                                    config_index = i;
                                }
                            }
                        }
                        ImGui::EndListBox();
                    }

                    if (ImGui::Button("Create Config", { 220,20 }))
                    {
                        variables::create_file(buffer);
                    }

                    if (config_index != -1 && config_index < static_cast<int>(variables::configs.size()))
                    {
                        if (ImGui::Button("Save", ImVec2{ 106.f, 20.f }))
                        {
                            variables::save(config_index);
                        }

                        ImGui::SameLine();

                        if (ImGui::Button("Load", ImVec2{ 106.f, 20.f }))
                        {
                            variables::load(config_index);
                            if (interfaces::engine->is_connected() && csgo::local_player->is_alive())
                            {
                                interfaces::console->get_convar("cl_fullupdate")->fnChangeCallback = 0;
                            }
                        }

                        if (ImGui::Button("Delete Config", { 220,20 }))
                        {
                            variables::delete_file(config_index);
                        }
                    }

                    if (ImGui::Button("Update Configs", { 220,20 }))
                    {
                        variables::update_configs();
                    }
                }
                ImGui::EndChild();
                ImGui::SameLine();
                ImGui::SetCursorPosX(245);
                ImGui::BeginChild("LUA/Settings", ImVec2(236, 486), true);
                {
                    //Settings
                    ImGui::Text("Menu Color", &variables::config::menu_color);
                    ImGui::SameLine();
                    CustomColorSelect("##menu_color", variables::config::menu_color, true);
                    ImGui::Checkbox("Watermark", &variables::config::watermark);
                    ImGui::Checkbox("GUI Blackout", &variables::config::blackout);
                    ImGui::Checkbox("Disable Panorama Blur", &variables::config::disable_blur);
                    ImGui::Checkbox("Player List", &variables::config::playerlistmenu);
                    ImGui::Checkbox("Exploit List", &variables::config::exploitlistmenu);
                    ImGui::Checkbox("Spotify API", &variables::config::spotify);
                    ImGui::Checkbox("Info", &variables::config::netchannels);
                    ImGui::Checkbox("pDebug Info", &variables::config::debuginfodump);
                    ImGui::Checkbox("Jiggle View Debug", &variables::config::jiggledebuginfo);
                    ImGui::Checkbox("Indicators", &variables::config::indicators);
                    if (ImGui::Button("Dump Steam-IDs", { 220,20 }))
                    {
                        utilities::dump_steam_id();
                    }
                }
                ImGui::EndChild();
                ImGui::Text(("Build Date: " __DATE__));
                ImGui::SameLine();
                ImGui::SetCursorPosX(360);
                if (std::strstr(GetCommandLineA(), "-insecure"))
                {
                    ImGui::SameLine();
                    ImGui::Text(VERSION);
                }
                else
                {
                    ImGui::SameLine();
                    ImGui::Text(VERSION2);
                }
                break;
            }
        }
        ImGui::EndChild();
    }
    ImGui::EndChild();
    ImGui::End();
}

void menu::playerlist()
{
    if (!variables::config::playerlistmenu)
        return;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.20f, 0.20f, 0.20f, 1.00f));
    ImGui::SetNextWindowSize(ImVec2{ 600.f, 400.f }, ImGuiCond_Once);
    ImGui::Begin("playerlist", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleColor();

    ImVec2 pos = ImGui::GetWindowSize();
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.08f, 0.08f, 0.08f, 1.00f));

    ImGui::SetCursorPosX(-3);
    ImGui::SetCursorPosY(4);

    ImGui::BeginChild("FirstChild", ImVec2(ImGui::GetContentRegionAvail().x * 2, ImGui::GetContentRegionAvail().y * 2 - 384), false);
    {
        ImGui::PopStyleColor();

        ImVec2 startPos = ImGui::GetCursorScreenPos();
        ImVec2 endPos = ImVec2(startPos.x + 1000.f, startPos.y);
        ImGui::GetWindowDrawList()->AddLine(startPos, endPos, ImColor(variables::config::menu_color[0], variables::config::menu_color[1], variables::config::menu_color[2]), 3.f);
        if (interfaces::engine->is_in_game() && csgo::local_player) {
            ImGui::Columns(3, NULL);
            ImGui::Text("Name");
            ImGui::NextColumn();
            ImGui::Text("Health");
            ImGui::NextColumn();
            ImGui::Text("Money");
            ImGui::NextColumn();
            static player_t* selectedPlayer;
            static player_info_t selectedPlayerInfo;
            for (int i = 1; i < interfaces::globals->max_clients; i++) {
                player_t* p = (player_t*)interfaces::entity_list->get_client_entity(i);
                if (p) {
                    ImGui::Separator();
                    player_info_t info;
                    interfaces::engine->get_player_info(i, &info);
                    ImGui::TextColored(p->team() == 2 ? ImColor(229, 189, 94, 255) : ImColor(110, 149, 215, 255), "%s", info.name);
                    if (ImGui::IsItemClicked()) {
                        selectedPlayer = p;
                        selectedPlayerInfo = info;
                        ImGui::OpenPopup("Player Popup");
                    }
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("Click for player settings!");
                    }

                    ImGui::NextColumn();
                    ImColor healthColor = ImColor(0, 255, 0);
                    ImGui::ColorConvertHSVtoRGB(((float)p->health() - 20.f) / 255.f, 1.f, 1.f, healthColor.Value.x, healthColor.Value.y, healthColor.Value.z);
                    ImGui::TextColored(healthColor, "%d", p->health());
                    ImGui::NextColumn();
                    ImGui::TextColored(ImColor(100, 200, 0, 255), "$%d", p->money());
                    ImGui::NextColumn();
                }
            }
            if (ImGui::BeginPopup("Player Popup")) {
                ImGui::Text("Player Options | %s", selectedPlayerInfo.name);
                ImGui::Separator();
                if (selectedPlayer) {
                    ImGui::Text("Name: %s", selectedPlayerInfo.name); ImGui::SameLine(); if (ImGui::Button("Steal Name")) {
                        static auto nameConvar = interfaces::console->get_convar("name");
                        nameConvar->fnChangeCallback = 0;

                        char* name = selectedPlayerInfo.name;
                        strcat(name, " ");
                        nameConvar->set_value(name);
                    }
                    ImGui::Text("GUID: %s", selectedPlayerInfo.guid);
                    ImGui::Text("XUID: %li", selectedPlayerInfo.xuid);

                    ImGui::Separator();
                    static char message[128] = "";
                    ImGui::InputText("Message##tbox", message, IM_ARRAYSIZE(message));
                    static char skinName[128] = "★ M9 Bayonet | Doppler";
                    ImGui::InputText("Skin/Weapon##tbox", skinName, IM_ARRAYSIZE(skinName));
                    ImGui::Text("Send fake: ");
                    ImGui::SameLine();
                    if (ImGui::Button("Message##btn")) {
                        char radioMessage[512];
                        snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8%s :\x01 %s\"", selectedPlayerInfo.name, message);
                        interfaces::engine->execute_cmd(radioMessage);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("VAC")) {
                        char radioMessage[512];
                        snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x02""%s has been permanently banned from official CS:GO servers.\"", selectedPlayerInfo.name);
                        interfaces::engine->execute_cmd(radioMessage);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Kick")) {
                        char radioMessage[512];
                        snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x01""Player %s left the game (Kicked from the session)\"", selectedPlayerInfo.name);
                        interfaces::engine->execute_cmd(radioMessage);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Unbox")) {
                        char radioMessage[512];
                        snprintf(radioMessage, sizeof(radioMessage), "playerchatwheel . \"Cheer! \xe2\x80\xa8""\x0B""%s \x01 has opened a container and found: \x02%s\"", selectedPlayerInfo.name, skinName);
                        interfaces::engine->execute_cmd(radioMessage);
                    }
                    ImGui::SameLine();
                    ImGui::TextDisabled("?");
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip("Sends a fake message into the chat via a radio message that uses\nchars to create a newline and change colours (pastebin.com/pZvCnGaC),\nyou can do this legit too via the 'playerchatwheel . \"\"' command!\n\nOnly works if you are alive and only teammates can see the message :(");
                }
                ImGui::EndPopup();
            }
            ImGui::Separator();
            ImGui::Columns(1);
        }
    }
    ImGui::EndChild();
    ImGui::End();
}

void menu::exploitlist()
{
    if (!variables::config::exploitlistmenu)
        return;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.20f, 0.20f, 0.20f, 1.00f));
    ImGui::SetNextWindowSize(ImVec2{ 600.f, 400.f }, ImGuiCond_Once);
    ImGui::Begin("exploitlist", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleColor();

    ImVec2 pos = ImGui::GetWindowSize();
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.08f, 0.08f, 0.08f, 1.00f));

    ImGui::SetCursorPosX(-3);
    ImGui::SetCursorPosY(4);

    ImGui::BeginChild("ExploitChild", ImVec2(ImGui::GetContentRegionAvail().x * 2, ImGui::GetContentRegionAvail().y * 2 - 384), false);
    {
        ImGui::PopStyleColor();

        ImVec2 startPos = ImGui::GetCursorScreenPos();
        ImVec2 endPos = ImVec2(startPos.x + 1000.f, startPos.y);
        ImGui::GetWindowDrawList()->AddLine(startPos, endPos, ImColor(variables::config::menu_color[0], variables::config::menu_color[1], variables::config::menu_color[2]), 3.f);
        ImGui::SetCursorPosX(12);
        ImGui::SetCursorPosY(7);
        ImGui::BeginChild("ExploitChild2", ImVec2(582, 380), true);
        {
            ImGui::Checkbox(XorStr("legit extended aa"), &variables::config::antiaim::legit_aa);
            ImGui::Checkbox(XorStr("breaklby"), &variables::config::antiaim::break_lby);
            ImGui::SliderInt(XorStr("update"), &variables::config::antiaim::next_update, 0, 200);
     
        }
        ImGui::EndChild();
    }
    ImGui::EndChild();
    ImGui::End();
}

// credits to:

// SoLID_HAX#5457 - Helped fixing the ImGui window spacing problem.

//ImGui::Checkbox("Watermark", &variables::config::watermark);
//CustomColorSelect("##menu_color", variables::config::menu_color, true);

/*
ImGui::Checkbox(XorStr("Enable Fog"), &variables::config::fogenable);
ImGui::SliderFloat(XorStr("Density"), &variables::config::fogmaxdensity, 0.0f, 1.0f, "%.2f");
ImGui::SliderInt(XorStr("Start"), &variables::config::fogstart, 0, 1000);
ImGui::SliderInt(XorStr("End"), &variables::config::fogend, 0, 2000);
*/