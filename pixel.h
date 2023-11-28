#ifndef pixel_h
#define pixel_h
#include <iostream>
#include <cmath>

using namespace std;

struct pixel {
	int R = 0;
	int G = 0;
	int B = 0;

	pixel() {}
	pixel(double& _R, double& _G, double& _B) : R(int(_R * 255)), G(int(_G * 255)), B(int(_B * 255)) { }
	pixel(double&& _R, double&& _G, double&& _B) : R(int(_R * 255)), G(int(_G * 255)), B(int(_B * 255)) { }
	pixel(int& _R, int& _G, int& _B) : R(_R), G(_G), B(_B) { }
	pixel(int&& _R, int&& _G, int&& _B) : R(_R), G(_G), B(_B) { }

	char* toByte3() {
		static char pixel[3];
		pixel[0] = (char)R;
		pixel[1] = (char)G;
		pixel[2] = (char)B;
		return pixel;
	}
	string toString() {
		return to_string(R) + " " + to_string(G) + " " + to_string(B) + "\n";
	}

	double brightness() {
		return sqrt(R*R + G*G + B*B);
	}
	pixel random() {
		randomDistribution rnd = randomDistribution(time(0));
		return pixel(rnd.randN(), rnd.randN(), rnd.randN());
	}

	pixel operator +(const pixel& v) { return pixel(R + v.R, G + v.G, B + v.B); }
	pixel operator -(const pixel& v) { return pixel(R - v.R, G - v.G, B - v.B); }
	pixel operator *(const pixel& v) { return pixel(R * v.R, G * v.G, B * v.B); }
	pixel operator /(const pixel& v) { return pixel(R / v.R, G / v.G, B / v.B); }
	pixel operator +(double& a) { return pixel(R + a, G + a, B + a); }
	pixel operator -(double& a) { return pixel(R - a, G - a, B - a); }
	pixel operator *(double& a) { return pixel(R * a, G * a, B * a); }
	pixel operator /(double& a) { return pixel(R / a, G / a, B / a); }
	void operator =(const pixel& v) { memcpy(this, &v, sizeof(pixel)); }
};
inline ostream& operator <<(ostream& out, pixel p) {
	return out << "(" << p.R << "," << p.G << "," << p.B << ")";
}

using color = pixel;
#endif
