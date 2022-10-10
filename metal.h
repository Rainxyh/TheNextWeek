#pragma once
#include "material.h"

class metal : public material
{
public:
	metal(){};
	metal(const vec::vec3 &albedo) : albedo(albedo) { fuzz = 0.1; };
	metal(const vec::vec3 &albedo, float f) : albedo(albedo)
	{
		if (f < 1)
			fuzz = f;
		else
			fuzz = 1;
	};

	virtual bool scatter(const ray &ray_in, const hit_record &rec, vec::vec3 &attenuation, ray &scattered) const override
	{
		vec::vec3 reflected = reflect(vec::unit_vector(ray_in.dir), rec.normal);
		scattered = ray(rec.point, reflected + fuzz * random_in_unit_sphere(), ray_in.get_time());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

	virtual const material *get_class_type(void) const override
	{
		return this;
	}

	vec::vec3 albedo;
	float fuzz;
};