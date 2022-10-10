#pragma once
#include "hitable.h"

class sphere : public hitable
{
public:
	sphere()
	{
		center = vec::vec3();
		radius = 1;
		mat_ptr = NULL;
	};
	sphere(vec::vec3 center, float radius, material *mat_ptr) : center(center), radius(radius), mat_ptr(mat_ptr){};
	virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &bbox) const;
	vec::vec3 center;
	float radius;
	material *mat_ptr;
};

bool sphere::hit(const ray &ray, float t_min, float t_max, hit_record &rec) const
{
	float a = vec::dot(ray.dir, ray.dir);
	float b = 2.0 * vec::dot(ray.dir, ray.ori - center);
	float c = vec::dot(ray.ori - center, ray.ori - center) - radius * radius;
	float delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		float temp = (-b - sqrt(delta)) / (2 * a);
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.point = ray.point_at_parameter(rec.t);
			rec.normal = (rec.point - center) / radius;
			rec.mat_ptr = mat_ptr;
			get_sphere_uv(rec.u, rec.v, rec.normal);
			return true;
		}
		temp = (-b + sqrt(delta)) / (2 * a);
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.point = ray.point_at_parameter(rec.t);
			rec.normal = (rec.point - center) / radius;
			rec.mat_ptr = mat_ptr;
			get_sphere_uv(rec.u, rec.v, rec.normal);
			return true;
		}
	}
	return false;
}

bool sphere::bounding_box(float t0, float t1, aabb &bbox) const
{
	bbox = aabb(center - vec::vec3(radius), center + vec::vec3(radius));
	return true;
}
