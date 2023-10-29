#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstring>
#include <vector>
#include <execution>
#include <algorithm>

#include "random.h"
#include "progressbar.h"
#include "pixel.h"
#include "vector3.h"
#include "vector2.h"
#include "ray.h"
#include "sphere.h"
#include "objects.cobj"
#include "raytrace.h"

using namespace std;

const double pi = 3.141592653589793238463;

static class imageC {public:
	const int width = 1920;
	const int height = 1080;
	double aspect = width / height;
	int depth = 8;
} image;

static class cameraC {public:
	vector3 position = vector3(0, 0, 0);
	double focal = 1;
	double fov = 90;
	double scale = ((position.X - (position.Z + focal)/tan((180 - fov) / (-360/pi))) * 2) / image.width;
	double width = image.width * scale;
	double height = image.height * scale;
	double aspect = width / height;
} camera;
static class viewportC : cameraC {public:
	vector3 start = camera.position + vector3(-camera.width / 2, camera.height / 2, camera.focal);
	vector3 end = start + vector3(camera.width, -camera.height, 0.0);
	double jump = camera.scale;
	int samples = 1;
	double flux = 0.0005;
	const int maxBounces = 4;
	color environment = color(0.125, 0.25, 0.5);
	double lightFalloff = 0.1;
} viewport;

int main() {
	clog << "RENDER SETTINGS:" << endl;
	clog << "RES: " << image.width << "x" << image.height << endl;
	clog << "FOV: " << atan(viewport.start.X/viewport.start.Z)*(-360.0/pi) << endl;
	clog << "FOCAL: " << camera.focal << endl;
	clog << "ASPECT: " << camera.aspect << endl;
	clog << "SAMPLES: " << viewport.samples << endl;
	clog << "SAMPLE FLUX: " << viewport.flux * 200 << "%" << endl;
	clog << endl;

	int startTime = time(0);
	int lines = 1;
	string header = "P6 " + to_string(image.width) + " " + to_string(image.height) + " 255\n";
	size_t headerSize = header.length();
	size_t outputSize = image.width * image.height * 3 + headerSize;
	char* output = (char*)malloc(outputSize);
	memcpy(output, (char*)header.c_str(), headerSize);

	clog << "Rendering image\n";
	vector<char> traceFor(image.height);
	fill(traceFor.begin(), traceFor.end(), 0);
	for_each(execution::par, traceFor.begin(), traceFor.end(), [&](char& v) {
		int j = int((size_t)&v - (size_t)&traceFor[0]);
	//tbb::parallel_for(0, image.height, [&](int j) {
		progress(lines, image.height, startTime).logBar();

		for (int i = 0; i < image.width; i++) {
			vector3 viewportLocation = viewport.start + vector3(i * viewport.jump, -j * viewport.jump, 0.0);
			ray r = ray(camera.position, viewportLocation - camera.position);

			char* raw = traceColor(
				r, viewport.samples, viewport.flux, viewport.maxBounces, viewport.environment, viewport.lightFalloff
			).toByte3();
			memcpy(output + headerSize + (j * image.width + i) * 3, raw, 3);
		}
		lines++;
	});
	clog << "\nWriting to output\n";
	for (size_t i = 0; i < outputSize; i++) {
		cout << *(output + i);
	}

	clog << endl;
	return 0;
}
