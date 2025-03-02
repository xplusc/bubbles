#include "input.h"

void input_Init(Input *input)
{
	for (size_t i = COMMAND_START; i < COMMAND_END; ++i) {
		input->command_states[i] = 0; // command is inactive
	}
}

void input_Poll(Input *input)
{
	SDL_Event e;
	// there may be multiple input events so we must loop until all are handled
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			input->command_states[COMMAND_QUIT] = 1;
		} else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
				case SDLK_w: input->command_states[COMMAND_PLAYER_MOVE_UP]    = e.type == SDL_KEYDOWN; break; // 1 if key down, 0 if key up
				case SDLK_a: input->command_states[COMMAND_PLAYER_MOVE_LEFT]  = e.type == SDL_KEYDOWN; break;
				case SDLK_s: input->command_states[COMMAND_PLAYER_MOVE_DOWN]  = e.type == SDL_KEYDOWN; break;
				case SDLK_d: input->command_states[COMMAND_PLAYER_MOVE_RIGHT] = e.type == SDL_KEYDOWN; break;
				case SDLK_q: input->command_states[COMMAND_QUIT]              = e.type == SDL_KEYDOWN; break;
				default: break;
			}
		} else if (e.type == SDL_MOUSEMOTION) {
			int mouse_x, mouse_y;
			SDL_GetMouseState(&mouse_x, &mouse_y);
			input->cursor_x = (double) mouse_x;
			input->cursor_y = (double) mouse_y;
		}
	}
}

char input_CommandActive(const Input *input, InputCommand command)
{
	return input->command_states[command];
}