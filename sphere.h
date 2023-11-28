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
	double reflectance = 0;

	sphere() {}
	sphere(vector3 _position, double _radius) : position(_position), radius(_radius) { }
	sphere(double _x, double _y, double _z, double _radius) : position(vector3(_x, _y, _z)), radius(_radius) { }
	sphere(vector3 _position, double _radius, color _shade) : position(_position), radius(_radius), shade(_shade) { }
	sphere(vector3 _position, double _radius, color _shade, double _emission) : position(_position), radius(_radius), shade(_shade), emission(_emission) { }
	sphere(vector3 _position, double _radius, color _shade, double _emission, double _reflectance) : position(_position), radius(_radius), shade(_shade), emission(_emission), reflectance(_reflectance) { }

	double intersectsAlong(ray r) {
		vector3 SminusO = r.origin - position;
		double a = r.direction.length_squared();
		double b = 2.0 * dot(r.direction, SminusO);
		double c = SminusO.length_squared() - radius * radius;
		double underRoot = b*b - 4 * a * c;
		if (underRoot < 0.0)
			return -1;
		else
			return (-b - sqrt(underRoot)) / 2*a;
	}
	bool intersects(ray r) {
		if (intersectsAlong(r) != -1) {
			return true;
		}
		return false;
	}
};
#endif
