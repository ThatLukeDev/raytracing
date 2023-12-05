#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstring>
#include <vector>
#include <mutex>
#include <memory>

using namespace std;
const double pi = 3.141592653589793238463;

#include "threading.h"
#include "random.h"
#include "progressbar.h"
#include "pixel.h"
#include "vector3.h"
#include "vector2.h"
#include "ray.h"
#include "object.h"
#include "sphere.h"
#include "config.cc"
#include "raytrace.h"

int main() {
	clog << "RENDER SETTINGS:" << endl;
	clog << "RES: " << image.width << "x" << image.height << endl;
	clog << "FOV: " << atan(viewport.start.X/viewport.start.Z)*(-360.0/pi) << endl;
	clog << "FOCAL: " << camera.focal << endl;
	clog << "ASPECT: " << camera.aspect << endl;
	clog << "SAMPLES: " << viewport.samples << endl;
	clog << "SAMPLE FLUX: " << viewport.flux * 200 << "%" << endl;
	clog << "CLAMP: " << colorClampMin << "-" << colorClampMax << endl;
	clog << endl;

	clampColor();

	mutex progressMut;
	int lines = 1;
	string header = "P6 " + to_string(image.width) + " " + to_string(image.height) + " 255\n";
	size_t headerSize = header.length();
	size_t outputSize = image.width * image.height * 3 + headerSize;
	char* output = (char*)malloc(outputSize);
	memcpy(output, (char*)header.c_str(), headerSize);
	int startTime = time(0);

	clog << "Rendering image\n";
	jobHandler jobs; 
	for (int j = 0; j < image.height; j++) jobs.addJob([&, j]() {
	//for (int j = 0; j < image.height; j++) {
		randomDistribution rnd(j);
		if (progressMut.try_lock()) {
			progress(lines, image.height, startTime).logBar();
			progressMut.unlock();
		}

		for (int i = 0; i < image.width; i++) {
			vector3 viewportLocation = viewport.start + vector3(i * viewport.jump, -j * viewport.jump, 0.0);
			ray r = ray(camera.position, viewportLocation - camera.position);

			color outPixel = traceColor(
				r, viewport.samples, viewport.flux, viewport.maxBounces, viewport.environment, viewport.lightFalloff, rnd
			);
			char* outByte3 = (char*)malloc(3);
			outByte3[0] = outPixel.R;
			outByte3[1] = outPixel.G;
			outByte3[2] = outPixel.B;
			memcpy(output + headerSize + (j * image.width + i) * 3, outByte3, 3);
		}
		lines++;
	});
	jobs.start();
	progress(image.height, image.height, startTime).logBar();
	clog << "\nWriting to output\n";
	ofstream outfile;
	outfile.open("out.ppm");
	outfile.write(output, outputSize);
	outfile.close();

	clog << endl;
	return 0;
}
