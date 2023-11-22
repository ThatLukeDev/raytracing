#ifndef randomDistribution_h
#define randomDistribution_h
#include <climits>

class randomDistribution {public:
	int seed = 1;
	int counter = 344;
	const int MAX = INT_MAX;

	randomDistribution() { }
	randomDistribution(int _seed) { seed = _seed; _val = _seed; }

	int randInt() {
		_val = _val * 1408497475 + 8741751;
		return _val;
	}
	int randUint() {
		return abs(randInt());
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
			return 1 - 2*(double(randUint()) / MAX);
		return double(randUint()) / MAX;
	}
	double randN() {
		return randDouble(true);
	}
private:
	int _val = seed;
};
#endif
