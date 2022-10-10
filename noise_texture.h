#pragma once
#include "texture.h"
#include "perlin.h"

class noise_texture : public texture
{
public:
    noise_texture(){};
    noise_texture(float scale) : scale(scale){};
    virtual vec::vec3 value(float u, float v, const vec::vec3 &point) const override
    {
        //return vec::vec3(1) * noise.noise(scale * point);
        return vec::vec3(1) * 0.5 * (1 + sin(scale * point.z() + 10 * noise.turb(point)));
    }

    virtual const noise_texture* get_class_type(void) const override{
        return this;
    }

    perlin noise;
    float scale;
};