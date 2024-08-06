#include "input.h"

void input_Init(Input *input)
{
	for (size_t i = COMMAND_START; i <= COMMAND_END; ++i) {
		input->command_states[i] = KEY_UP;
	}
}

void input_Poll(Input *input)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			input->command_states[COMMAND_QUIT] = KEY_DOWN | KEY_PRESSED;
		} else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:  input->command_states[COMMAND_PLAYER_ROTATE_CCW] = KEY_DOWN | KEY_PRESSED; break;
				case SDLK_RIGHT: input->command_states[COMMAND_PLAYER_ROTATE_CW]  = KEY_DOWN | KEY_PRESSED; break;
				default: break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:  input->command_states[COMMAND_PLAYER_ROTATE_CCW] = KEY_UP | KEY_RELEASED; break;
				case SDLK_RIGHT: input->command_states[COMMAND_PLAYER_ROTATE_CW]  = KEY_UP | KEY_RELEASED; break;
				default: break;
			}
		}
	}
}

int input_GetCommandState(const Input *input, int command)
{
	return input->command_states[command];
}