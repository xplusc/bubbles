#ifndef INPUT_H
#define INPUT_h

#include <SDL.h>

enum input_command {
	COMMAND_START					= 0,
	COMMAND_PLAYER_ROTATE_CW		= 0,
	COMMAND_PLAYER_ROTATE_CCW		= 1,
	COMMAND_QUIT					= 2,
	COMMAND_END						= 3
};
typedef enum input_command InputCommand;

/*enum input_state {
	KEY_DOWN     = 0x1,
	KEY_UP       = 0x2,
	KEY_PRESSED  = 0x4,
	KEY_RELEASED = 0x8
};
typedef enum input_state InputState;*/

struct input {
	char command_states[COMMAND_END];
};
typedef struct input Input;

void input_Init(Input*);
void input_Poll(Input*);
char input_CommandActive(const Input*, int);

#endif // INPUT_H