#pragma once
#include "hitable.h"
class moving_sphere : public hitable
{
public:
	moving_sphere(){};
	moving_sphere(vec::vec3 center0, vec::vec3 center1, float time0, float time1, float radius, material *mat_ptr) : center0(center0), center1(center1), time0(time0), time1(time1), radius(radius), mat_ptr(mat_ptr){};

	virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &bbox) const;
	vec::vec3 center(float time) const;

	vec::vec3 center0, center1;
	float time0, time1;
	float radius;
	material *mat_ptr;
};

// replace "center" with "center(r.time())"
bool moving_sphere::hit(const ray &ray, float t_min, float t_max, hit_record &rec) const
{
	vec::vec3 moving_center = center(ray.get_time());
	vec::vec3 oc = ray.ori - moving_center;
	float a = vec::dot(ray.dir, ray.dir);
	float b = vec::dot(oc, ray.dir);
	float c = vec::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	auto has_resolve_or_not = [&](float temp) -> bool
	{
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.point = ray.point_at_parameter(temp);
			rec.normal = (rec.point - moving_center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		return false;
	};
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a; // first solution
		if (has_resolve_or_not(temp))
			return true;
		temp = (-b + sqrt(discriminant)) / a; // second solution
		if (has_resolve_or_not(temp))
			return true;
	}
	return false;
}

bool moving_sphere::bounding_box(float t0, float t1, aabb &bbox) const
{
	aabb bbox0 = aabb(center0 - vec::vec3(radius), center0 + vec::vec3(radius));
	aabb bbox1 = aabb(center1 - vec::vec3(radius), center1 + vec::vec3(radius)); // wrong write center0, sphere is torn
	bbox = surrounding_box(bbox0, bbox1);
	return true;
}

vec::vec3 moving_sphere::center(float time) const
{
	return center0 + (time - time0) / (time1 - time0) * (center1 - center0);
}