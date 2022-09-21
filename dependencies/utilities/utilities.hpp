#pragma once
#include <cstdint>
#include "../../source-sdk/math/vector3d.hpp"
#include <time.h>

namespace utilities {
	template< typename t >
	__forceinline static t call_virtual(void* name, int offset) {
		int* table = *(int**)name;
		int address = table[offset];
		return (t)(address);
	}

	std::uint8_t* pattern_scan(const char* module_name, const char* signature) noexcept;
	std::uint8_t* pattern_scan(void* module, const char* signature);
	std::uint8_t* pattern_scan2(void* module, const char* signature);
	void console_printing();
	void dump_steam_id();

	const char* hitgroup_name(int hitgroup);

	int epoch_time();

	void console_warning(const char* msg, ...);

	void apply_name(const char* name_to_change);

	void apply_clan_tag(const char* name);

	// Virtual stuff
	template <typename T, std::uint32_t index, typename ...Arguments>
	inline auto call_virtual(void* const class_base, Arguments... args) noexcept
	{
		using fn = T(__thiscall***)(void*, Arguments...);
		return ((*static_cast<fn>(class_base))[index])(class_base, args...);
	}
	inline auto get_virtual(void* const class_base, const std::uint32_t index) noexcept
	{
		return reinterpret_cast<void*>((*static_cast<int**>(class_base))[index]);
	}

	namespace fnv_1a {
		template< typename S >
		struct fnv_internal;
		template< typename S >
		struct fnv1a;

		template< >
		struct fnv_internal< uint32_t > {
			constexpr static uint32_t default_offset_basis = 0x811C9DC5;
			constexpr static uint32_t prime = 0x01000193;
		};

		template< >
		struct fnv1a< uint32_t > : public fnv_internal< uint32_t > {
			constexpr static uint32_t hash(char const* string, const uint32_t val = default_offset_basis) {
				return (string[0] == '\0') ? val : hash(&string[1], (val ^ uint32_t(string[0])) * prime);
			}

			constexpr static uint32_t hash(wchar_t const* string, const uint32_t val = default_offset_basis) {
				return (string[0] == L'\0') ? val : hash(&string[1], (val ^ uint32_t(string[0])) * prime);
			}
		};
	}

	using fnv = fnv_1a::fnv1a< uint32_t >;
}
