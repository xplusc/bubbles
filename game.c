#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_image.h>

const Uint64 MS_PER_UPDATE = 16;
const size_t BUBBLES_SIZE = 4;

void game_Update(Uint64 current_time, const Input *input, Tank *tank, ArrayList *rect_list)
{
	arraylist_Clear(rect_list);
	tank_ApplyControls(input, tank);
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
		arraylist_Append(rect_list, &r);
	}
	
	return;
}

void game_Render(SDL_Window *wind, SDL_Renderer *rend, SDL_Texture *tex_bubble, const SDL_Rect *rects, const size_t num_rects)
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

int game_Run(SDL_Window *wind, SDL_Renderer *rend)
{
/* initialize game assets and data */
	
	Tank player_tank;
	ArrayList *bubble_list = arraylist_Create(sizeof(BubbleSprite));
	ArrayList *rect_list   = arraylist_Create(sizeof(SDL_Rect));
	
	SDL_Texture *tex_bubble = IMG_LoadTexture(rend, "bubble.png");
	if (tex_bubble == NULL) {
		fprintf(stderr, "Error creating texture: %s\n", IMG_GetError());
		return -1;
	}
	
	BubbleSprite bs = {0.0, 0.0, 40.0, 625.0, 0.15, {0}, tex_bubble};
	bubble_Randomize(&bs);
	arraylist_Append(bubble_list, &bs);
	bs.x += 25.0;
	bs.size += -20.0;
	bubble_Randomize(&bs);
	arraylist_Append(bubble_list, &bs);
	bs.x += -50.0;
	bs.y += -15.0;
	bubble_Randomize(&bs);
	arraylist_Append(bubble_list, &bs);
	bs.y += 30.0;
	bubble_Randomize(&bs);
	arraylist_Append(bubble_list, &bs);
	
	player_tank.x = 320.0;
	player_tank.y = 240.0;
	player_tank.rot = 0.0;
	player_tank.bubbles_size = BUBBLES_SIZE;
	player_tank.bubbles = bubble_list->data;
	
	Input input;
	input_Init(&input);

/* run the game */
	int game_running = 1;
	Uint64 simulation_time = SDL_GetTicks64();
	while (game_running) {
		Uint64 current_time = SDL_GetTicks64();
		
		while (simulation_time < current_time) {
			simulation_time += MS_PER_UPDATE;
			input_Poll(&input);
			game_Update(simulation_time, &input, &player_tank, rect_list);
			if (input_CommandActive(&input, COMMAND_QUIT))
				game_running = 0;
		}
		
		game_Render(wind, rend, tex_bubble, rect_list->data, BUBBLES_SIZE);
	}

/* free all game assets */
	arraylist_Destroy(&bubble_list);
	arraylist_Destroy(&rect_list);
	SDL_DestroyTexture(tex_bubble);
	return 0;
}