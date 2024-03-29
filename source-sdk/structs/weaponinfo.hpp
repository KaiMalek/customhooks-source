#pragma once

class weapon_info_t {
public:
	char		u0[0x4];
	char		*weapon_name;
	char		u1[0xC];
	__int32		weapon_max_clip;
	char		u2[0xC];
	__int32		weapon_max_reserved_ammo;
	char		u3[0x4];
	char		*weapon_model_path;
	char		*weapon_model_path_alt;
	char		*weapon_dropped_model_path;
	char		*weapon_default_clip;
	char		u4[0x44];
	char		*weapon_bullet_type;
	char		u5[0x4];
	char		*weapon_hud_name;
	char		*weapon_name_alt;
	char		u6[0x38];
	__int32		weapon_type;
	__int32 m_iWeaponType; //0x00C8
	__int32		weapon_type_alt;
	__int32		weapon_price;
	__int32		weapon_reward;
	char		*weapon_type_name;
	float		weapon_unknown_float;
	char		u7[0xC];
	unsigned char	weapon_full_auto;
	char		u8[ 0x3 ];
	__int32		weapon_damage;
	float		weapon_armor_ratio;
	__int32		weapon_bullets;
	float		weapon_penetration;
	char		u9[0x8];
	float		weapon_range;
	float		weapon_range_mod;
	float		weapon_throw_velocity;
	char		u10[0xC];
	unsigned char	weapon_has_silencer;
	char		u11[0xF];
	float		weapon_max_speed;
	float		weapon_max_speed_alt;
	float		weapon_attack_move_factor;
	float		weapon_spread;
	float		weapon_spread_alt;
	float		weapon_inaccuracy_crouch;
	float		weapon_inaccuracy_crouch_alt;
	float		weapon_inaccuracy_stand;
	float		weapon_inaccuracy_stand_alt;
	float		weapon_inaccuracy_jump;
	float		weapon_inaccuracy_jump_alt;
	char		u12[0x28];
	__int32		weapon_recoil_seed;
	char		u13[0x68];
	char		*weapon_traces_type;
};
