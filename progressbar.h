#include <iostream>

using namespace std;

struct progress { 
	int num;
	int denom;
	double completion = 0;
	progress() {}

	progress(int numIn, int denomIn) {
		num = numIn;
		denom = denomIn;
		completion = double(num) / double(denom);
	}
	void log() {
		clog << int(completion * 100) << "\% completed" << endl;
	}
	void logBar() {
		char completion50 = char(completion * 50);
		clog << "\r[";
		for (int i = 0; i < 50; i++) {
			if (i < completion50) {
				clog << "#";
			}
			else {
				clog << " ";
			}
		}
		clog << "] ";
		clog << int(completion * 100) << "\% complete (" << num << "/" << denom << ")";
	}
};
