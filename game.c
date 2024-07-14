#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_image.h>

#include "bubble.h"
#include "tank.h"

const Uint64 MS_PER_UPDATE = 16;
const size_t BUBBLES_SIZE = 25;

void gameUpdate(Uint64 current_time, Tank *tank, SDL_Rect *rects)
{
	tank->rot += 0.017;
	for (size_t i = 0; i < tank->bubbles_size; ++i) {
		BubbleSprite bs = tank->bubbles[i];
		unsigned long total_complete_periods = (unsigned long) ((double) current_time / bs.period); // rounding down on purpose with the cast
		double phase = ((double) current_time - ((double) total_complete_periods * bs.period)) / bs.period;
		double scale_factor = 1.0 + bs.pulsiness * sin(2 * M_PI * phase);
		double new_size = bs.size * scale_factor;
		
		double rot_x = bs.x * cos(tank->rot) - bs.y * sin(tank->rot); // NOTE: vector math
		double rot_y = bs.x * sin(tank->rot) + bs.y * cos(tank->rot);
		int rect_x = (int) (tank->x + rot_x - new_size / 2);
		int rect_y = (int) (tank->y + rot_y - new_size / 2);
		SDL_Rect r = {rect_x, rect_y, (int) new_size, (int) new_size};
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

int gameRun(SDL_Window *wind, SDL_Renderer *rend)
{
/* initialize game assets and data */
	Tank player_tank;
	BubbleSprite bubbles[BUBBLES_SIZE];
	SDL_Rect rects[BUBBLES_SIZE];
	
	SDL_Texture *tex_bubble = IMG_LoadTexture(rend, "bubble.png");
	if (tex_bubble == NULL) {
		fprintf(stderr, "Error creating texture: %s\n", IMG_GetError());
		return -1;
	}
	
	for (size_t i = 0; i < BUBBLES_SIZE; ++i) {
		BubbleSprite bs = {
			(double) (rand() % 640) - 320.0,
			(double) (rand() % 480) - 240.0,
			(double) (rand() % 15) + 35.0,
			(double) (rand() % 250) + 625.0,
			(double) (rand() % 10) / 100.0 + 0.1,
			{0},
			tex_bubble
		};
		//SDL_Rect r = {640 / 2 - 50 / 2 + 60 * ((int) i - 5), 480 / 2 - 50 / 2, 50, 50};
		bubbles[i] = bs;
	}
	
	player_tank.x = 320.0;
	player_tank.y = 240.0;
	player_tank.rot = 0.0;
	player_tank.bubbles_size = BUBBLES_SIZE;
	player_tank.bubbles = bubbles;

/* run the game */	
	int game_running = 1;
	Uint64 simulation_time = SDL_GetTicks64();
	while (game_running) {
		Uint64 current_time = SDL_GetTicks64();
		
		while (simulation_time < current_time) {
			simulation_time += MS_PER_UPDATE;
			gameUpdate(simulation_time, &player_tank, rects);
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

/* free all game assets */	
	SDL_DestroyTexture(tex_bubble);
	return 0;
}