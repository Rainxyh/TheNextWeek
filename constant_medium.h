#pragma once
#include "hitable.h"
#include "isotropic.h"
class constant_medium : public hitable
{
public:
    constant_medium(){};
    constant_medium(hitable *boundary, float density, texture *tex) : boundary(boundary), density(density)
    {
        phase_function = new isotropic(tex);
    };

    virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const override;

    virtual bool bounding_box(float t0, float t1, aabb &bbox) const override
    {
        return boundary->bounding_box(t0, t1, bbox);
    }

    hitable *boundary;
    float density;
    material *phase_function;
};

inline bool constant_medium::hit(const ray &ray, float t_min, float t_max, hit_record &rec) const
{
    bool db = (rand_float() < 0.00001);
    db = false;
    hit_record rec1, rec2;
    if (boundary->hit(ray, -FLT_MAX, FLT_MAX, rec1))
    {
        if (boundary->hit(ray, rec1.t + 0.0001, FLT_MAX, rec2))
        {
            if (db)
                std::cerr << "\n0 t1" << rec1.t << " " << rec2.t << "\n";
            if (rec1.t < t_min)
                rec1.t = t_min;
            if (rec2.t > t_max)
                rec2.t = t_max;
            if (rec1.t >= rec2.t)
                return false;
            if (rec1.t < 0)
                rec1.t = 0;
            float distance_inside_boundary = (rec2.t - rec1.t) * ray.direction().length();
            float hit_distance = -(1. / density) * log(rand_float());
            if (hit_distance < distance_inside_boundary)
            {
                if (db)
                    std::cerr << "hit_distance = " << hit_distance << "\n";
                rec.t = rec1.t + hit_distance / ray.direction().length();
                if (db)
                    std::cerr << "rec.t = " << rec.t << "\n";
                rec.point = ray.point_at_parameter(rec.t);
                if (db)
                    std::cerr << "rec.point = " << rec.point << "\n";
                rec.normal = vec::vec3(1, 0, 0); // arbitrary
                rec.mat_ptr = phase_function;
                return true;
            }
        }
    }
    return false;
}