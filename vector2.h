#include <iostream>
#include <cmath>

using namespace std;

struct vector2 {
        double X = 0;
        double Y = 0;
        vector2() {} 
        vector2(int a, int b) {
                X = double(a);
                Y = double(b);
        }
        vector2(double a, double b) {
                X = a;  
                Y = b;
        }
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
        vector2 operator =(const vector2& v) {
		X = v.X;
		Y = v.Y;
                return v;
        }
	double dot() {
		return a.X * v.X + a.Y * v.Y;
	}
};      
inline vector2 operator +(vector2& a, vector2& v) {
        return vector2(a.X + v.X, a.Y + v.Y);
}
inline vector2 operator -(vector2& a, vector2& v) {
        return vector2(a.X - v.X, a.Y - v.Y);
}
inline vector2 operator *(vector2& a, vector2& v) {
        return vector2(a.X * v.X, a.Y * v.Y);
}
inline vector2 operator /(vector2& a, vector2& v) {
        return vector2(a.X / v.X, a.Y / v.Y);
}
inline vector2 operator +(vector2& v, double a) {
        return vector2(v.X + a, v.Y + a);
}
inline vector2 operator -(vector2& v, double a) {
        return vector2(v.X - a, v.Y - a);
}
inline vector2 operator *(vector2& v, double a) {
        return vector2(v.X * a, v.Y * a);
}
inline vector2 operator /(vector2& v, double a) {
        return vector2(v.X / a, v.Y / a);
}
inline ostream& operator <<(ostream& out, vector2 v) {
        return out << "(" << v.X << "," << v.Y << ")";
}
