#include <cstdlib>
#include <ctime>

void randSeed() {
	srand(time(0));
}
int randInt(int min, int max) {
	return rand() % max + min;
}
double randDouble() {
	return double(rand()) / RAND_MAX;
}
double randDouble(bool negative) {
	if (!negative)
		return randDouble();
	return 1 - randDouble() * 2;
}
double randN() {
	return randDouble(true);
}
