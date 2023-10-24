#include <cmath>

struct ray {
        vector3 origin = vector3();
        vector3 direction = vector3();

        ray() {}
        ray(vector3 originIn, vector3 directionIn) {
                origin = originIn;
                direction = directionIn.unit();
        }
        vector3 at(double distance) {
                return origin + direction * distance;
                return origin + direction * distance;
        }
        color traceColor() {
		// placeholder code
		vector3 rayAt1 = at(1);
                return color(abs(rayAt1.X), abs(rayAt1.Y), abs(rayAt1.Z));
        }
};
inline ostream& operator <<(ostream& out, ray r) {
        return out << "(" << r.origin << "," << r.direction << ")";
}
