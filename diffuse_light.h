#pragma once
#include "material.h"
#include "texture.h"

class diffuse_light : public material
{
public:
    diffuse_light(){};
    diffuse_light(texture *emit) : emit(emit){};
    virtual bool scatter(const ray &ray_in, const hit_record &rec, vec::vec3 &attenuation, ray &scattered) const override
    {
        return false;
    }
    virtual const material *get_class_type(void) const override
    {
        return this;
    }

    virtual vec::vec3 emitted(float u, float v, const vec::vec3 &point) const override
    {
        return emit->value(u, v, point);
    }

    texture *emit;
};