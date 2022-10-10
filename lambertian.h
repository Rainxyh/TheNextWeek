#pragma once
#include "material.h"
#include "texture.h"

class lambertian : public material
{
public:
	lambertian(){};
	lambertian(texture *albedo) : albedo(albedo){};

	virtual bool scatter(const ray &ray_in, const hit_record &rec, vec::vec3 &attenuation, ray &scattered) const override
	{
		vec::vec3 target = rec.point + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.point, target - rec.point, ray_in.get_time());
		attenuation = albedo->value(rec.u, rec.v, rec.point);
		return true;
	}

	virtual const material *get_class_type(void) const override
	{
		return this;
	}

	texture *albedo;
};