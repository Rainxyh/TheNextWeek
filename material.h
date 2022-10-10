#pragma once
#include "ray.h"
#include "hitable.h"
#include "rand.h"

class material
{
public:
	// hit_record is to avoid a bunch of arguments so we can stuff whatever info we want in there. You can use arguments instead;
	virtual bool scatter(const ray &ray_in, const hit_record &rec, vec::vec3 &attenuation, ray &scattered) const = 0;
	virtual const material *get_class_type(void) const = 0;
	virtual vec::vec3 emitted(float u, float v, const vec::vec3 &point) const
	{
		return vec::vec3(0);
	}
};

vec::vec3 gamma_correct(vec::vec3 col)
{
	return vec::vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
}

inline vec::vec3 reflect(const vec::vec3 &v, const vec::vec3 &n)
{
	return v - 2 * dot(v, n) * n;
}

inline bool refract(const vec::vec3 &v, const vec::vec3 &normal, float eta, vec::vec3 &refracted)
{
	vec::vec3 uv = unit_vector(v);
	float cosine = dot(uv, normal);
	float discrimination = 1.0f - eta * eta * (1.0f - cosine * cosine);
	if (discrimination > 0)
	{
		refracted = eta * (uv - normal * cosine) - normal * sqrt(discrimination);
		return true;
	}
	return false;
}

inline float schlick(float cosine, float eta)
{
	float r0 = (1.0f - eta) / (1.0f + eta);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * (float)pow((1 - cosine), 5);
}
