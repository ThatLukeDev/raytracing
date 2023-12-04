#ifndef raytrace_h
#define raytrace_h
#include <cmath>
#include "ray.h"
#include "pixel.h"
#include "vector3.h"

color traceColor(ray& r, int bounces, int maxBounces, color environment, double falloff, randomDistribution& rnd) {
	if (bounces > maxBounces)
		return color(0, 0, 0);

	double intersectDsmallest = 2147483647;
	sphere* closestObject = nullptr;
	for (int i = 0; i < objectsLength; i++) {
		double intersectD = objects[i].intersectsAlong(r);
		if (intersectD > 0.0) {
			if (intersectD < intersectDsmallest) {
				intersectDsmallest = intersectD;
				closestObject = &objects[i];
			}
		}
	}

	if (closestObject == nullptr)
		return environment;
	if (intersectDsmallest < 0.01)
		return color(0, 0, 0);

	color output = color();

	vector3 intersect = r.at(intersectDsmallest);
	vector3 normal = (intersect - closestObject->position).unit();
	vector3 randVector = vector3(rnd.randN(), rnd.randN(), rnd.randN()).unit();
	ray bounce = ray(intersect, r.direction).reflect(normal, randVector, 1 - closestObject->reflectance);

	color bounceOutput = traceColor(bounce, bounces + 1, maxBounces, environment, falloff, rnd);
	double refl = closestObject->reflectance;
	double inverserefl = 1.0 - closestObject->reflectance;
	output = closestObject->shade * closestObject->emission * inverserefl + bounceOutput * refl;
	output.R *= (bounceOutput.R * inverserefl / 255.999) + 1.0;
	output.G *= (bounceOutput.G * inverserefl / 255.999) + 1.0;
	output.B *= (bounceOutput.B * inverserefl / 255.999) + 1.0;

	return output;
}

color traceColor(ray& r, int maxBounces, color environment, double falloff, randomDistribution& rnd) {
	return traceColor(r, 0, maxBounces, environment, falloff, rnd);
}

color traceColor(ray& r, int samples, double maxD, int maxBounces, color environment, double falloff, randomDistribution& rnd) {
	color output = color();
	for (int i = 0; i < samples; i++) {
		ray sampleRay = r;
		sampleRay.direction = (r.direction + vector3(rnd.randN() * maxD, rnd.randN() * maxD, rnd.randN() * maxD)).unit();
		color sample = traceColor(sampleRay, maxBounces, environment, falloff, rnd);
		output = output + sample;
	}
	output.R /= samples;
	output.G /= samples;
	output.B /= samples;
	if (output.R > 255) output.R = 255;
	if (output.G > 255) output.G = 255;
	if (output.B > 255) output.B = 255;
	return output;
}
#endif
