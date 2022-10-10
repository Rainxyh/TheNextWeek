#pragma once
#include "hitable.h"
class filp_normals : public hitable
{
public:
    filp_normals(){};
    filp_normals(hitable *ptr) : ptr(ptr){};

    virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const override
    {
        if (ptr->hit(ray, t_min, t_max, rec))
        {
            rec.normal = -rec.normal;
            return true;
        }
        return false;
    }

    virtual bool bounding_box(float t0, float t1, aabb &bbox) const override
    {
        return ptr->bounding_box(t0, t1, bbox);
    }

    hitable *ptr;
};