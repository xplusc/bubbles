#!/bin/bash
gcc -o bubbles \
	-W -Wall -Wextra -pedantic \
	bubbles.c \
	game.c \
	-I./SDL2/include/SDL2 -I./SDL2_image/include/SDL2 \
	-L./SDL2/lib -L./SDL2_image/lib \
	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image