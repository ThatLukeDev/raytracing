#include <iostream>
#include <fstream>

#define HEIGHT 256
#define WIDTH 256

using namespace std;

int main() {
	cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

	for (int j = 0; j < HEIGHT; j++) {
		clog << "\r" << int(double(j) / HEIGHT * 100) << "\% complete (" << j << "/" << HEIGHT << ")";
		for (int i = 0; i < WIDTH; i++) {
			double r = double(i) / (WIDTH - 1);
			double g = double(j) / (HEIGHT - 1);
			double b = 0.5 - r / 2;

			cout << int(r * 255.999) << " " << int(g * 255.999) << " " << int(b * 255.999) << "\n";
		}
	}

	return 0;
}
