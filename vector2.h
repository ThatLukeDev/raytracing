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
	vector2(int& _X, int& _Y) : X(double(_X)), Y(double(_Y)) { }
	vector2(double& _X, double& _Y) : X(_X), Y(_Y) { }
	vector2(int&& _X, int&& _Y) : X(double(_X)), Y(double(_Y)) { }
	vector2(double&& _X, double&& _Y) : X(_X), Y(_Y) { }

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
	vector2 operator +(const vector2& v) {
		return vector2(X + v.X, Y + v.Y);
	}
	vector2 operator -(const vector2& v) {
		return vector2(X - v.X, Y - v.Y);
	}
	vector2 operator *(const vector2& v) {
		return vector2(X * v.X, Y * v.Y);
	}
	vector2 operator /(const vector2& v) {
		return vector2(X / v.X, Y / v.Y);
	}
	inline vector2 operator +(double& a) {
		return vector2(X + a, Y + a);
	}
	inline vector2 operator -(double& a) {
		return vector2(X - a, Y - a);
	}
	inline vector2 operator *(double& a) {
		return vector2(X * a, Y * a);
	}
	inline vector2 operator /(double& a) {
		return vector2(X / a, Y / a);
	}
	void operator =(const vector2& v) {
		memcpy(this, &v, sizeof(vector2));
	}
};      
double dot(vector2& a, vector2& v) {
	return a.X * v.X + a.Y * v.Y;
}
inline ostream& operator <<(ostream& out, vector2 v) {
	return out << "(" << v.X << "," << v.Y << ")";
}
#endif
