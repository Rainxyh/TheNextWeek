#pragma once
#include "ray.h"
#include "rand.h"

class camera
{
public:
	// new: add t0 and t1
	camera(){};
	camera(vec::vec3 lookfrom, vec::vec3 lookat, vec::vec3 vup, float vfov, float aspect, float aperture, float focus_dist, float t0, float t1);

	ray get_ray(float s, float t);

	vec::vec3 origin;
	vec::vec3 u, v, w;
	vec::vec3 lower_left_corner;
	vec::vec3 horizontal;
	vec::vec3 vertical;
	float time0, time1; // new variables
	float lens_radius;
};

camera::camera(vec::vec3 lookfrom, vec::vec3 lookat, vec::vec3 vup, float vfov, float aspect, float aperture, float focus_dist, float t0, float t1)
{ // vfov is top to bottom in degrees
	time0 = t0;
	time1 = t1;
	lens_radius = aperture / 2;
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;

	origin = lookfrom;
	w = vec::unit_vector(lookfrom - lookat);
	u = vec::unit_vector(vec::cross(vup, w));
	v = vec::cross(w, u);
	lower_left_corner = origin - (half_width * u + half_height * v + w) * focus_dist;
	horizontal = 2 * half_width * u * focus_dist;
	vertical = 2 * half_height * v * focus_dist;
}

ray camera::get_ray(float s, float t)
{
	vec::vec3 rd = lens_radius * random_in_unit_disk();
	vec::vec3 offset = u * rd.x() + v * rd.y();
	float time = time0 + rand_float() * (time1 - time0);
	return ray(origin + offset, lower_left_corner + horizontal * s + vertical * t - origin - offset, time);
}