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

sphere objects[] = {
	sphere(
		vector3(-1,1,2),1,
		color(240,0,20),0.0
	),
        sphere(
		vector3(1,0,4),1,
		color(35,140,35),0.0
	),
        sphere(
		vector3(3,-2,4),1,
		color(0,70,170),0.0
	),
        sphere(
		vector3(-1,-1,4),1,
		color(255,255,255),5.0
	),
};
int objectsLength = sizeof(objects) / sizeof(objects[0]);
double colorClampMin = 16;
double colorClampMax = 240;
void clampColor() {
	for (int i = 0; i < objectsLength; i++) {
		if (objects[i].shade.R < colorClampMin) objects[i].shade.R = colorClampMin;
		if (objects[i].shade.R > colorClampMax) objects[i].shade.R = colorClampMax;
		if (objects[i].shade.G < colorClampMin) objects[i].shade.G = colorClampMin;
		if (objects[i].shade.G > colorClampMax) objects[i].shade.G = colorClampMax;
		if (objects[i].shade.B < colorClampMin) objects[i].shade.B = colorClampMin;
		if (objects[i].shade.B > colorClampMax) objects[i].shade.B = colorClampMax;
	}
}
