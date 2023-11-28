#ifndef randomDistribution_h
#define randomDistribution_h
#include <climits>

class randomDistribution {
private:
	int val_m = seed;
public:
	int seed = 1;

	randomDistribution() { }
	randomDistribution(int _seed) : seed(_seed), val_m(_seed) { }

	int randInt() {
		val_m = val_m * 1408497475 + 8741751;
		return val_m;
	}
	int randUint() {
		return abs(randInt());
	}
	int randInt(int min, int max) {
		return randUint() % max + min;
	}
	double randDouble() {
		return double(randUint()) / INT_MAX;
	}
	double randDoubleO() {
		return double(rand()) / INT_MAX;
	}
	double randDouble(bool negative) {
		if (negative)
			return 1 - 2*(double(randUint()) / INT_MAX);
		return double(randUint()) / INT_MAX;
	}
	double randN() {
		return randDouble(true);
	}
};
#endif
