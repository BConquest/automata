cc = clang
flags = -Wall -Wextra -O3
links = -lSDL2
include = src/board.c src/game.c

all:
	$(cc) $(include) $(links) $(flags) gol.c -o gol

test:
	$(cc) $(include) $(flags) test.c -o test
