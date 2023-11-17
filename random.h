#ifndef randomDistribution_h
#define randomDistribution_h
#include <climits>
#define R_MAX 245

#include "crand.h"
class randomDistribution {public:
	int seed = 1;
	int counter = 344;
	const int MAX = INT_MAX;

	randomDistribution() { }
	randomDistribution(int _seed) { seed = _seed; _val = _seed; }

	int randInt() {
		_val = (_val * 1103515245 + 12345) % MAX;
		return _val;
	}
	int randUint() {
		return __random();
	}
	int randInt(int min, int max) {
		return randUint() % max + min;
	}
	double randDouble() {
		return double(randUint()) / MAX;
	}
	double randDoubleO() {
		return double(rand()) / MAX;
	}
	double randDouble(bool negative) {
		if (negative)
			return 1 - (double(randUint()) / MAX) * 2;
		return double(randUint()) / MAX;
	}
	double randN() {
		return randDouble(true);
	}
	void init() {
		r[0] = seed;
		for (int i=1; i<31; i++) {
			r[i] = (16807LL * r[i-1]) % 2147483647;
			if (r[i] < 0) {
				r[i] += 2147483647;
			}
		}
		for (int i=31; i<34; i++) {
			r[i] = r[i-31];
		}
		for (int i=34; i<344; i++) {
			r[i] = r[i-31] + r[i-3];
		}
	}
private:
	int _val = seed;
	int r[R_MAX];
};
#endif
