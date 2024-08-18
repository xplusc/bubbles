/**
 * The Input struct. Keeps track of which commands are currently active.
 * Maintains bindings between SDL scancodes and commands that control the game.
 * Allows callback functions to be registered to any SDL_KEYDOWN or SDL_KEYUP
 * event.
 */

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

/* Command definitions: */
enum input_command {
	COMMAND_START					 = 0,
	COMMAND_PLAYER_MOVE_UP			 = 0,
	COMMAND_PLAYER_MOVE_LEFT,		// 1
	COMMAND_PLAYER_MOVE_DOWN,		// 2
	COMMAND_PLAYER_MOVE_RIGHT,		// 3
	COMMAND_QUIT,					// 4
	COMMAND_END						// 5
};
typedef enum input_command InputCommand;

/**
 * The input struct is an array of current command states, a mapping of SDL scancodes
 * to commands, and a mapping of commands to function pointers for callback functions.
 */
struct input {
	//InputCommand command_map[NUM_SCANCODES]; // indices are SDL scancodes, elements are commands
	//void (*function_map[COMMAND_END])(); // indices are commands, elements are pointers to functions taking no arguments and returning void
	char command_states[COMMAND_END]; // OPTIMIZATION: Use a bit field to reduce the space needed even further.
	double cursor_x;
	double cursor_y;
};
typedef struct input Input;

/**
 * Initialize the input object such that command_map contains all default key bindings,
 * function_map is empty, and command_states is filled with zeros (command inactive).
 */
void input_Init(Input*);

/**
 * Update the input object with the currently received input events, consumes the
 * events.
 */
void input_Poll(Input*);

/**
 * Given the command type return 1 if it is currently active, 0 otherwise.
 */
char input_CommandActive(const Input*, InputCommand);

#endif // INPUT_H