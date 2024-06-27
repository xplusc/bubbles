#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char *argv[])
{
	// initialize
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
	
	// load assets
	SDL_Texture *tex_bubble = IMG_LoadTexture(rend, "bubble.png");
	if (tex_bubble == NULL) {
		fprintf(stderr, "Error creating texture: %s\n", IMG_GetError());
		return 0;
	}
	
	int wind_width;
	int wind_height;
	SDL_GetWindowSize(wind, &wind_width, &wind_height);
	int running = 1;
	SDL_Event event;
	while (running) {
		// events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: running = 0; break;
				default: break;
			}
		}
		
		// clear screen
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderClear(rend);
		
		// draw assets
		const SDL_Rect bubble_rect = {wind_width / 2 - 100, wind_height / 2 - 100, 200, 200};
		SDL_RenderCopy(rend, tex_bubble, NULL, &bubble_rect);
		
		// draw to window
		SDL_RenderPresent(rend);
		
		// wait until next frame
		SDL_Delay(1000.0 / 60);
	}
	
	// release resources
	SDL_DestroyTexture(tex_bubble);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(wind);
	SDL_Quit();
	return 0;
}