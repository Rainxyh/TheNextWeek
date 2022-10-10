#pragma once
#include "hitablelist.h"
#include "rectangle.h"
#include "filp_normals.h"

class box : public hitable
{
public:
    box(){};
    box(vec::vec3 pmin, vec::vec3 pmax, material *mat_ptr) : pmin(pmin), pmax(pmax), mat_ptr(mat_ptr)
    {
        hitable **list = new hitable *[6];
        list[0] = new xy_rect(pmin.x(), pmin.y(), pmax.x(), pmax.y(), pmax.z(), mat_ptr);
        list[1] = new filp_normals(new xy_rect(pmin.x(), pmin.y(), pmax.x(), pmax.y(), pmin.z(), mat_ptr));
        list[2] = new xz_rect(pmin.x(), pmin.z(), pmax.x(), pmax.z(), pmax.y(), mat_ptr);
        list[3] = new filp_normals(new xz_rect(pmin.x(), pmin.z(), pmax.x(), pmax.z(), pmin.y(), mat_ptr));
        list[4] = new yz_rect(pmin.y(), pmin.z(), pmax.y(), pmax.z(), pmax.x(), mat_ptr);
        list[5] = new filp_normals(new yz_rect(pmin.y(), pmin.z(), pmax.y(), pmax.z(), pmin.x(), mat_ptr));
        hit_ptr = new hitable_list(list, 6);
    }

    virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const override
    {
        return hit_ptr->hit(ray, t_min, t_max, rec);
    }

    virtual bool bounding_box(float t0, float t1, aabb &bbox) const override
    {
        bbox = aabb(pmin, pmax);
        return true;
    }

    vec::vec3 pmin, pmax;
    material *mat_ptr;
    hitable *hit_ptr;
};
