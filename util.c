#include "util.h"

#include <stdlib.h>

int util_Sign(int x)
{
	return (x > 0) - (x < 0);
}

double util_Clamp(double x, double lower, double upper)
{
	if (x < lower) {
		return lower;
	} else if (x > upper) {
		return upper;
	} else {
		return x;
	}
}

double util_RandRange(double lower, double upper)
{
	return lower + (upper - lower) * ((double) rand() / RAND_MAX);
}