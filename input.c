#include "input.h"

void inputInit(Input *input)
{
	for (size_t i = COMMAND_START; i <= COMMAND_END; ++i) {
		input->command_states[i] = 0x2;
	}
}

void inputPoll(Input *input)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			input->command_states[COMMAND_QUIT] = 0x1;
		} else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:  input->command_states[COMMAND_PLAYER_ROTATE_CCW] = 0x1; break;
				case SDLK_RIGHT: input->command_states[COMMAND_PLAYER_ROTATE_CW]  = 0x1; break;
				default: break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:  input->command_states[COMMAND_PLAYER_ROTATE_CCW] = 0x2; break;
				case SDLK_RIGHT: input->command_states[COMMAND_PLAYER_ROTATE_CW]  = 0x2; break;
				default: break;
			}
		}
	}
}

int inputGetCommandState(Input *input, int command)
{
	return input->command_states[command];
}