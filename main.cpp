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
struct vector3 {
	double X = 0;
	double Y = 0;
	double Z = 0;
	vector3() {}
	vector3(int a, int b, int c) {
		X = double(a);
		Y = double(b);
		Z = double(c);
	}
	vector3(double a, double b, double c) {
		X = a;
		Y = b;
		Z = c;
	}
	double length_squared() {
		return X*X + Y*Y + Z*Z;
	}
	double length() {
		return sqrt(length_squared());
	}
	vector3 unit() {
		double len = length();
		X /= len;
		Y /= len;
		Z /= len;
		return *this;
	}
	vector3 operator +(const vector3& v) {
		return vector3(X + v.X, Y + v.Y, Z + v.Z);
	}
	vector3 operator -(const vector3& v) {
		return vector3(X - v.X, Y - v.Y, Z - v.Z);
	}
	vector3 operator *(const vector3& v) {
		return vector3(X * v.X, Y * v.Y, Z * v.Z);
	}
	vector3 operator /(const vector3& v) {
		return vector3(X / v.X, Y / v.Y, Z / v.Z);
	}
	vector3 operator =(const vector3& v) {
		return v;
	}
};
inline vector3 operator +(const vector3& a, vector3& v) {
	return vector3(a.X + v.X, a.Y + v.Y, a.Z + v.Z);
}
inline vector3 operator -(const vector3& a, vector3& v) {
	return vector3(a.X - v.X, a.Y - v.Y, a.Z - v.Z);
}
inline vector3 operator *(const vector3& a, vector3& v) {
	return vector3(a.X * v.X, a.Y * v.Y, a.Z * v.Z);
}
inline vector3 operator /(const vector3& a, vector3& v) {
	return vector3(a.X / v.X, a.Y / v.Y, a.Z / v.Z);
}
inline vector3 operator *(vector3& v, double a) {
	return vector3(v.X * a, v.Y * a, v.Z * a);
}
inline vector3 operator /(vector3& v, double a) {
	return vector3(v.X / a, v.Y / a, v.Z / a);
}
inline ostream& operator <<(ostream& out, vector3 v) {
	return out << "(" << v.X << "," << v.Y << "," << v.Z << ")";
}

struct pixel {
	int R = 0;
	int G = 0;
	int B = 0;

	pixel() {}
	pixel(double dR, double dG, double dB) {
		R = int(dR * 255.999);
		G = int(dG * 255.999);
		B = int(dB * 255.999);
	}
	pixel(int dR, int dG, int dB) {
		R = dR;
		G = dG;
		B = dB;
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

struct ray {
	vector3 origin = vector3();
	vector3 direction = vector3();

	ray() {}
	ray(vector3 originIn, vector3 directionIn) {
		origin = originIn;
		direction = directionIn;
	}
	vector3 at(double distance) {
		return origin + direction * distance;
		return origin + direction * distance;
	}
};

int main() {
	//return 0;
	//------------------------
	cout << "P6 " << WIDTH << " " << HEIGHT << " 255\n";

	clog << "Rendering image\n";
	for (int j = 0; j < HEIGHT; j++) {
		logProgress(j + 1, HEIGHT);

		for (int i = 0; i < WIDTH; i++) {
			double r = 1 - (double(i) / (WIDTH - 1));
			double g = 1 - r;
			double b = double(j) / (HEIGHT - 1);
			char* raw = pixel(r, g, b).toByte3();

			cout << *(raw) << *(raw + 1) << *(raw + 2);
		}
	}

	clog << endl;
	return 0;
}
