#ifndef raytrace_h
#define raytrace_h
#include <cmath>
#include "ray.h"
#include "pixel.h"
#include "vector3.h"

color traceColor(ray& r, int bounces, int maxBounces, environmentC environment, double falloff, randomDistribution& rnd, object* ignore) {
	if (bounces > maxBounces)
		return color(0, 0, 0);

	double objDis = 2147483647;
	shared_ptr<object> obj = nullptr;
	for (int i = 0; i < objectsLength; i++) {
		double intersectD = objects[i]->intersectsAlong(r);
		if (intersectD > 0.0 && &(*objects[i]) != ignore) {
			if (intersectD < objDis) {
				objDis = intersectD;
				obj = objects[i];
			}
		}
	}

	if (obj == nullptr)
		return environment.getPixel(r);
	if (objDis < 0.01)
		return color(0, 0, 0);

	vector3 intersect = r.at(objDis);
	vector3 normal = obj->normalAt(intersect);
	vector3 randVector = vector3(rnd.randN(), rnd.randN(), rnd.randN()).unit();
	ray bounce = ray(intersect, r.direction);
	object* nextIgnore = nullptr;
	if (rnd.randDouble() < obj->texture.transparency) { bounce = bounce.refract(normal, obj->texture.ior); nextIgnore = &(*obj); }
	else { bounce = bounce.reflect(normal); }
	bounce = bounce.fuzz(randVector, 1 - obj->texture.fuzz);

	color bounceOutput = traceColor(bounce, bounces + 1, maxBounces, environment, falloff, rnd, nextIgnore);
	color output = obj->texture.getPixel(bounceOutput);

	return output;
}
color traceColor(ray& r, int bounces, int maxBounces, environmentC environment, double falloff, randomDistribution& rnd) {
	return traceColor(r, bounces, maxBounces, environment, falloff, rnd, nullptr);
}

color traceColor(ray& r, int maxBounces, environmentC environment, double falloff, randomDistribution& rnd) {
	return traceColor(r, 0, maxBounces, environment, falloff, rnd);
}

color traceColor(ray& r, int samples, double maxD, int maxBounces, environmentC environment, double falloff, randomDistribution& rnd) {
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
