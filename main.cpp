//William Shevis Johnson
//Data Structures - Spring 2016
//Game of Life - Main File

#include <iostream>
#include <fstream>
#include "game.h"

using namespace std;

int getUserChoice(string prompt, string failPrompt, string responses[], int size) 
{ //returns the index of the choice the user has selected
	cout << prompt;
	string userIn;

	while(true) {
		cin >> userIn;
		for (int i = 0; i < size; ++i) {
			if (!userIn.compare(responses[i])) {
				return i;
			}
		}
		cout << failPrompt;
	}
}

string getUserInput(string prompt) 
{ //prints a prompt and returns user input as a string	
	cout << prompt;
	string userIn;
	cin >> userIn;
	return userIn;
}

string* makeMap(int& rows, int& cols) 
{ //retrieves dimension and density information from user and returns a randomly generated map
	double dens;

	//get user input
	while (true) {
		try {
			rows = stoi(getUserInput("Please enter number of rows: "))+2;
			if (rows < 1) throw new invalid_argument("invalid");
			cols = stoi(getUserInput("Please enter number of columns: "))+2;
			if (cols < 1) throw new invalid_argument("invalid");
			dens = stod(getUserInput("Please enter starting population density (between 0 and 1): "));
			if (dens < 0.0 | dens > 1.0) throw new invalid_argument("invalid");
			break;
		} catch (invalid_argument& ia) {
			cout << "Invalid input, please try again." << endl;
		} catch (invalid_argument* ia) {
			cout << "Invalid input, please try again." << endl;
		}
	}

	//create map
	string* output = new string[rows];

	cout << "\nYour map:" << endl;

	for (int i = 0; i < rows; ++i) {
		if (i == 0 | i == rows-1) {
			string line = string(cols, 'o');
			output[i] = line;
			cout << line << endl;
		} else {
			string line = "";
			for (int j = 0; j < cols; ++j) {
				if (j == 0 | j == cols-1) {
					line += 'o';
				} else {
					double random = double((rand() % 101))/100.0;
					//cout << random << ":";
					if (random >= dens) {
						line += '-';
					} else {
						line += 'X';
					}
				}
			}
			output[i] = line;
			cout << line << endl;
		}
	}

	return output;
}

string* importMap(ifstream& file, int& rows, int& cols) 
{ //creates and returns a map from an imported file
	string line;
	getline(file, line);
	rows = stoi(line)+2;
	getline(file, line);
	cols = stoi(line)+2;

	cout << "\nYour map:" << endl;

	string* output = new string[rows];

	for (int i = 0; i < rows; ++i) {
		if (i == 0 | i == rows-1) {
			line = string(cols, 'o');
		} else {
			getline(file, line);
			line = "o" + line + "o";
		}
		output[i] = line;
		cout << line << endl;
	}

	return output;
}

int main() 
{ //retrieves user input and initializes Game object to run simulation
	string* mapArray;
	
	int rows;
	int cols;
	int mode;
	int outputMode;


	cout << "\n>>>> Welcome to Conway's Game of Life! <<<<" << endl << ">>>>>>>> by William Shevis Johnson <<<<<<<<\n" << endl;

	string responses[2] = {"r", "f"};
	int response = getUserChoice("Would you like to generate a random map\nor import one from a file? (r for random, f for file):", "Invalid input. Please enter 'r' or 'f': ", responses, 2);

	switch (response) {
	case 0:
		mapArray = makeMap(rows, cols);
		break;
	case 1:
		ifstream mapFile;
		do {
			mapFile.open(getUserInput("Please enter the name of the file you wish to use: "));
			if (!mapFile.is_open()) {
				cout << "File not found." << endl;
			}
		} while (!mapFile.is_open());
		mapArray = importMap(mapFile, rows, cols);
		break;
	}

	string modes[3] = {"1", "2", "3"};
	mode = getUserChoice("\nGame Modes:\n(1) Classic\n(2) Doughnut\n(3) Mirror\n\nPlease enter a number: ", "Invalid input. Please enter 1, 2, or 3: ", modes, 3);

	string outputModes[3] = {"1", "2", "3"};
	outputMode = getUserChoice("\nOutput Modes:\n(1) Brief pause between generations.\n(2) Press enter between generations.\n(3) Output to a file. \n\nPlease enter a number: ", "Invalid input. Please enter 1, 2, or 3: ", outputModes, 3);

	cin.clear();
	cin.ignore (10, '\n');

	Game* newGame = new Game(mapArray, rows, cols, mode, outputMode);

	newGame->run();

	cout << "\nSimulation has finished. Press enter to exit..." << endl;
	cin.clear();
	cin.ignore (10, '\n');

	return(0);
}






