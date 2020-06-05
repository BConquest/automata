#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "./inc/board.h"
#include "./inc/game.h"

int chance = 0;
int pauseFlag = 1;

void drawCells(SDL_Renderer *renderer, BOARD *b, GAME *g)
{
	SDL_Rect cell;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (int x = 0; x < g->numXCells; x++) {
		for (int y = 0; y < g->numYCells; y++) {
			cell.x = x*g->cellWidth;
			cell.y = y*g->cellWidth;
			cell.w = x*g->cellWidth+g->cellWidth;
			cell.h = y*g->cellWidth+g->cellWidth;
			if (b->board[x][y] == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			} else {
				SDL_SetRenderDrawColor(renderer, 100, 125, 255,   255);
			}
			SDL_RenderFillRect(renderer, &cell);
		}
	}
	SDL_RenderPresent(renderer);
}

void draw(SDL_Renderer *renderer, BOARD *b, GAME *g)
{
	drawCells(renderer, b, g);
}

void drawFrame(SDL_Renderer *renderer, BOARD *b, GAME *g)
{
	drawCells(renderer, b, g);
}

void update(BOARD *b, GAME *g)
{
	updateBoard(b);
}

int main(int argc, char *argv[])
{
	if (argc != 6) {
		printf("Usage ./gol <height> <width> <size> <iterations> <chance>\n");
		exit(EXIT_FAILURE);
	}

	int HEIGHT = atoi(argv[1]);
	int WIDTH = atoi(argv[2]);
	int SIZE = atoi(argv[3]);

	int NUMXCELLS = WIDTH / SIZE;
	int NUMYCELLS = HEIGHT / SIZE;

	chance = atoi(argv[5]);

	BOARD *b = newBoard(NUMXCELLS, NUMYCELLS);
	GAME *g = newGame(WIDTH, HEIGHT, SIZE, NUMXCELLS, NUMYCELLS);

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *window = SDL_CreateWindow("Conway's Game of Life",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIDTH, HEIGHT,
			SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);

	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_SetWindowResizable(window, SDL_FALSE);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Event e;
	int quit = 0;
	int counter = atoi(argv[4]);
	unsigned int dcurr = 0, dprev = 0;
	unsigned int ucurr = 0, uprev = 0;
	
	randomizeBoard(b, chance);

	while (quit == 0) {
		dprev = dcurr;
		uprev = ucurr;

		while(SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_KEYDOWN:
					printf("%d\n", e.key.keysym.sym);
					if (e.key.keysym.sym == 32) {
						pauseFlag = !pauseFlag;
					} else if (e.key.keysym.sym == 44) {
						update(b, g);
					} else if (e.key.keysym.sym == 114) {
						randomizeBoard(b, chance);
					}
					break;
				default: {}
			}
		}

		dprev = dcurr;
		draw(renderer, b, g);
		dcurr = SDL_GetTicks();

		uprev = ucurr;
		if (pauseFlag) {
			update(b, g);
		}
		ucurr = SDL_GetTicks();

		printf("Draw Time : %5d\t", dcurr-dprev);
		printf("Update Time : %5d\r", ucurr-uprev);
		counter--;

		if (counter <= 0) {
			quit = 1;
		}
	}

	destroyBoard(b);
	destroyGame(g);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
