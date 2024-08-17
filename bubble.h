/**
 * The BubbleSprite struct. Stores all data required to position
 * animate and display the bubbles that make up the bubble tanks.
 */

#ifndef BUBBLE_H
#define BUBBLE_H

#include <SDL.h>

struct bubble_sprite {
	double x;		  // units pending
	double y;		  // units pending
	double size;	  // units pending
	double period;    // ms
	double pulsiness; // as a proportion of size
	SDL_Rect src_rect;
	SDL_Texture *tex;
};
typedef struct bubble_sprite BubbleSprite;

#endif // BUBBLE_H