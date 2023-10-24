#include <iostream>
#include <cmath>
#include <fstream>

#include "pixel.h"
#include "vector3.h"
#include "vector2.h"
#include "ray.h"
#include "progressbar.h"

using namespace std;

static class imageC {public:
	const int width = 1920;
	const int height = 1080;
	double aspect = width / height;
	int depth = 8;
} image;

static class cameraC {public:
	double scale = 0.001;
	double width = image.width * scale;
	double height = image.height * scale;
	double aspect = width / height;
	double focal = 1;
	vector3 position = vector3(0, 0, 0);
} camera;
static class viewportC : cameraC {public:
	vector3 start = camera.position - vector3(camera.width / 2, camera.height / 2, camera.focal);
	vector3 end = start + vector3(camera.width, camera.height, 0.0);
	double jump = camera.scale;
} viewport;

int main() {
	cout << "P6 " << image.width << " " << image.height << " 255\n";

	clog << "Rendering image\n";
	for (int j = 0; j < image.height; j++) {
		progress(j + 1, image.height).logBar();

		for (int i = 0; i < image.width; i++) {
			vector3 viewportLocation = viewport.start + vector3(i * viewport.jump, j * viewport.jump, 0.0);
			ray r = ray(camera.position, viewportLocation - camera.position);

			char* raw = r.traceColor().toByte3();
			cout << *(raw) << *(raw + 1) << *(raw + 2);
		}
	}

	clog << endl;
	return 0;
}
