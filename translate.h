#pragma once
#include "hitable.h"
class translate : public hitable
{
public:
    translate(){};
    translate(hitable *hit_ptr, vec::vec3 offset) : hit_ptr(hit_ptr), offset(offset){};

    virtual bool hit(const ray &_ray, float t_min, float t_max, hit_record &rec) const override
    {
        ray moved_ray(_ray.origin() - offset, _ray.direction(), _ray.get_time());
        if (hit_ptr->hit(moved_ray, t_min, t_max, rec))
        {
            rec.point += offset;
            return true;
        }
        return false;
    }

    virtual bool bounding_box(float t0, float t1, aabb &bbox) const override
    {
        if (hit_ptr->bounding_box(t0, t1, bbox))
        {
            bbox = aabb(bbox.min() + offset, bbox.max() + offset);
            return true;
        }
        return false;
    }

    hitable *hit_ptr;
    vec::vec3 offset;
};