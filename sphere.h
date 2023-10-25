#include <iostream>
#include <cmath>

struct sphere {
	vector3 position = vector3();
	double radius = 0;

	sphere() {}

	sphere(vector3 v, double r) {
		position = v;
		radius = r;
	}
	sphere(double x, double y, double z, double r) {
		position = vector3(x, y, z);
		radius = r;
	}

	double intersectsAlong(ray r) {
		vector3 SminusO = r.origin - position;
		double a = dot(r.direction, r.direction);
		double b = 2.0 * dot(r.direction, SminusO);
		double c = dot(SminusO, SminusO) - radius * radius;
		double underRoot = b*b - 4 * a * c;
		if (underRoot < 0.0) {
			return -1;
		}
		else if (underRoot == 0.0) {
			return (-b) / 2*a;
		}
		else {
			return (-b - 4*a*c) / 2*a;
		}
	}
	bool intersects(ray r) {
		if (intersectsAlong(r) != -1) {
			return true;
		}
		return false;
	}
};
