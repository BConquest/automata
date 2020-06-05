
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
	temp->board = calloc(sizeof(int *), x);
	temp->buffer = calloc(sizeof(int *), x);

	if (temp->board == NULL || temp->buffer == NULL) {
		fprintf(stderr, "newBoard calloc error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < x; i++) {
		temp->board[i] = calloc(sizeof(int), y);
		temp->buffer[i] = calloc(sizeof(int), y);

		if (temp->board[i] == NULL || temp->buffer[i] == NULL) {
			fprintf(stderr, "newBoard calloc error");
			exit(EXIT_FAILURE);
		}
	}
	return temp;
}

extern int getCell(BOARD *b, int x, int y)
{
	return b->board[x][y];
}

extern void copyto(BOARD *b, int num)
{
	for (int i = 0; i < b->width; i++) {
		for (int j = 0; j < b->height; j++) {
			if (num == 0) {
				b->buffer[i][j] = b->board[i][j];
			} else if (num == 1) {
				b->board[i][j] = b->buffer[i][j];
			}
		}
	}
}

extern void destroyBoard(BOARD *b)
{
	for (int i = 0; i < b->width; i++) {
		free(b->board[i]);
		free(b->buffer[i]);
	}
	free(b->board);
	free(b->buffer);
	free(b);
}

extern void printBoard(BOARD *board)
{
	int i, j;

	for (i = 0; i < board->width; i++) {
		for (j = 0; j < board->height; j++) {
			printf("%d ", board->board[i][j]);
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
				board->board[i][j] = 1;
			} else {
				board->board[i][j] = 0;
			}
		}
	}
}

extern int checkNeighbors(int **cells, int x, int y, int w, int h)
{
	int sum = 0;

	if (x == 0) {
		if (y == 0) {
//			if (cells[w-1][h-1] == 1) sum++;
		} else {
//			if (cells[w-1][y-1] == 1) sum++;
		}

//		if (cells[w-1][y] == 1) sum++;

		if (y == h-1) {
//			if (cells[w-1][0] == 1) sum++;
		} else {
//			if (cells[w-1][y+1] == 1) sum++;
		}
	} else {
		if (y == 0) {
//			if (cells[x-1][h-1] == 1) sum++;
		} else {
			if (cells[x-1][y-1] == 1) sum++;
		}

		if (cells[x-1][y] == 1) sum++;

		if (y == h-1) {
//			if (cells[x-1][0] == 1) sum++;
		} else {
			if (cells[x-1][y+1] == 1) sum++;
		}
	}

	if (y == 0) {
//		if (cells[x][h-1]) sum++;
	} else {
		if (cells[x][y-1] == 1) sum++;
	}

	if (y == h-1) {
//		if (cells[x][0] == 1) sum++;
	} else {
		if (cells[x][y+1] == 1) sum++;
	}

	if (x == w-1) {
		if (y == 0) {
//			if (cells[0][h-1] == 1) sum++;
		} else {
//			if (cells[0][y-1] == 1) sum++;
		}

//		if (cells[0][y] == 1) sum++;

		if (y == h-1) {
//			if (cells[0][0] == 1) sum++;
		} else {
//			if (cells[0][y+1] == 1) sum++;
		}
	} else {
		if (y == 0) {
//			if (cells[x+1][h-1] == 1) sum++;
		} else {
			if (cells[x+1][y-1] == 1) sum++;
		}

		if (cells[x+1][y] == 1) sum++;

		if (y == h-1) {
//			if (cells[x+1][0] == 1) sum++;
		} else {
			if (cells[x+1][y+1] == 1) sum++;
		}
	}

	return sum;
}

extern void updateBoard(BOARD *b)
{	
	int i, j;

	copyto(b, 0);

	//right now ignores outer edges
	for (i = 0; i < b->width; i++) {
		for (j = 0; j < b->height; j++) {
			int neighbors = checkNeighbors(b->board, i, j, b->width, b->height);
			if (b->board[i][j] == 1) {
				if (neighbors < 2) {
					b->buffer[i][j] = 0;
				} else if (neighbors > 3) {
					b->buffer[i][j] = 0;
				} else {
					b->buffer[i][j] = 1;
				}
			} else {
				if (neighbors == 3) {
					b->buffer[i][j] = 1;
				}
			}
		}
	}
	copyto(b, 1);
}
