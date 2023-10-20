#include <iostream>
#include <fstream>
#include <cmath>

#define HEIGHT 1080
#define WIDTH 1920

using namespace std;

void logProgress(int num, int denom) {
	double progress = double(num) / (denom - 1); 
	char progress50 = char(progress * 50);
	clog << "\r[";
	for (int i = 0; i < 50; i++) {
		if (i < progress50) {
			clog << "#";
		}
		else {
			clog << " ";
		}
	}
	clog << "] ";
	clog << int(progress * 100) << "\% complete (" << num << "/" << denom << ")";
}
struct vec3 {
	double v1 = 0;
	double v2 = 0;
	double v3 = 0;
	vec3 fromInt3(int a, int b, int c) {
		v1 = double(a);
		v2 = double(b);
		v3 = double(c);
		return *this;
	}
	vec3 fromDouble3(double a, double b, double c) {
		v1 = a;
		v2 = b;
		v3 = c;
		return *this;
	}
	double length_squared() {
		return v1*v1 + v2*v2 + v3*v3;
	}
	double length() {
		return sqrt(length_squared());
	}
};

struct pixel {
	int R = 0;
	int G = 0;
	int B = 0;

	pixel fromDouble3(double dR, double dG, double dB) {
		R = int(dR * 255.999);
		G = int(dG * 255.999);
		B = int(dB * 255.999);
		return *this;
	}
	pixel fromInt3(int dR, int dG, int dB) {
		R = dR;
		G = dG;
		B = dB;
		return *this;
	}
	string toString() {
		return to_string(R) + " " + to_string(G) + " " + to_string(B) + "\n";
	}
};

int main() {
	cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

	clog << "Rendering image\n";
	for (int j = 0; j < HEIGHT; j++) {
		logProgress(j + 1, HEIGHT);

		for (int i = 0; i < WIDTH; i++) {
			double r = 1 - (double(i) / (WIDTH - 1));
			double g = 1 - r;
			double b = double(j) / (HEIGHT - 1);

			cout << (new pixel)->fromDouble3(r, g, b).toString();
		}
	}

	clog << endl;
	return 0;
}
