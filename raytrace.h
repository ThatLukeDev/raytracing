#include <cmath>

color traceColor(ray r) {
	// placeholder code
	vector3 rayAt1 = r.at(1);
	vector3 hit = vector3(-1,-1,-1);
	for (int i = 0; i < objectsLength; i++) {
		double intersectD = objects[i].intersectsAlong(r);
		if (intersectD > 0) {
			vector3 intersect = r.at(intersectD);
			vector3 normal = (intersect - objects[i].position).unit();
			return color(abs(normal.X), abs(normal.Y), abs(normal.Z));
		}
	}
	return color(0, 0, 0);
}
