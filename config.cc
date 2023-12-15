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
	double lightFalloff = 0.0;
} viewport;
static class environmentC : viewportC {
public:
	color getPixel(ray r) {
		return color(1.0 - r.direction.Y, 1.0 - r.direction.Y, 1.0).clamp(color(128,128,192), color(255,255,255));
		// color(65,135,245);
	}
} environment;

double colorClampMin = 16;
double colorClampMax = 240;

vector<shared_ptr<object>> objects {
	make_shared<sphere>(sphere(
		vector3(0,0,3),2,
		color(200,200,200),0.5,1.0,0.0,1.0,1.5
	)),

	make_shared<sphere>(sphere(
		vector3(-3,-1,3),1,
		color(200,200,200),0.5,0.9,0.5,0.0,1.0
	)),
	make_shared<sphere>(sphere(
		vector3(0,-1,3),1,
		color(200,20,10),0.5,0.0,1.0,0.0,1.0
	)),
	make_shared<sphere>(sphere(
		vector3(3,-1,3),1,
		color(200,200,200),0.5,1.0,0.0,1.0,1.5
	)),
        make_shared<sphere>(sphere(
		vector3(3,4,3),2,
		color(235,215,55),10.0,0.0,1.0,0.0,1.0
	)),
        make_shared<sphere>(sphere(
		vector3(0,-1002,3),1000,
		color(35,140,35),0.5,0.0,1.0,0.0,1.0
	)),
};
int objectsLength = objects.size();

void clampColor() {
	for (int i = 0; i < objectsLength; i++) {
		objects[i]->texture.shade.clamp(colorClampMin, colorClampMax);
	}
}
