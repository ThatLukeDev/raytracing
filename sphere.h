#ifndef sphere_h
#define sphere_h
#include <iostream>
#include <cmath>
#include "vector3.h"
#include "pixel.h"
#include "ray.h"
#include "object.h"

struct sphere : object {
	double radius = 0;
	sphere() : object(vector3(), color(), 0.0, 0.0, 0.0) { }
	sphere(vector3 _position, double _radius) : object(_position, color(), 0.0, 0.0, 0.0), radius(_radius) { }
	sphere(vector3 _position, double _radius, color _shade) : object(_position, _shade, 0.0, 0.0, 0.0), radius(_radius) { }
	sphere(vector3 _position, double _radius, color _shade, double _emission, double _reflectance, double _transparency)
	: object(_position, _shade, _emission, _reflectance, _transparency), radius(_radius) { }

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
};
#endif
