#include "tank.h"

#include <math.h>

#include "util.h"

void tank_ApplyControls(const Input *input, Tank *tank)
{
	// rotate toward cursor
	double cursor_delta_x = input->cursor_x - tank->x; // TODO: This will not work when there is a camera that
	double cursor_delta_y = input->cursor_y - tank->y; // follows the player's tank around (moving the origin).
	double y_over_x = cursor_delta_y / cursor_delta_x; // Fix by also storing the world position of the cursor in input.
	double angle_toward_cursor = cursor_delta_x >= 0.0 ? atan(y_over_x) : atan(y_over_x) + M_PI;
	tank->rot = angle_toward_cursor;
	
	// move up, left, down, right
	double delta_x = 0.0;
	double delta_y = 0.0;
	char up    = input_CommandActive(input, COMMAND_PLAYER_MOVE_UP);
	char left  = input_CommandActive(input, COMMAND_PLAYER_MOVE_LEFT);
	char down  = input_CommandActive(input, COMMAND_PLAYER_MOVE_DOWN);
	char right = input_CommandActive(input, COMMAND_PLAYER_MOVE_RIGHT);
	if (up && !down) {
		delta_y = -1.0;
	} else if (down && !up) {
		delta_y =  1.0;
	}
	if (left && !right) {
		delta_x = -1.0;
	} else if (right && !left) {
		delta_x =  1.0;
	}
	// normalize diagonal directions
	if (delta_x != 0.0 && delta_y != 0.0) {
		delta_x *= M_SQRT1_2;
		delta_y *= M_SQRT1_2;
	}
	// kinematics
	double acceleration =  0.75; // TEMP
	double max_speed    = 10.0 ; // TEMP
	if (delta_x != 0.0) {
		tank->v_x += acceleration * delta_x;
	} else {
		int sign_before = util_sign(tank->v_x);
		tank->v_x -= acceleration * sign_before;
		if (sign_before != util_sign(tank->v_x)) {
			tank->v_x = 0.0;
		}
	}
	if (delta_y != 0.0) {
		tank->v_y += acceleration * delta_y;
	} else {
		int sign_before = util_sign(tank->v_y);
		tank->v_y -= acceleration * sign_before;
		if (sign_before != util_sign(tank->v_y)) {
			tank->v_y = 0.0;
		}
	}
	tank->v_x = util_clamp(tank->v_x, -max_speed, max_speed);
	tank->v_y = util_clamp(tank->v_y, -max_speed, max_speed);
	
	tank->x += tank->v_x;
	tank->y += tank->v_y;
}