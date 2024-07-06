#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#include "game.h"

int main(int argc, char *argv[])
{	
	// initialize
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return 0;
	}
	printf("SDL successfully initialized\n");
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
		return 0;
	}
	printf("SDL_image successfully initialized\n");
	
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	
	// window
	SDL_Window *wind = SDL_CreateWindow(
		"Bubbles",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, 0);
	if (!wind) {
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}
	
	// renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *rend = SDL_CreateRenderer(wind, -1, render_flags);
	if (!rend) {
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(wind);
		SDL_Quit();
		return 0;
	}
	
	gameRun(wind, rend);
	
	// release resources
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(wind);
	SDL_Quit();
	return 0;
}
