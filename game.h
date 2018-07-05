//William Shevis Johnson
//Data Structures - Spring 2016
//Game of Life - Game Header File

#include <fstream>

using namespace std;

class Game 
{
	//instance variables
	string* map;
	string* shadowMap;
	string* shadowMap2;
	int rows;
	int cols;
	int mode;
	int outputMode;
	ofstream outputFile;

	public:
		Game(); //default constructor
		Game(string* p_map, int p_rows, int p_cols, int p_mode, int p_outputMode); //detailed constructor
		~Game(); //destructor

		void run();

	private:
		void beginSim();
		bool checkGame();
		bool checkStable();
		void toOut(char output);
		void toOut(string output);
};