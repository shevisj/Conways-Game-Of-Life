# Conways-Game-Of-Life
## An implementation of Jon Conway's "Game of Life" written in C++

## Author: William Shevis Johnson
## Data Structures : Spring 2016
## Assignment_2 - Conway's Game of Life

From (Wikipedia)[https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life]:
>"The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

>The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves, or, for advanced players, by creating patterns with particular properties.

## Rules

>The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

* Any live cell with fewer than two live neighbors dies, as if by under population.
* Any live cell with two or three live neighbors lives on to the next generation.
* Any live cell with more than three live neighbors dies, as if by overpopulation.
* Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

>The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules  simultaneously to every cell in the seed; births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations."

## build command:
```
$ g++ main.cpp game.cpp -o <executable>
```

## Resources:
- http://www.cplusplus.com/doc/tutorial/
- http://stackoverflow.com/questions/21695935/how-to-throw-stdinvalid-argument-error
- http://www.math.cornell.edu/~lipa/mec/lesson6.html
