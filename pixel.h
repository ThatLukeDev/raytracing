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
        pixel(double dR, double dG, double dB) {
                R = int(dR * 255.999);
                G = int(dG * 255.999);
                B = int(dB * 255.999);
        }
        pixel(int dR, int dG, int dB) {
                R = dR;
                G = dG;
                B = dB;
        }
        char* toByte3() {
                static char pixel[3];
                pixel[0] = (char)uint8_t(R);
                pixel[1] = (char)uint8_t(G);
                pixel[2] = (char)uint8_t(B);
                return pixel;
        }
        string toString() {
                return to_string(R) + " " + to_string(G) + " " + to_string(B) + "\n";
        }
};
inline ostream& operator <<(ostream& out, pixel p) {
        return out << "(" << p.R << "," << p.G << "," << p.B << ")";
}

using color = pixel;
#endif
