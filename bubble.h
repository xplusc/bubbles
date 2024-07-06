#ifndef BUBBLE_H
#define BUBBLE_H

#include <SDL.h>

struct bubble_sprite {
	double x;
	double y;
	double size;
	double period;    // ms
	double pulsiness; // as a percentage of size
	SDL_Rect src_rect;
	SDL_Texture *tex;
};
typedef struct bubble_sprite BubbleSprite;

#endif // BUBBLE_H