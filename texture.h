#pragma once
#include "vec3.h"
class texture
{
public:
    texture() {}
    virtual vec::vec3 value(float u, float v, const vec::vec3 &point) const = 0;
    virtual const texture* get_class_type(void) const = 0;
};
