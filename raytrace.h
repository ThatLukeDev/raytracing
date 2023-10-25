#include <cmath>

color traceColor(ray r) {
	// placeholder code
	vector3 rayAt1 = r.at(1);
	vector3 hit = vector3(-1,-1,-1);
	for (int i = 0; i < objectsLength; i++) {
		if (objects[i].intersects(r) ) {
			return color(1.0, 0.0, abs(rayAt1.Y));
		}
	}
	return color(0.0, 0.0, abs(rayAt1.Y));
}