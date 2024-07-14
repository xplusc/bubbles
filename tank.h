#ifndef TANK_H
#define TANK_H

#include "bubble.h"

struct tank {
	double x;
	double y;
	double rot; // rotation angle in radians, positive is clockwise, 0 is the x-axis
	size_t bubbles_size;
	BubbleSprite *bubbles;
};
typedef struct tank Tank;

#endif // TANK_H