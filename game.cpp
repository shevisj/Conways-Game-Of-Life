//William Shevis Johnson
//Data Structures - Spring 2016
//Game of Life - Game Implimentation File

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "game.h"

using namespace std;

Game::Game() {} //default constructor

Game::Game(string* p_map, int p_rows, int p_cols, int p_mode, int p_outputMode) 
{ //detailed constructor
	this->map = p_map;
	this->shadowMap = new string[p_rows];
	this->shadowMap2 = new string[p_rows];
	this->rows = p_rows;
	this->cols = p_cols;
	this->mode = p_mode;
	this->outputMode = p_outputMode;
	if (p_outputMode == 2) {
		this->outputFile.open("johnson.out");
	}
}


Game::~Game() 
{ //destructor
	delete this->map;
	delete this->shadowMap;
	delete this->shadowMap2;
}

void Game::run() 
{ //public simulation initializer
	this->toOut("\n");
	for (int i = 0; i < this->rows; ++i) {
		this->toOut(this->map[i]);
		this->toOut("\n");
	}
	cout << "\nPress enter to begin simulation... \n";

	if (this->outputMode == 2) cout << "(Results will be saved to 'johnson.out' in the current directory)";

	cin.clear();
	cin.ignore (10, '\n');

	this->beginSim(); //begins looping simulation
}

void Game::beginSim() 
{ //private simulation function 
	while (true) {
		for (int i = 0; i < this->rows; ++i) {
			string line = "";
			for (int j = 0; j < this->cols; ++j) {

				if (this->map[i][j] == 'o') {
					line += 'o';
					this->toOut('o');
				} else {
					//check neighbors
					int numNeighbors = 0;
					for (int k = -1; k < 2; ++k) {
						for (int l = -1; l < 2; ++l) {
							if (k == 0 & l == 0) {
								//checking self - do nothing
							}
							else if (this->map[i+k][j+l] == 'X'){ //has neighbor
								++numNeighbors;
							} 
							else if(this->map[i+k][j+l] == 'o') { //neighbor is map border
								switch (this->mode) { //Game Mode switch
								case 0:
									//classic - do nothing
									break;
								case 1:
									//doughnut - grid wrap
									if ((i+k) == 0) {
										if ((j+l) == this->cols-1) {
											if (this->map[rows-2][1] == 'X') ++numNeighbors;
										}
										else if ((j+l) == 0) {
											if (this->map[rows-2][cols-2] == 'X') ++numNeighbors;
										}
										else {
											if (this->map[rows-2][j+l] == 'X') ++numNeighbors;
										}
									}
									else if ((i+k) == this->rows-1) {
										if ((j+l) == this->cols-1) {
											if (this->map[1][1] == 'X') ++numNeighbors;
										}
										else if ((j+l) == 0) {
											if (this->map[1][cols-2] == 'X') ++numNeighbors;
										} else {
											if (this->map[1][j+k] == 'X') ++numNeighbors;
										}
									}
									else if ((j+l) == 0) {
										if (this->map[i+k][cols-2] == 'X') ++numNeighbors;
									}
									else {
										if (this->map[i+k][1] == 'X') ++numNeighbors;
									}
									break;
								case 2:
									//mirror - reflect
									if ((i+k) == 0) {
										if ((j+l) == this->cols-1) {
											if (this->map[1][cols-2] == 'X') numNeighbors += 2;
										}
										else if ((j+l) == 0) {
											if (this->map[1][1] == 'X') numNeighbors += 2;
										}
										else {
											if (this->map[1][j+l] == 'X') ++numNeighbors;
										}
									}
									else if ((i+k) == this->rows-1) {
										if ((j+l) == this->cols-1) {
											if (this->map[rows-2][cols-2] == 'X') numNeighbors += 2;
										}
										else if ((j+l) == 0) {
											if (this->map[rows-2][cols-2] == 'X') numNeighbors += 2;
										} else {
											if (this->map[rows-2][j+k] == 'X') ++numNeighbors;
										}
									}
									else if ((j+l) == 0) {
										if (this->map[i+k][1] == 'X') ++numNeighbors;
									}
									else {
										if (this->map[i+k][cols-2] == 'X') ++numNeighbors;
									}
									break;
								}
							}
						}
					}
					if (numNeighbors <= 1) { //dies of lonliness
						line += '-';
						this->toOut('-');
					} else if (numNeighbors == 3) { //new life
						line += 'X';
						this->toOut('X');
					} else if (numNeighbors >= 4) { //overcrowding
						line += '-';
						this->toOut('-');
					} else {
						line += map[i][j];
						this->toOut(map[i][j]);
					}
				}
			}
			this->shadowMap[i] = line;
			this->toOut("\n");
		}

		//check for stability
		if (this->checkGame() | this->checkStable()) {
			this->outputFile.close();
			break;
		}

		//copy maps for next generation
		for (int i = 0; i < this->rows; ++i) {
			this->shadowMap2[i] = this->map[i];
			this->map[i] = this->shadowMap[i];
		}

		switch (this->outputMode) { //switch for output mode
		case 0:
			//brief pause
			cout << endl << endl;
			usleep(500000);
			break;
		case 1:
			//press enter
			this->toOut("\nPress enter to continue...\n");
			cin.clear();
			cin.ignore (10, '\n');
			break;
		case 2:
			//output to a file
			break;
		}
	}
}

bool Game::checkGame() 
{ //compares current map to previous map
	for (int i = 0; i < this->rows; ++i) {
		if (this->shadowMap[i] != this->map[i]) {
			return false;
		}
	}
	return true;
}

bool Game::checkStable()
{ //compares current map to map before previous map
	for (int i = 0; i < this->rows; ++i) {
		if (this->shadowMap[i] != this->shadowMap2[i]) {
			return false;
		}
	}
	return true;
}

void Game::toOut(char output) 
{ //sends output to the correct destination based on output mode
	switch (this->outputMode) {
	case 2:
		this->outputFile << output;
		break;
	default:
		cout << output;
		break;
	}
}

void Game::toOut(string output) 
{ //sends output to the correct destination based on output mode
	switch (this->outputMode) {
	case 2:
		this->outputFile << output;
		break;
	default:
		cout << output;
		break;
	}
}

