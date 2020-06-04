#include "../inc/game.h"

extern GAME *newGame(int w, int h, int s, int x, int y)
{
	GAME *temp = malloc(sizeof(GAME));

	if (temp == NULL) {
		fprintf(stderr, "GAME structure malloc error");
		exit(EXIT_FAILURE);
	}

	temp->screenWidth = w;
	temp->screenHeight = h;
	temp->cellWidth = s;
	temp->numXCells = x;
	temp->numYCells = y;

	return temp;
}

extern void destroyGame(GAME *game)
{
	free(game);
}
