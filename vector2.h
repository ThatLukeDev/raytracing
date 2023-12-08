#ifndef vector2_h
#define vector2_h
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

struct vector2 {
	double X = 0;
	double Y = 0;

	vector2() { } 
	template <typename T>
	vector2(T _X, T _Y) : X(double(_X)), Y(double(_Y)) { }

	double length_squared() {
		return X*X + Y*Y;
	}
	double length() {
		return sqrt(length_squared());
	}
	vector2 unit() {
		double len = length();
		X /= len;
		Y /= len;
		return *this;
	}
	vector2 random() {
		randomDistribution rnd = randomDistribution(time(0));
		return vector2(rnd.randN(), rnd.randN());
	}
	vector2 operator+(vector2 v) {
		return vector2(X + v.X, Y + v.Y);
	}
	vector2 operator-(vector2 v) {
		return vector2(X - v.X, Y - v.Y);
	}
	vector2 operator*(vector2 v) {
		return vector2(X * v.X, Y * v.Y);
	}
	vector2 operator/(vector2 v) {
		return vector2(X / v.X, Y / v.Y);
	}
	template <typename T>
	vector2 operator+(T a) {
		return vector2(X + a, Y + a);
	}
	template <typename T>
	vector2 operator-(T a) {
		return vector2(X - a, Y - a);
	}
	template <typename T>
	vector2 operator*(T a) {
		return vector2(X * a, Y * a);
	}
	template <typename T>
	vector2 operator/(T a) {
		return vector2(X / a, Y / a);
	}
	template <typename T>
	void operator=(T _X) {
		X = _X;
		Y = _X;
	}
	void operator=(const vector2& v) {
		memcpy(this, &v, sizeof(vector2));
	}
};      
double dot(vector2 a, vector2 v) {
	return a.X * v.X + a.Y * v.Y;
}
inline ostream& operator<<(ostream& out, vector2 v) {
	return out << "(" << v.X << "," << v.Y << ")";
}
#endif
