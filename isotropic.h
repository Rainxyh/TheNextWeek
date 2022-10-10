#pragma once
#include "material.h"
#include "texture.h"
class isotropic : public material
{
public:
    isotropic(){};
    isotropic(texture *albedo) : albedo(albedo){};

    virtual bool scatter(const ray &ray_in, const hit_record &rec, vec::vec3 &attenuation, ray &scattered) const override
    {
        scattered = ray(rec.point, random_in_unit_sphere(), ray_in.get_time());
        attenuation = albedo->value(rec.u, rec.v, rec.point);
        return true;
    }

    virtual const material *get_class_type(void) const override
    {
        return this;
    }

    texture *albedo;
};