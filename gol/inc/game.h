#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct game {
	int screenWidth;
	int screenHeight;
	int cellWidth;
	int numXCells;
	int numYCells;
}GAME;

extern GAME *newGame(int, int, int, int, int);

extern void destroyGame(GAME *);
#endif
