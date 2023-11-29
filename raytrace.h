#ifndef raytrace_h
#define raytrace_h
#include <cmath>
#include "ray.h"
#include "pixel.h"
#include "vector3.h"

color traceColor(ray& r, int bounces, int maxBounces, color environment, double falloff, randomDistribution& rnd) {
	if (bounces > maxBounces)
		return environment;
	double intersectDsmallest = 2147483647;
	sphere* objectAtSmallest = nullptr;
	for (int i = 0; i < objectsLength; i++) {
		double intersectD = objects[i].intersectsAlong(r);
		if (intersectD > 0.01) {
			if (intersectD < intersectDsmallest) {
				intersectDsmallest = intersectD;
				objectAtSmallest = &objects[i];
			}
		}
	}
	if (objectAtSmallest != nullptr) {
		color output = color();

		vector3 intersect = r.at(intersectDsmallest);
		vector3 normal = (intersect - objectAtSmallest->position).unit();
		vector3 randVector = vector3(rnd.randN(), rnd.randN(), rnd.randN()).unit();
		ray bounce = ray(intersect, r.direction).reflect(normal, randVector, 1 - objectAtSmallest->reflectance);

		output = objectAtSmallest->shade;
		double multiplier = objectAtSmallest->emission;
		if (falloff > 0.01) {
			multiplier /= (intersectDsmallest*intersectDsmallest * falloff);
		}
		else {
			multiplier *= 2;
		}
		if (multiplier < 0.5) multiplier = 0.5;
		output.R = output.R * multiplier;
		output.G = output.G * multiplier;
		output.B = output.B * multiplier;
		color bounceOutput = traceColor(bounce, bounces + 1, maxBounces, environment, falloff, rnd);
		output.R *= (bounceOutput.R / 255.999) + 1.0;
		output.G *= (bounceOutput.G / 255.999) + 1.0;
		output.B *= (bounceOutput.B / 255.999) + 1.0;

		return output;
	}
	return environment;
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
#endif
