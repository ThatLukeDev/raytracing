#ifndef raytrace_h
#define raytrace_h
#include <cmath>
#include "ray.h"
#include "pixel.h"
#include "vector3.h"

color traceColor(ray& r, int bounces, int maxBounces, color environment, double falloff, randomDistribution& rnd) {
	if (bounces > maxBounces)
		return color(0, 0, 0);

	double closestRay = 2147483647;
	shared_ptr<object> closestObject = nullptr;
	for (int i = 0; i < objectsLength; i++) {
		double intersectD = objects[i]->intersectsAlong(r);
		if (intersectD > 0.0) {
			if (intersectD < closestRay) {
				closestRay = intersectD;
				closestObject = objects[i];
			}
		}
	}

	if (closestObject == nullptr)
		return environment;
	if (closestRay < 0.01)
		return color(0, 0, 0);

	vector3 intersect = r.at(closestRay);
	vector3 normal = closestObject->normalAt(intersect);
	vector3 randVector = vector3(rnd.randN(), rnd.randN(), rnd.randN()).unit();
	ray bounce = ray(intersect, r.direction).reflect(normal, randVector, 1 - closestObject->texture.fuzz);

	color bounceOutput = traceColor(bounce, bounces + 1, maxBounces, environment, falloff, rnd);
	color output = closestObject->texture.getPixel(bounceOutput);

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
		output += sample;
	}
	output /= samples;
	output.clamp();
	return output;
}
#endif
