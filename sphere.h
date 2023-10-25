#include <iostream>
#include <cmath>

struct sphere {
	double x = 0;
	double y = 0;
	double z = 0;
	double r = 0;

	sphere() {}

	sphere(double xIn, double yIn, double zIn, double rIn) {
		x = xIn;
		y = yIn;
		z = zIn;
		r = rIn;
	}
};
