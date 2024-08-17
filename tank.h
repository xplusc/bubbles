/**
 * The tank struct. Stores all data required to position, rotate,
 * and display a formation of BubbleSprites that makes up a
 * bubble tank.
 */

#ifndef TANK_H
#define TANK_H

#include "bubble.h"

struct tank {
	double x;	// units pending
	double y;	// units pending
	double rot; // rotation angle in radians, positive is clockwise, 0 is the x-axis
	size_t bubbles_size;
	BubbleSprite *bubbles;
};
typedef struct tank Tank;

#endif // TANK_H