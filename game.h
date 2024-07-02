/**
 * It's the game. Initialization of the game and its auxiliaries.
 * Running the game loop. Releasing the game's resources.
 */

#ifndef GAME_H
#define GAME_H

#include <SDL.h>

//extern const Uint64 MIN_MS_PER_DRAW_CALL; // not used and may never be used
extern const Uint64 MS_PER_UPDATE;

int gameInitialize(SDL_Renderer*, SDL_Texture**);
void gameUpdate(Uint64, double*);
void gameRender(SDL_Window*, SDL_Renderer*, SDL_Texture*, const double);
void gameDestroy(SDL_Texture*);
int gameRun(SDL_Window*, SDL_Renderer*);

#endif // GAME_H