#include "utilities.hpp"
#include "../utilities/csgo.hpp"
#include <psapi.h>
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <Psapi.h>

bool FileLog = false;
std::ofstream logFile;

std::uint8_t* utilities::pattern_scan(const char* module_name, const char* signature) noexcept {
    const auto module_handle = GetModuleHandleA(module_name);

    if (!module_handle)
        return nullptr;

    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
    auto nt_headers =
        reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

    auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
    auto pattern_bytes = pattern_to_byte(signature);
    auto scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle);

    auto s = pattern_bytes.size();
    auto d = pattern_bytes.data();

    for (auto i = 0ul; i < size_of_image - s; ++i) {
        bool found = true;

        for (auto j = 0ul; j < s; ++j) {
            if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found)
            return &scan_bytes[i];
    }

    return nullptr;
}

std::uint8_t* utilities::pattern_scan(void* module, const char* signature) {
    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto dos_headers = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
    auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>((std::uint8_t*)module + dos_headers->e_lfanew);

    auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
    auto pattern_bytes = pattern_to_byte(signature);
    auto scan_bytes = reinterpret_cast<std::uint8_t*>(module);

    auto s = pattern_bytes.size();
    auto d = pattern_bytes.data();

    for (auto i = 0ul; i < size_of_image - s; ++i) {
        bool found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return &scan_bytes[i];
        }
    }
    return nullptr;
}

std::uint8_t* utilities::pattern_scan2(void* module, const char* signature) {
    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto dos_headers = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
    auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>((std::uint8_t*)module + dos_headers->e_lfanew);

    auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
    auto pattern_bytes = pattern_to_byte(signature);
    auto scan_bytes = reinterpret_cast<std::uint8_t*>(module);

    auto s = pattern_bytes.size();
    auto d = pattern_bytes.data();

    for (auto i = 0ul; i < size_of_image - s; ++i) {
        bool found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return &scan_bytes[i];
        }
    }
    return nullptr;
}

#if RELEASE
#if BETA
#define VERSION ("[alpha]")
#else
#define VERSION ("[beta] ")
#endif
#else
#define VERSION ("[alpha]")
#endif

void utilities::console_printing() {
    static bool once = []() {
        interfaces::engine->execute_cmd("log_color General 00FFFFFF; log_color Console 00FFFFFF\n");
        interfaces::engine->execute_cmd("toggleconsole\n");
        interfaces::engine->execute_cmd("clear\n");
        interfaces::console->console_printf("customhooks build type: ");
        interfaces::console->console_printf(VERSION);
        interfaces::console->console_printf("\n");
        return true;
    } ();
}

void utilities::dump_steam_id() {
    if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game()) {
        interfaces::console->console_printf(VERSION);
        interfaces::console->console_printf("you have to be in a game to dump players info. \n");
        return;
    }

    static constexpr auto steam_id64_constant = 0x0110000100000000ULL;

    for (int i = 1; i <= interfaces::globals->max_clients; i++) {
        auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

        if (!entity)
            continue;

        player_info_t info;
        interfaces::engine->get_player_info(i, &info);


        auto steam_id64 = steam_id64_constant + info.friendsid;

        std::stringstream output;

        std::string player_name = info.name;
        std::transform(player_name.begin(), player_name.end(), player_name.begin(), ::tolower);

        if (!info.fakeplayer) {
            interfaces::console->console_printf("[alpha] ");
            output << "player " << player_name.c_str() << ": " << "steamcommunity.com/profiles/" << steam_id64 << "/" << "\n";
        }
        else {
            interfaces::console->console_printf("[alpha] ");
            output << "player " << player_name.c_str() << ": " << "bot" << "\n";
        }

        interfaces::console->console_printf("%s", output.str());

    }
}

const char* utilities::hitgroup_name(int hitgroup) {
    switch (hitgroup) {
    case hitgroup_head:
        return "head";
    case hitgroup_leftleg:
        return "left leg";
    case hitgroup_rightleg:
        return "right leg";
    case hitgroup_stomach:
        return "stomach";
    case hitgroup_leftarm:
        return "left arm";
    case hitgroup_rightarm:
        return "right arm";
    default:
        return "body";
    }
}

int utilities::epoch_time() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void utilities::console_warning(const char* msg, ...) {
    if (msg == nullptr)
        return;
    typedef void(__cdecl* console_warning_fn)(const char* msg, va_list);
    static console_warning_fn fn = (console_warning_fn)GetProcAddress(GetModuleHandle("tier0.dll"), "Warning");
    char buffer[989];
    va_list list;
    va_start(list, msg);
    vsprintf(buffer, msg, list);
    va_end(list);
    fn(buffer, list);
}

void utilities::apply_name(const char* name_to_change) {
    auto name = interfaces::console->get_convar("name");
    name->callbacks.size = 0;

    name->set_value(name_to_change);
}

void utilities::apply_clan_tag(const char* name) {
    using Fn = int(__fastcall*)(const char*, const char*);
    static auto apply_clan_tag_fn = reinterpret_cast<Fn>(utilities::pattern_scan("engine.dll", sig_apply_clan_tag));
    apply_clan_tag_fn(name, name);
};