#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstring>
#include <vector>
#include <mutex>

#include "threading.h"
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
	const int width = 192;
	const int height = 108;
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
	int samples = 1024;
	double flux = 0.0005;
	const int maxBounces = 4;
	color environment = color(65,135,245);
	double lightFalloff = 0.0;
} viewport;

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
		if (progressMut.try_lock()) {
			progress(lines, image.height, startTime).logBar();
			progressMut.unlock();
		}

		for (int i = 0; i < image.width; i++) {
			vector3 viewportLocation = viewport.start + vector3(i * viewport.jump, -j * viewport.jump, 0.0);
			ray r = ray(camera.position, viewportLocation - camera.position);

			color outPixel = traceColor(
				r, viewport.samples, viewport.flux, viewport.maxBounces, viewport.environment, viewport.lightFalloff
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
