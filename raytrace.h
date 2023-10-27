#include <cmath>

color traceColor(ray r) {
	vector3 rayAt1 = r.at(1);
	vector3 hit = vector3(-1,-1,-1);
	double intersectDsmallest = pow(2,32);
	sphere* objectAtSmallest = nullptr;
	for (int i = 0; i < objectsLength; i++) {
		double intersectD = objects[i].intersectsAlong(r);
		if (intersectD > 0 && intersectD < intersectDsmallest) {
			intersectDsmallest = intersectD;
			objectAtSmallest = &objects[i];
		}
	}
	if (intersectDsmallest != pow(2,32)) {
		vector3 intersect = r.at(intersectDsmallest);
		vector3 normal = (intersect - objectAtSmallest->position).unit();
		return color(abs(normal.X), abs(normal.Y), abs(normal.Z));
	}
	return color(0, 0, 0);
}
