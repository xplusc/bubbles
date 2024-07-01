#include "game.h"

#include <stdio.h>
#include <SDL_image.h>

const Uint64 MS_PER_UPDATE = 16;

int gameInitialize(SDL_Renderer *rend, SDL_Texture **tex_bubble)
{
	// load assets
	*tex_bubble = IMG_LoadTexture(rend, "bubble.png");
	if (*tex_bubble == NULL) {
		fprintf(stderr, "Error creating texture: %s\n", IMG_GetError());
		return 1;
	}
	return 0;
}

void gameRun(SDL_Window *wind, SDL_Renderer *rend, SDL_Texture *tex_bubble)
{
	int game_running = 1;
	Uint64 simulation_time = SDL_GetTicks64();
	
	while (game_running) {
		Uint64 current_time = SDL_GetTicks64();
		
		while (simulation_time < current_time) {
			simulation_time += MS_PER_UPDATE;
			// gameUpdate();
			SDL_Event event;
			// input events
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT: game_running = 0; break;
					default: break;
				}
			}
		}
		
		// gameRender();
		int wind_width;
		int wind_height;
		SDL_GetWindowSize(wind, &wind_width, &wind_height);
		
		// clear screen
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderClear(rend);
		
		// draw assets
		const SDL_Rect bubble_rect = {wind_width / 2 - 100, wind_height / 2 - 100, 200, 200};
		SDL_RenderCopy(rend, tex_bubble, NULL, &bubble_rect);
		
		// draw to window
		SDL_RenderPresent(rend);
	}
	return;
}

void gameDestroy(SDL_Texture *tex_bubble)
{
	SDL_DestroyTexture(tex_bubble);
	return;
}