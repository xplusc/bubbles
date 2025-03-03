/**
 * It's the game. Initialization of the game and its auxiliaries.
 * Running the game loop. Releasing the game's resources.
 */

#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "input.h"
#include "bubble.h"
#include "tank.h"
#include "arraylist.h"

//extern const Uint64 MIN_MS_PER_DRAW_CALL; // not used and may never be used
extern const Uint64 MS_PER_UPDATE;

/**
 * Process one tick (1/60 s) of time in the game simulation. Takes elapsed time,
 * the input object, a list of tanks, and the render rects ArrayList.
 * 
 * Update order (so far):
 *   - Poll input (happens outside this function currently)
 *   - Set player tank controls
 *   - Apply controls
 *   - Build render conveyor (the list of rects being sent to game_Render())
 */
void game_Update(Uint64, const Input*, Tank*, ArrayList*);

/**
 * Display current game state to the screen. Takes an SDL window, SDL renderer,
 * the bubble texture (just this one texture for now), the render rects list, and
 * the size of the render rects list.
 */
void game_Render(SDL_Window*, SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const size_t);

/**
 * Start the main game loop. game_Update() and game_Render() will be called
 * continuously until the game is quit.
 */
int  game_Run(SDL_Window*, SDL_Renderer*);

#endif // GAME_H