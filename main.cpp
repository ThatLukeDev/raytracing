#include <iostream>
#include <fstream>

#define HEIGHT 1080
#define WIDTH 1920

using namespace std;

void logProgress(int num, int denom) {
		double progress = double(num) / (denom - 1); 
		char progress50 = char(progress * 50);
		clog << "\r[";
		for (int i = 0; i < 50; i++) {
			if (i < progress50) {
				clog << "#";
			}
			else {
				clog << " ";
			}
		}
		clog << "] ";
		clog << int(progress * 100) << "\% complete (" << num << "/" << denom << ")";
}

struct pixel {
	int R = 0;
	int G = 0;
	int B = 0;
	pixel fromDouble3(double dR, double dG, double dB) {
		R = int(dR * 255.999);
		G = int(dG * 255.999);
		B = int(dB * 255.999);
		return *this;
	}
	string toString() {
		return to_string(R) + " " + to_string(G) + " " + to_string(B) + "\n";
	}
};

int main() {
	cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

	for (int j = 0; j < HEIGHT; j++) {
		logProgress(j + 1, HEIGHT);

		for (int i = 0; i < WIDTH; i++) {
			double r = 1 - (double(i) / (WIDTH - 1));
			double g = 1 - r;
			double b = double(j) / (HEIGHT - 1);

			cout << (new pixel)->fromDouble3(r, g, b).toString();
			//cout << int(r * 255.999) << " " << int(g * 255.999) << " " << int(b * 255.999) << "\n";
		}
	}

	clog << endl;
	return 0;
}
