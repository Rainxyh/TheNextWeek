#pragma once
#include "texture.h"
class checker_texture : public texture
{
public:
    checker_texture();
    checker_texture(texture *odd, texture *even) : odd(odd), even(even){};
    virtual vec::vec3 value(float u, float v, const vec::vec3 &point) const override
    {
        float sines = sin(10 * point.x()) * sin(10 * point.y()) * sin(10 * point.z());
        if (sines < 0)
            return odd->value(u, v, point);
        else
            return even->value(u, v, point);
    }

    virtual const checker_texture* get_class_type(void) const override{
        return this;
    }

    texture *odd;
    texture *even;
};