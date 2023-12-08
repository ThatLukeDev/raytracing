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
	template <typename T>
	pixel(T _R, T _G, T _B) : R(int(_R * 255)), G(int(_G * 255)), B(int(_B * 255)) { }
	pixel(int _R, int _G, int _B) : R(_R), G(_G), B(_B) { }

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
	pixel clamp(pixel min, pixel max) {
		if (R < min.R) R = min.R;
		if (R > max.R) R = max.R;
		if (G < min.G) G = min.G;
		if (G > max.G) G = max.G;
		if (B < min.B) B = min.B;
		if (B > max.B) B = max.B;
		return *this;
	}
	pixel clamp(int min, int max) {
		if (R < min) R = min;
		if (R > max) R = max;
		if (G < min) G = min;
		if (G > max) G = max;
		if (B < min) B = min;
		if (B > max) B = max;
		return *this;
	}
	pixel clamp() {
		return clamp(0, 255);
	}

	pixel operator+(pixel v) { return pixel(int(R + v.R), int(G + v.G), int(B + v.B)); }
	pixel operator-(pixel v) { return pixel(int(R - v.R), int(G - v.G), int(B - v.B)); }
	pixel operator*(pixel v) { return pixel(int(R * v.R), int(G * v.G), int(B * v.B)); }
	pixel operator/(pixel v) { return pixel(int(R / v.R), int(G / v.G), int(B / v.B)); }
	template <typename T>
	pixel operator+(T a) { return pixel(int(R + a), int(G + a), int(B + a)); }
	template <typename T>
	pixel operator-(T a) { return pixel(int(R - a), int(G - a), int(B - a)); }
	template <typename T>
	pixel operator*(T a) { return pixel(int(R * a), int(G * a), int(B * a)); }
	template <typename T>
	pixel operator/(T a) { return pixel(int(R / a), int(G / a), int(B / a)); }

	void operator+=(pixel v) { R += v.R; G += v.G; B += v.B; }
	void operator-=(pixel v) { R -= v.R; G -= v.G; B -= v.B; }
	void operator*=(pixel v) { R *= v.R; G *= v.G; B *= v.B; }
	void operator/=(pixel v) { R /= v.R; G /= v.G; B /= v.B; }
	template <typename T>
	void operator+=(T a) { R += a; G += a; B += a; }
	template <typename T>
	void operator-=(T a) { R -= a; G -= a; B -= a; }
	template <typename T>
	void operator*=(T a) { R *= a; G *= a; B *= a; }
	template <typename T>
	void operator/=(T a) { R /= a; G /= a; B /= a; }

	void operator=(pixel& v) { memcpy(this, &v, sizeof(*this)); }
};
inline ostream& operator<<(ostream& out, pixel p) {
	return out << "(" << p.R << "," << p.G << "," << p.B << ")";
}

using color = pixel;
#endif
