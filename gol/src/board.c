
#include "../inc/board.h"

extern BOARD *newBoard(int x, int y)
{
	BOARD *temp = malloc(sizeof(BOARD));

	if (temp == NULL) {
		fprintf(stderr, "BOARD structure malloc error");
		exit(EXIT_FAILURE);
	}

	temp->width = x;
	temp->height = y;
	temp->board = calloc(sizeof(int),x*y);

	if (temp->board == NULL) {
		fprintf(stderr, "BOARD integer calloc error");
		exit(EXIT_FAILURE);
	}

	return temp;
}

extern void copyto(BOARD *b, int num)
{
	for (int i = 0; i < b->width; i++) {
		for (int j = 0; j < b->height; j++) {
			if (num == 0) {
				b->buffer[i*b->width+j] = b->board[i*b->width+j];
			} else if (num == 1) {
				b->board[i*b->width+j] = b->buffer[i*b->width+j];
			}
		}
	}
}

extern void destroyBoard(BOARD *board)
{
	free(board->board);
	free(board);
}

extern void printBoard(BOARD *board)
{
	int i, j;

	for (i = 0; i < board->width; i++) {
		for (j = 0; j < board->height; j++) {
			printf("%d ", board->board[i*board->width+j]);
		}
		printf("\n");
	}
}

extern void randomizeBoard(BOARD *board, int chance)
{
	int i, j;

	for (i = 0; i < board->width; i++) {
		for (j = 0; j < board->height; j++) {
			if (rand() % chance == 0) {
				board->board[i*board->width+j] = 1;
			} else {
				board->board[i*board->width+j] = 0;
			}
		}
	}
}

