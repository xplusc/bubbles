#include "input.h"

void input_Init(Input *input)
{
	for (size_t i = COMMAND_START; i <= COMMAND_END; ++i) {
		input->command_states[i] = 0; // command is inactive
	}
}

void input_Poll(Input *input)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			input->command_states[COMMAND_QUIT] = 1;
		} else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:  input->command_states[COMMAND_PLAYER_ROTATE_CCW] = 1; break;
				case SDLK_RIGHT: input->command_states[COMMAND_PLAYER_ROTATE_CW]  = 1; break;
				default: break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:  input->command_states[COMMAND_PLAYER_ROTATE_CCW] = 0; break;
				case SDLK_RIGHT: input->command_states[COMMAND_PLAYER_ROTATE_CW]  = 0; break;
				default: break;
			}
		}
	}
}

char input_CommandActive(const Input *input, int command)
{
	return input->command_states[command];
}