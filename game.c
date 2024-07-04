#include "game.h"

#include <stdio.h>
#include <math.h>
#include <SDL_image.h>

const Uint64 MS_PER_UPDATE = 16;
const size_t RECTS_SIZE = 10;

int gameInitialize(SDL_Renderer *rend, SDL_Texture **tex_bubble, SDL_Rect *rects, const size_t num_rects)
{
	// load assets
	*tex_bubble = IMG_LoadTexture(rend, "bubble.png");
	if (*tex_bubble == NULL) {
		fprintf(stderr, "Error creating texture: %s\n", IMG_GetError());
		return -1;
	}
	
	for (size_t i = 0; i < num_rects; ++i) {
		SDL_Rect r = {640 / 2 - 50 / 2 + 60 * ((int) i - 5), 480 / 2 - 50 / 2, 50, 50};
		rects[i] = r;
	}
	
	return 0;
}

void gameUpdate(Uint64 current_time, SDL_Rect *rects, const size_t num_rects)
{
	double period = 750.0; // ms
	double amplitude = 0.15;
	unsigned long total_complete_periods = (unsigned long) ((double) current_time / period);
	double phase = ((double) current_time - ((double) total_complete_periods * period)) / period;
	double scale_factor = 1.0 + amplitude * sin(2 * M_PI * phase);
	
	for (size_t i = 0; i < num_rects; ++i) {
		double size = 50.0 * scale_factor;
		SDL_Rect r = {640 / 2 - size / 2 + 60 * ((int) i - 5), 480 / 2 - size / 2, size, size};
		rects[i] = r;
	}
	
	return;
}

void gameRender(SDL_Window *wind, SDL_Renderer *rend, SDL_Texture *tex_bubble, const SDL_Rect *rects, const size_t num_rects)
{
	int wind_width;
	int wind_height;
	SDL_GetWindowSize(wind, &wind_width, &wind_height);
	
	// clear screen
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);
	
	// draw assets
	for (size_t i = 0; i < num_rects; ++i) {
		SDL_RenderCopy(rend, tex_bubble, NULL, &rects[i]);
	}
	
	// render on window
	SDL_RenderPresent(rend);
	return;
}

void gameDestroy(SDL_Texture *tex_bubble)
{
	SDL_DestroyTexture(tex_bubble);
	return;
}

int gameRun(SDL_Window *wind, SDL_Renderer *rend)
{
	SDL_Rect rects[RECTS_SIZE];
	
	SDL_Texture *tex_bubble = 0;
	if (gameInitialize(rend, &tex_bubble, rects, RECTS_SIZE)) // returns true on error
		return -1;
	
	int game_running = 1;
	Uint64 simulation_time = SDL_GetTicks64();
	while (game_running) {
		Uint64 current_time = SDL_GetTicks64();
		
		while (simulation_time < current_time) {
			simulation_time += MS_PER_UPDATE;
			gameUpdate(simulation_time, rects, RECTS_SIZE);
			SDL_Event event;
			// input events
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT: game_running = 0; break;
					default: break;
				}
			}
		}
		
		gameRender(wind, rend, tex_bubble, rects, RECTS_SIZE);
	}
	
	gameDestroy(tex_bubble);
	return 0;
}