# Automata

## Elementary Cellular Automata (eca)

This is contains the c code for running simulations of elementary cellular automata. The usage is `./a.out <size> <iterations> <rule: 0-255> <sleep time>`.
    - Size is the size of the board and it wraps around the board.
    - Iterations is the number of steps to run through
    - Rule is based off how [rules](https://en.wikipedia.org/wiki/Elementary_cellular_automaton) are set up for this style of cellular automata.
    - Sleep time is how long to delay between each step.

Some examples of it running are:
[![asciicast](https://asciinema.org/a/xGopEBNxNyXll4ufU8XrtVLof.svg)](https://asciinema.org/a/xGopEBNxNyXll4ufU8XrtVLof)

[![asciicast](https://asciinema.org/a/dOkmwJ9L0uzFyOL7jOX9SnGdE.svg)](https://asciinema.org/a/dOkmwJ9L0uzFyOL7jOX9SnGdE)

## Game of Life (gol)

This is Conway's came of written in C using libSDL2. You will need libSDL2 to compile it. The usage for it is `./gol <height> <width> <size> <interations> <chance>`
    - Height is the size in pixels of the window
    - Width is the size in pixels of the window
    - Size is the size of the squares that you want in pixels
    - Iterations is how many times you want the program to run for
    - Chance is the odds that a cell will die on spawing.

The user input that is accepted for now is:
    - space = Pauses the program
    - ,     = Steps ahead once
    - r     = Regenerates the board

Video of it working https://youtu.be/3OfzzbuPY0k.
