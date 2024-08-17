/**
 * The tank struct. Stores all data required to position, rotate,
 * and display a formation of BubbleSprites that makes up a
 * bubble tank.
 */

#ifndef TANK_H
#define TANK_H

#include "input.h"
#include "bubble.h"

struct tank {
	double x;	// units pending
	double y;	// units pending
	double rot; // rotation angle in radians, positive is clockwise, 0 is the x-axis
	size_t bubbles_size;
	BubbleSprite *bubbles;
};
typedef struct tank Tank;

/**
 * Apply the current controls active in an input object to a tank.
 * This will control the tank's motion and rotation.
 */
void tank_ApplyControls(const Input*, Tank*);

#endif // TANK_H