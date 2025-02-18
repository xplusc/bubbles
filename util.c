#include "util.h"

int util_sign(int x)
{
	return (x > 0) - (x < 0);
}

double util_clamp(double x, double lower, double upper)
{
	if (x < lower) {
		return lower;
	} else if (x > upper) {
		return upper;
	} else {
		return x;
	}
}