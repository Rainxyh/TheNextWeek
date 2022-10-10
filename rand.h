#pragma once
#include<random>
#include"vec3.h"

std::random_device rd;
std::default_random_engine random_engine(rd());
std::uniform_real_distribution<float> distribution(0, 1);

float rand_float() {
	return distribution(random_engine);
}

float square_rand_float() {
	return distribution(random_engine);
}

vec::vec3 random_in_unit_sphere() {
	vec::vec3 p;
	do {
		p = 2 * vec::vec3(rand_float(), rand_float(), rand_float()) - vec::vec3(1, 1, 1);
	} while (p.length() >= 1.0);
	return p;
}

vec::vec3 random_in_unit_disk() {
	vec::vec3 p;
	do {
		p = 2 * vec::vec3(rand_float(), rand_float(), 0) - vec::vec3(1, 1, 0);
	} while (p.length() >= 1.0);
	return p;
}