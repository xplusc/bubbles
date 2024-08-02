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

enum input_state {
	KEY_DOWN     = 0x1,
	KEY_UP       = 0x2,
	KEY_PRESSED  = 0x4,
	KEY_RELEASED = 0x8
};
typedef enum input_state InputState;

struct input {
	int command_states[COMMAND_END + 1];
};
typedef struct input Input;

void inputInit(Input*);
void inputPoll(Input*);
int inputGetCommandState(const Input*, int);

#endif // INPUT_H