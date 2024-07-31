#ifndef INPUT_H
#define INPUT_h

#include <SDL.h>

enum input_command {
	COMMAND_START					= 0,
	COMMAND_PLAYER_ROTATE_CW		= 0,
	COMMAND_PLAYER_ROTATE_CCW		= 1,
	COMMAND_QUIT					= 2,
	COMMAND_END						= 2
};
typedef enum input_command InputCommand;

struct input {
	// 0x1 = key down
	// 0x2 = key up
	// 0x4 = key pressed
	// 0x8 = key released
	InputCommand command_states[COMMAND_END + 1];
};
typedef struct input Input;

void inputInit(Input*);
void inputPoll(Input*);
int inputGetCommandState(Input*, int);

#endif // INPUT_H