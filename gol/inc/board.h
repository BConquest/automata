#ifndef __board_h__
#define __board_h__

#include <stdio.h>
#include <stdlib.h>

typedef struct board {
	int width;
	int height;
	int **board;
	int **buffer;
}BOARD;

extern BOARD *newBoard(int, int);

extern int getCell(BOARD *, int, int);

extern void copyto(BOARD *, int);
extern void destroyBoard(BOARD *);
extern void printBoard(BOARD *);
extern void randomizeBoard(BOARD *, int);
extern void updateBoard(BOARD *);
#endif
