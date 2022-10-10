#pragma once
#include "material.h"
class dielectric : public material
{
public:
	dielectric(float ri) : eta(ri){};

	/*
	attribute:
		float eta = n'/n > 1
	parameter:
		ray& ray_in 入射光线
		hit_record& rec 视点信息
		vec::vec3& attenuation 衰减量
		ray& scattered 散射光线
	*/

	virtual bool scatter(const ray &ray_in, const hit_record &rec, vec::vec3 &attenuation, ray &scattered) const override
	{
		vec::vec3 outward_normal;							   // 外向法线 将法线转换为与入射光位于同一平面
		vec::vec3 reflected = reflect(ray_in.dir, rec.normal); // 反射方向
		vec::vec3 refracted;
		attenuation = vec::vec3(1, 1, 1);
		float ni_over_nt;
		float reflect_prob;
		float cosine_theta, cosine_theta_prime;
		if (dot(ray_in.direction(), rec.normal) > 0)
		{								  // 1、出射光线 当半径为正时球内的折射光线 射出球面 出射方向与法线同向 2、当半径为负时 入射光线与法线同向(法线指向球心内部)
			outward_normal = -rec.normal; // 由于法线始终从球心指向外部 将法线转换至与入射光线同侧
			ni_over_nt = eta;			  // 光密到光疏
			cosine_theta_prime = dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
			cosine_theta = sqrt(1 - eta * eta * (1 - cosine_theta_prime * cosine_theta_prime)); // 如果非球体有bug 因为入射球的光线一定能够出射
		}
		else
		{ // 入射光线
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / eta;
			cosine_theta = -dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
		}
		if (refract(ray_in.direction(), outward_normal, ni_over_nt, refracted))
		{ // 若满足发生折射的条件
			reflect_prob = schlick(cosine_theta, eta);
		}
		else
		{ // 若发生全反射
			reflect_prob = 1.0;
		}
		if (rand_float() < reflect_prob)
		{ // 发生反射
			scattered = ray(rec.point, reflected, ray_in.get_time());
		}
		else
		{ // 发生折射
			scattered = ray(rec.point, refracted, ray_in.get_time());
		}
		return true;
	}

	virtual const material *get_class_type(void) const override
	{
		return this;
	}

	float eta;
};
