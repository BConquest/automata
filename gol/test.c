#include <stdio.h>
#include <stdlib.h>

#include "./inc/board.h"

int main(int argc, char *argv[]) {
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);

	BOARD *b = newBoard(w, h);

	printBoard(b);
	
	randomizeBoard(b, 2);
	printf("\n");
	printBoard(b);
	printf("\n");

	for (int i = 0; i < atoi(argv[3]); i++) {
		updateBoard(b);
		printBoard(b);
		printf("\n");
		sleep(1);
	}

	destroyBoard(b);
}
