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
	double X = 0;
	double Y = 0;
	double Z = 0;
	vec3 fromInt3(int a, int b, int c) {
		X = double(a);
		Y = double(b);
		Z = double(c);
		return *this;
	}
	vec3 fromDouble3(double a, double b, double c) {
		X = a;
		Y = b;
		Z = c;
		return *this;
	}
	double length_squared() {
		return X*X + Y*Y + Z*Z;
	}
	double length() {
		return sqrt(length_squared());
	}
	vec3 operator +(const vec3& v) {
		return fromDouble3(X + v.X, Y + v.Y, Z + v.Z);
	}
	vec3 operator -(const vec3& v) {
		return fromDouble3(X - v.X, Y - v.Y, Z - v.Z);
	}
	vec3 operator *(const vec3& v) {
		return fromDouble3(X * v.X, Y * v.Y, Z * v.Z);
	}
	vec3 operator /(const vec3& v) {
		return fromDouble3(X / v.X, Y / v.Y, Z / v.Z);
	}
	vec3 operator =(const vec3& v) {
		return v;
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
	char* toByte3() {
		static char pixel[3];
		pixel[0] = (char)uint8_t(R);
		pixel[1] = (char)uint8_t(G);
		pixel[2] = (char)uint8_t(B);
		return pixel;
	}
	string toString() {
		return to_string(R) + " " + to_string(G) + " " + to_string(B) + "\n";
	}
};

int main() {
	cout << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";

	clog << "Rendering image\n";
	for (int j = 0; j < HEIGHT; j++) {
		logProgress(j + 1, HEIGHT);

		for (int i = 0; i < WIDTH; i++) {
			double r = 1 - (double(i) / (WIDTH - 1));
			double g = 1 - r;
			double b = double(j) / (HEIGHT - 1);
			char* raw = (new pixel)->fromDouble3(r, g, b).toByte3();

			cout << *(raw) << *(raw + 1) << *(raw + 2);
		}
	}

	clog << endl;
	return 0;
}
