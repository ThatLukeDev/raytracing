#ifndef ray_h
#define ray_h
#include <cmath>
#include "vector3.hpp"

struct ray {
	vector3 origin;
	vector3 direction;

	ray() { }
	ray(vector3 _origin, vector3 _direction) : origin(_origin), direction(_direction) { }

	vector3 at(double distance) {
		return origin + direction * distance;
	}

	ray fuzz(vector3 fuzzVector, double _fuzz) {
		ray r = *this;
		r.direction = (r.direction + (fuzzVector * _fuzz)).unit();
		return r;
	}
	ray fuzz(vector3 _fuzz) {
		return fuzz(_fuzz, 1.0);
	}

	ray reflect(vector3 normal) {
		ray reflected = ray(origin, direction - (normal * (2 * dot(direction, normal))));
		return reflected;
	}

	ray refract(vector3 normal, double ior) {
		if (dot(normal, direction) < 0.0) { ior = 1.0 / ior; }

		double cos = dot(direction * -1, normal);
		if (cos < 1.0) cos = 1.0;
		double sin = sqrt(1.0 - cos*cos);
		if (ior * sin > 1.0) { return reflect(normal); }

		vector3 perpendicular =  (direction + normal * cos) * ior;
		vector3 parallel = normal * -sqrt(abs(1.0 - perpendicular.length_squared()));

		return ray(origin, (perpendicular + parallel).unit());
	}
};
inline ostream& operator <<(ostream& out, ray& r) {
	return out << "(" << r.origin << "," << r.direction << ")";
}
#endif
