#ifndef progressbar_h
#define progressbar_h
#include <iostream>
#include <ctime>

using namespace std;

struct progress { 
	int num;
	int denom;
	double completion = 0;
	int dtime = 0;
	progress() {}

	progress(int numIn, int denomIn) {
		num = numIn;
		denom = denomIn;
		completion = double(num) / double(denom);
	}
	progress(int numIn, int denomIn, int startT) {
		num = numIn;
		denom = denomIn;
		completion = double(num) / double(denom);
		dtime = time(0) - startT;
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
		if (dtime > 0) {
			int estimate = int(dtime / completion) + 1;
			clog << " (" << estimate - dtime << " seconds remaining)";
		}
	}
};
#endif
