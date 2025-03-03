#include "bubble.h"

#include "util.h"

void bubble_Randomize(BubbleSprite *bs)
{
	bs->period    = util_RandRange(575.0 , 800.0 );
	bs->pulsiness = util_RandRange(  0.15,   0.22);
}