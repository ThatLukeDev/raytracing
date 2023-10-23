#include <cmath>

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
        color traceColor() {
                return color();
        }
};
inline ostream& operator <<(ostream& out, ray r) {
        return out << "(" << r.origin << "," << r.direction << ")";
}
