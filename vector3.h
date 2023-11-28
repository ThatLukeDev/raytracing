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
	vector3(int _X, int _Y, int _Z) : X(double(_X)), Y(double(_Y)), Z(double(_Z)) { }
	vector3(double _X, double _Y, double _Z) : X(_X), Y(_Y), Z(_Z) { }

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
	double dot(vector3& v) {
		return X * v.X + Y * v.Y + Z * v.Z;
	}
	vector3 random() {
		randomDistribution rnd = randomDistribution(time(0));
		return vector3(rnd.randN(), rnd.randN(), rnd.randN());
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
	vector3 operator +(double& a) {
		return vector3(X + a, Y + a, Z + a);
	}
	vector3 operator -(double& a) {
		return vector3(X - a, Y - a, Z - a);
	}
	vector3 operator *(double& a) {
		return vector3(X * a, Y * a, Z * a);
	}
	vector3 operator /(double& a) {
		return vector3(X / a, Y / a, Z / a);
	}
	void operator =(const vector3& v) {
		memcpy(this, &v, sizeof(vector3));
	}
};
double dot(vector3& a, vector3& v) {
	return a.X * v.X + a.Y * v.Y + a.Z * v.Z;
}
inline ostream& operator <<(ostream& out, vector3 v) {
	return out << "(" << v.X << "," << v.Y << "," << v.Z << ")";
}
#endif
