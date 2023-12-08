static class imageC {public:
	const int width = 192;
	const int height = 108;
	double aspect = width / height;
	int depth = 8;
} image;

static class cameraC {public:
	vector3 position = vector3(0, 0, 0);
	double focal = 1;
	double fov = 120;
	double scale = ((position.X - (position.Z + focal)/tan((180 - fov) / (-360/pi))) * 2) / image.width;
	double width = image.width * scale;
	double height = image.height * scale;
	double aspect = width / height;
} camera;

static class viewportC : cameraC {public:
	vector3 start = camera.position + vector3(-camera.width / 2, camera.height / 2, camera.focal);
	vector3 end = start + vector3(camera.width, -camera.height, 0.0);
	double jump = camera.scale;
	int samples = 1000;
	double flux = 0.001;
	const int maxBounces = 4;
	color environment = color(65,135,245);
	double lightFalloff = 0.0;
} viewport;

double colorClampMin = 16;
double colorClampMax = 240;

vector<shared_ptr<object>> objects {
	make_shared<sphere>(sphere(
		vector3(0,-1,3),1,
		color(200,200,200),0.5,0.9,0.5,0.0
	)),
        make_shared<sphere>(sphere(
		vector3(0,-102,3),100,
		color(35,140,35),0.5,0.0,0.0,0.0
	)),
        make_shared<sphere>(sphere(
		vector3(3,4,3),2,
		color(235,215,55),10.0,0.0,0.0,0.0
	)),
};
int objectsLength = objects.size();

void clampColor() {
	for (int i = 0; i < objectsLength; i++) {
		objects[i]->texture.shade.clamp(colorClampMin, colorClampMax);
	}
}
