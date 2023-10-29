#ifndef sphere_h
#define sphere_h
#include <iostream>
#include <cmath>
#include "vector3.h"
#include "pixel.h"
#include "ray.h"

struct sphere {
	vector3 position = vector3();
	double radius = 0;
	color shade = color();
	double emission = 0;

	sphere() {}

	sphere(vector3 v, double r) {
		position = v;
		radius = r;
	}
	sphere(double x, double y, double z, double r) {
		position = vector3(x, y, z);
		radius = r;
	}
	sphere(vector3 v, double r, color c) {
		position = v;
		radius = r;
		shade = c;
	}
	sphere(vector3 v, double r, color c, double e) {
		position = v;
		radius = r;
		shade = c;
		emission = e;
	}

	double intersectsAlong(ray r) {
		vector3 SminusO = r.origin - position;
		double a = r.direction.length_squared();
		double b = 2.0 * dot(r.direction, SminusO);
		double c = SminusO.length_squared() - radius * radius;
		double underRoot = b*b - 4 * a * c;
		if (underRoot < 0.0) {
			return -1;
		}
		else if (underRoot == 0.0) {
			return (-b) / 2*a;
		}
		else {
			return (-b - sqrt(b*b - 4*a*c)) / 2*a;
		}
	}
	bool intersects(ray r) {
		if (intersectsAlong(r) != -1) {
			return true;
		}
		return false;
	}
};
#endif
