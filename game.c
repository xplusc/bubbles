#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_image.h>

#include "bubble.h"

const Uint64 MS_PER_UPDATE = 16;
const size_t BUBBLES_SIZE = 25000;

int gameInitialize(SDL_Renderer *rend, SDL_Texture **tex_bubble, BubbleSprite *bubbles, const size_t num_bubbles)
{
	// load assets
	*tex_bubble = IMG_LoadTexture(rend, "bubble.png");
	if (*tex_bubble == NULL) {
		fprintf(stderr, "Error creating texture: %s\n", IMG_GetError());
		return -1;
	}
	
	for (size_t i = 0; i < num_bubbles; ++i) {
		BubbleSprite bs = {
			(double) (rand() % 640),
			(double) (rand() % 480),
			(double) (rand() % 15) + 35.0,
			(double) (rand() % 250) + 625.0,
			(double) (rand() % 10) / 100.0 + 0.1,
			{0},
			*tex_bubble
		};
		//SDL_Rect r = {640 / 2 - 50 / 2 + 60 * ((int) i - 5), 480 / 2 - 50 / 2, 50, 50};
		bubbles[i] = bs;
	}
	
	return 0;
}

void gameUpdate(Uint64 current_time, BubbleSprite *bubbles, SDL_Rect *rects, const size_t num_bubbles)
{
	for (size_t i = 0; i < num_bubbles; ++i) {
		BubbleSprite bs = bubbles[i];
		unsigned long total_complete_periods = (unsigned long) ((double) current_time / bs.period); // rounding down on purpose with the cast
		double phase = ((double) current_time - ((double) total_complete_periods * bs.period)) / bs.period;
		double scale_factor = 1.0 + bs.pulsiness * sin(2 * M_PI * phase);
		double new_size = bs.size * scale_factor;
		SDL_Rect r = {(int) (bs.x - new_size / 2), (int) (bs.y - new_size / 2), (int) new_size, (int) new_size};
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
	BubbleSprite bubbles[BUBBLES_SIZE];
	SDL_Rect rects[BUBBLES_SIZE];
	
	SDL_Texture *tex_bubble = 0;
	if (gameInitialize(rend, &tex_bubble, bubbles, BUBBLES_SIZE)) // returns true on error
		return -1;
	
	int game_running = 1;
	Uint64 simulation_time = SDL_GetTicks64();
	while (game_running) {
		Uint64 current_time = SDL_GetTicks64();
		
		while (simulation_time < current_time) {
			simulation_time += MS_PER_UPDATE;
			gameUpdate(simulation_time, bubbles, rects, BUBBLES_SIZE);
			SDL_Event event;
			// input events
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT: game_running = 0; break;
					default: break;
				}
			}
		}
		
		gameRender(wind, rend, tex_bubble, rects, BUBBLES_SIZE);
	}
	
	gameDestroy(tex_bubble);
	return 0;
}