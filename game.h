/**
 * It's the game. Initialization of the game and its auxiliaries.
 * Running the game loop. Releasing the game's resources.
 */

#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "bubble.h"

//extern const Uint64 MIN_MS_PER_DRAW_CALL; // not used and may never be used
extern const Uint64 MS_PER_UPDATE;

int gameInitialize(SDL_Renderer*, SDL_Texture**, BubbleSprite*, const size_t);
void gameUpdate(Uint64, BubbleSprite*, SDL_Rect*, const size_t);
void gameRender(SDL_Window*, SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const size_t);
void gameDestroy(SDL_Texture*);
int gameRun(SDL_Window*, SDL_Renderer*);

#endif // GAME_H