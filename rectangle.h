#pragma once
#include "hitable.h"
class xy_rect : public hitable
{
public:
    xy_rect(){};
    xy_rect(float x0, float y0, float x1, float y1, float k, material *mat_ptr) : x0(x0), y0(y0), x1(x1), y1(y1), k(k), mat_ptr(mat_ptr){};

    virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const override
    {
        float t = (k - ray.origin().z()) / ray.direction().z();
        if (t < t_max && t > t_min)
        {
            float x = ray.origin().x() + t * ray.direction().x();
            float y = ray.origin().y() + t * ray.direction().y();
            if (x > x0 && x < x1 && y > y0 && y < y1)
            {
                rec.point = ray.point_at_parameter(t);
                rec.mat_ptr = mat_ptr;
                rec.normal = vec::vec3(0, 0, 1);
                rec.u = (x - x0) / (x1 - x0);
                rec.v = (y - y0) / (y1 - y0);
                rec.t = t;
                return true;
            }
        }
        return false;
    }

    virtual bool bounding_box(float t0, float t1, aabb &bbox) const override
    {
        bbox = aabb(vec::vec3(x0, y0, k - 0.0001), vec::vec3(x1, y1, k + 0.0001));
        return true;
    }

    float x0, y0, x1, y1, k;
    material *mat_ptr;
};

class xz_rect : public hitable
{
public:
    xz_rect(){};
    xz_rect(float x0, float z0, float x1, float z1, float k, material *mat_ptr) : x0(x0), z0(z0), x1(x1), z1(z1), k(k), mat_ptr(mat_ptr){};

    virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const override
    {
        float t = (k - ray.origin().y()) / ray.direction().y();
        if (t < t_max && t > t_min)
        {
            float x = ray.origin().x() + t * ray.direction().x();
            float z = ray.origin().z() + t * ray.direction().z();
            if (x > x0 && x < x1 && z > z0 && z < z1)
            {
                rec.point = ray.point_at_parameter(t);
                rec.mat_ptr = mat_ptr;
                rec.normal = vec::vec3(0, 1, 0);
                rec.u = (x - x0) / (x1 - x0);
                rec.v = (z - z0) / (z1 - z0);
                rec.t = t;
                return true;
            }
        }
        return false;
    }

    virtual bool bounding_box(float t0, float t1, aabb &bbox) const override
    {
        bbox = aabb(vec::vec3(x0, z0, k - 0.0001), vec::vec3(x1, z1, k + 0.0001));
        return true;
    }

    float x0, z0, x1, z1, k;
    material *mat_ptr;
};

class yz_rect : public hitable
{
public:
    yz_rect(){};
    yz_rect(float y0, float z0, float y1, float z1, float k, material *mat_ptr) : y0(y0), z0(z0), y1(y1), z1(z1), k(k), mat_ptr(mat_ptr){};

    virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const override
    {
        float t = (k - ray.origin().x()) / ray.direction().x();
        if (t < t_max && t > t_min)
        {
            float y = ray.origin().y() + t * ray.direction().y();
            float z = ray.origin().z() + t * ray.direction().z();
            if (z > z0 && z < z1 && y > y0 && y < y1)
            {
                rec.point = ray.point_at_parameter(t);
                rec.mat_ptr = mat_ptr;
                rec.normal = vec::vec3(1, 0, 0);
                rec.u = (y - y0) / (y1 - y0);
                rec.v = (z - z0) / (z1 - z0);
                rec.t = t;
                return true;
            }
        }
        return false;
    }

    virtual bool bounding_box(float t0, float t1, aabb &bbox) const override
    {
        bbox = aabb(vec::vec3(y0, z0, k - 0.0001), vec::vec3(y1, z1, k + 0.0001));
        return true;
    }

    float y0, z0, y1, z1, k;
    material *mat_ptr;
};