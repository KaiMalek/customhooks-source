#pragma once
#define deg_to_rad( x )  ( (float)(x) * (float)( M_PI / 180.f ) )
#define rad_to_deg( x )  ( (float)(x) * (float)( 180.f / M_PI ) )

constexpr double pi = 3.14159265358979323846;

namespace math {
	void correct_movement(vec3_t old_angles, c_usercmd* cmd, float old_forwardmove, float old_sidemove);
	void angle_vectors_alternative(vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up);
	void vector_angles_alternative(const vec3_t& forward, vec3_t& angles);
	vec3_t calculate_angle_alternative(const vec3_t& a, const vec3_t& b);
	vec3_t calculate_angle(const vec3_t& source, const vec3_t& destination, const vec3_t& viewAngles);
	void sin_cos(float r, float* s, float* c);
	vec3_t angle_vector(vec3_t angle);
	void transform_vector(vec3_t&, matrix_t&, vec3_t&);
	void vector_angles(vec3_t&, vec3_t&);
	void angle_vectors(vec3_t&, vec3_t*, vec3_t*, vec3_t*);
	void angle_to_vectors(const vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up);
	vec3_t vector_add(vec3_t&, vec3_t&);
	vec3_t vector_subtract(vec3_t&, vec3_t&);
	vec3_t vector_multiply(vec3_t&, vec3_t&);
	vec3_t vector_divide(vec3_t&, vec3_t&);
	float get_fov(const vec3_t& view_angle, const vec3_t& aim_angle);
	vec3_t calculate_angle_backtrack(vec3_t& a, vec3_t& b);
	bool screen_transform(const vec3_t& point, vec3_t& screen);
	bool world_to_screen(const vec3_t& origin, vec3_t& screen);
	vec3_t normalize(vec3_t angle);
	float NormalizeAngleFloat(float flAng);
	template <typename t> t clamp_value(t value, t min, t max) {
			if (value > max) {
				return max;
			}
			if (value < min) {
				return min;
			}
			return value;
		}
};