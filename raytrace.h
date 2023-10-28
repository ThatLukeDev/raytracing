#include <cmath>

color traceColor(ray r, int bounces, int maxBounces, color environment, double falloff) {
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
	if (intersectDsmallest != pow(2,32) && bounces < maxBounces) {
		color output = color();
		vector3 intersect = r.at(intersectDsmallest);
		vector3 normal = (intersect - objectAtSmallest->position).unit();

		vector3 bounceD = vector3().random().unit();
		if (dot(bounceD, normal) < 0.0) bounceD = bounceD * -1;
		ray bounce = ray(intersect, bounceD);

		output = objectAtSmallest->shade;
		double multiplier = objectAtSmallest->emission/(intersectDsmallest*intersectDsmallest * falloff);
		if (multiplier < 0.5) multiplier = 0.5;
		output.R *= multiplier;
		output.G *= multiplier;
		output.B *= multiplier;
		color bounceOutput = traceColor(bounce, bounces + 1, maxBounces, environment, falloff);
		output.R *= (bounceOutput.R / 255.999) + 1.0;
		output.G *= (bounceOutput.G / 255.999) + 1.0;
		output.B *= (bounceOutput.B / 255.999) + 1.0;

		return output;
	}
	return environment;
}

color traceColor(ray r, int maxBounces, color environment, double falloff) {
	return traceColor(r, 0, maxBounces, environment, falloff);
}

color traceColor(ray r, int samples, double maxD, int maxBounces, color environment, double falloff) {
	color output = color();
	for (int i = 0; i < samples; i++) {
		ray sampleRay = r;
		sampleRay.direction = (r.direction + vector3(randN() * maxD, randN() * maxD, randN() * maxD)).unit();
		color sample = traceColor(sampleRay, maxBounces, environment, falloff);
		output.R += sample.R;
		output.G += sample.G;
		output.B += sample.B;
	}
	output.R /= samples;
	output.G /= samples;
	output.B /= samples;
	if (output.R > 255) output.R = 255;
	if (output.G > 255) output.G = 255;
	if (output.B > 255) output.B = 255;
	return output;
}
