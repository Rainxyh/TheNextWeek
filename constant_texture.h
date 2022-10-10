#pragma once
#include "texture.h"
class constant_texture : public texture
{
public:
    constant_texture();
    constant_texture(vec::vec3 color) : color(color){};

    virtual vec::vec3 value(float u, float v, const vec::vec3 &point) const override
    {
        return color;
    }

    virtual const constant_texture* get_class_type(void) const override{
        return this;
    }

    vec::vec3 color;
};
