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
		color output = color();
		output = objectAtSmallest->shade;
		return output;
	}
	return color(0, 0, 0);
}
color traceColor(ray r, int samples, double maxD) {
	color output = color();
	for (int i = 0; i < samples; i++) {
		ray sampleRay = r;
		sampleRay.direction = (r.direction + vector3(randN() * maxD, randN() * maxD, randN() * maxD)).unit();
		color sample = traceColor(sampleRay);
		output.R += sample.R;
		output.G += sample.G;
		output.B += sample.B;
	}
	output.R /= samples;
	output.G /= samples;
	output.B /= samples;
	return output;
}
