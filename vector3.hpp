#ifndef vector3_h
#define vector3_h
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

struct vector3 {
	double X = 0;
	double Y = 0;
	double Z = 0;

	vector3() { }
	template <typename T>
	vector3(T _X, T _Y, T _Z) : X(double(_X)), Y(double(_Y)), Z(double(_Z)) { }

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
	double dot(vector3 v) {
		return X * v.X + Y * v.Y + Z * v.Z;
	}
	vector3 random() {
		randomDistribution rnd = randomDistribution(time(0));
		return vector3(rnd.randN(), rnd.randN(), rnd.randN());
	}
	vector3 operator+(const vector3 v) {
		return vector3(X + v.X, Y + v.Y, Z + v.Z);
	}
	vector3 operator-(const vector3 v) {
		return vector3(X - v.X, Y - v.Y, Z - v.Z);
	}
	vector3 operator*(const vector3 v) {
		return vector3(X * v.X, Y * v.Y, Z * v.Z);
	}
	vector3 operator/(const vector3 v) {
		return vector3(X / v.X, Y / v.Y, Z / v.Z);
	}
	template <typename T>
	vector3 operator+(T a) {
		return vector3(X + a, Y + a, Z + a);
	}
	template <typename T>
	vector3 operator-(T a) {
		return vector3(X - a, Y - a, Z - a);
	}
	template <typename T>
	vector3 operator*(T a) {
		return vector3(X * a, Y * a, Z * a);
	}
	template <typename T>
	vector3 operator/(T a) {
		return vector3(X / a, Y / a, Z / a);
	}
	template <typename T>
	void operator=(T x) {
		X = double(x);
		Y = double(x);
		Z = double(x);
	}
	void operator=(const vector3& v) {
		memcpy(this, &v, sizeof(*this));
	}
};
double dot(vector3 a, vector3 v) {
	return a.X * v.X + a.Y * v.Y + a.Z * v.Z;
}
inline ostream& operator<<(ostream& out, vector3 v) {
	return out << "(" << v.X << "," << v.Y << "," << v.Z << ")";
}
#endif
