#pragma once
#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable_list(){};
	hitable_list(hitable **list, int list_size) : list(list), list_size(list_size){};
	virtual bool hit(const ray &ray, float t_min, float t_max, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &bbox) const;

	hitable **list;
	int list_size;
};

bool hitable_list::hit(const ray &ray, float t_min, float t_max, hit_record &rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(ray, t_min, closest_so_far, temp_rec)) // sphere or moving sphere instances, call its overridden virtual method
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

bool hitable_list::bounding_box(float t0, float t1, aabb &bbox) const
{
	if (list_size < 1)
		return false;
	aabb temp_box;
	bool first_true = list[0]->bounding_box(t0, t1, temp_box);
	if (!first_true)
		return false;
	else
		bbox = temp_box;
	for (int i = 1; i < list_size; i++)
	{
		if (list[0]->bounding_box(t0, t1, temp_box))
		{
			bbox = surrounding_box(bbox, temp_box);
		}
		else
			return false;
	}
	return true;
}