#ifndef ray_h
#define ray_h
#include <cmath>
#include "vector3.h"

struct ray {
	vector3 origin;
	vector3 direction;

	ray() { }
	ray(vector3 _origin, vector3 _direction) { origin = _origin; direction = _direction; }

	vector3 at(double distance) {
		return origin + direction * distance;
	}
};
inline ostream& operator <<(ostream& out, ray r) {
	return out << "(" << r.origin << "," << r.direction << ")";
}
#endif
