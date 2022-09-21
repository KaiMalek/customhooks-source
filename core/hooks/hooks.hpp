#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/menu.hpp"
#include "../features/features.hpp"

namespace hooks {
	extern WNDPROC wndproc_original;
	extern HWND window;

	bool initialize();
	void release();

	LRESULT __stdcall wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*reinterpret_cast<int**>(_class))[index]); }

	namespace create_move_proxy {
		using fn = void(__stdcall*)(int, float, bool);
		inline fn original = nullptr;
		void __stdcall hook(int sequence_number, float input_sample_time, bool is_active);
	};

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		inline fn original = nullptr;
		void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
	}

	namespace sv_cheats_get_bool {
		using fn = bool(__thiscall*)(void*);
		inline fn original = nullptr;
		bool __fastcall hook(PVOID convar, int edx);
	}

	namespace view_model {
		using fn = float(__stdcall*)();
		inline fn original = nullptr;
		float __fastcall hook();
	}

	namespace present {
		using fn = long(__stdcall*)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
		inline fn original = nullptr;
		long __stdcall hook(IDirect3DDevice9* directx, RECT* source_rect, RECT* dest_rect, HWND dest_window_override, RGNDATA* dirty_region);
	}

	namespace override_view {
		using fn = void* (__fastcall*)(i_client_mode*, void* _this, view_setup_t* setup);
		inline fn original = nullptr;
		void __fastcall hook(void* _this, void* _edx, view_setup_t* setup);
	}
	
	namespace findmdl {
		using fn = unsigned long(__thiscall*)(void*, const char*);
		inline fn original = nullptr;
		unsigned long __stdcall hook(const char* path) noexcept;
	}
	
	namespace dme {
		using fn = void(__thiscall*)(void*, void*, void*, const model_render_info_t&, matrix_t*);
		inline fn original = nullptr;
		void __fastcall hook(void* thisptr, void* edx, void* ctx, void* state, const model_render_info_t& info, matrix_t* custom_bone_to_world);
	}

	namespace file_check {
		using fn = void(__fastcall*)(void*, void*);
		inline fn original = nullptr;
		void __fastcall hook(void* ecx, void* edx);
	}

	namespace file_system {
		using fn = bool(__fastcall*)(void*, void*);
		inline fn original = nullptr;
		bool __fastcall hook(void* ecx, void* edx);
	}

	namespace do_effect {
		using fn = int(__fastcall*)(void* ecx, void* edx, int a1);
		inline fn original = nullptr;
		int __fastcall hook(void* ecx, void* edx, int a1);
	}

	namespace frame_stage_notify {
		using fn = void(__thiscall*)(i_base_client_dll*, int);
		inline fn original = nullptr;
		void __stdcall hook(int frame_stage);
	}

	namespace reset {
		using fn = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		inline fn original = nullptr;
		long __stdcall hook(IDirect3DDevice9* directx, D3DPRESENT_PARAMETERS* present_parameters);
	}
}