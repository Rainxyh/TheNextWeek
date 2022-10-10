#pragma once
#include "vec3.h"
class ray
{
public:
	ray()
	{
		ori = 0.0;
		dir = vec::vec3();
		time = 0.0f;
	};
	ray(const vec::vec3 &ori, const vec::vec3 &dir) : ori(ori), dir(dir){};
	ray(const vec::vec3 &ori, const vec::vec3 &dir, float time) : ori(ori), dir(dir), time(time){};

	vec::vec3 origin() const { return ori; }
	vec::vec3 direction() const { return dir; }
	float get_time() const { return time; }
	vec::vec3 point_at_parameter(float t) const { return vec::vec3(ori + dir * t); }

	vec::vec3 ori, dir;
	float time;
};
