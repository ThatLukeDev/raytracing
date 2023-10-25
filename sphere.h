#include <iostream>
#include <cmath>

struct sphere {
	vector3 position = vector3();
	double r = 0;

	sphere() {}

	sphere(vector3 v, double rIn) {
		position = v;
		r = rIn;
	}
	sphere(double x, double y, double z, double rIn) {
		position = vector3(x, y, z);
		r = rIn;
	}

	bool intersects(ray r) {
		return true;
	}
};
