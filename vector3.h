#include <iostream>
#include <cmath>

using namespace std;

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
		X = v.X;
		Y = v.Y;
		Z = v.Z;
                return v;
        }
};
inline vector3 operator +(vector3& a, vector3& v) {
        return vector3(a.X + v.X, a.Y + v.Y, a.Z + v.Z);
}
inline vector3 operator -(vector3& a, vector3& v) {
        return vector3(a.X - v.X, a.Y - v.Y, a.Z - v.Z);
}
inline vector3 operator *(vector3& a, vector3& v) {
        return vector3(a.X * v.X, a.Y * v.Y, a.Z * v.Z);
}
inline vector3 operator /(vector3& a, vector3& v) {
        return vector3(a.X / v.X, a.Y / v.Y, a.Z / v.Z);
}
inline vector3 operator +(vector3& v, double a) {
        return vector3(v.X + a, v.Y + a, v.Z + a);
}
inline vector3 operator -(vector3& v, double a) {
        return vector3(v.X - a, v.Y - a, v.Z - a);
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
