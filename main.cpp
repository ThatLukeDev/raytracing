#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>

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
	double fov = 90;
	double scale = fov / image.width * 0.025;
	double width = image.width * scale;
	double height = image.height * scale;
	double aspect = width / height;
	double focal = 1;
	vector3 position = vector3(0, 0, 0);
} camera;
static class viewportC : cameraC {public:
	vector3 start = camera.position + vector3(-camera.width / 2, camera.height / 2, camera.focal);
	vector3 end = start + vector3(camera.width, -camera.height, 0.0);
	double jump = camera.scale;
} viewport;

int main() {
	clog << "RENDER SETTINGS:" << endl;
	clog << "RES: " << image.width << "x" << image.height << endl;
	clog << "FOV: " << abs(atan(viewport.start.Z/viewport.start.X)*(360.0/pi)) << endl;
	clog << "FOCAL: " << camera.focal << endl;
	clog << "ASPECT: " << camera.aspect << endl;
	clog << endl;

	int startTime = time(0);
	cout << "P6 " << image.width << " " << image.height << " 255\n";

	clog << "Rendering image\n";
	for (int j = 0; j < image.height; j++) {
		progress(j + 1, image.height, startTime).logBar();

		for (int i = 0; i < image.width; i++) {
			vector3 viewportLocation = viewport.start + vector3(i * viewport.jump, -j * viewport.jump, 0.0);
			ray r = ray(camera.position, viewportLocation - camera.position);

			char* raw = traceColor(r).toByte3();
			cout << *(raw) << *(raw + 1) << *(raw + 2);
		}
	}

	clog << endl;
	return 0;
}
