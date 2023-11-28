#ifndef ray_h
#define ray_h
#include <cmath>
#include "vector3.h"

struct ray {
	vector3 origin;
	vector3 direction;

	ray() { }
	ray(vector3 _origin, vector3 _direction) : origin(_origin), direction(_direction) { }

	vector3 at(double& distance) {
		return origin + direction * distance;
	}

	ray reflect(vector3& normal) {
		ray reflected = ray(origin, normal);
		return reflected;
	}
	ray reflect(vector3& normal, vector3& fuzz) {
		ray reflected = reflect(normal);
		reflected.direction = (reflected.direction + fuzz).unit();
		return reflected;
	}
};
inline ostream& operator <<(ostream& out, ray& r) {
	return out << "(" << r.origin << "," << r.direction << ")";
}
#endif
