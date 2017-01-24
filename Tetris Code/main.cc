#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Trie.h"
#include "Grid.h"
#include "Level.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "TextDisplay.h"
#include <math.h>
using namespace std;
Trie allCommands;
string blocksFileName = "sequence.txt";
string norandomBlockSequence = "";
int norandomSequenceIndex = 0;
bool textOnly = false;
bool extraFeatureMacro = false;
vector<pair<string, string>> macroCommands;
Grid *g;
Level *currLevel = new Level0;
int startLevel = 0;

int main(int argc, char *argv[]){
	// declaring helper functions
	void ReadCommands(istream &in);

	allCommands.Insert("LEFT RIGHT DOWN DROP LEVELUP LEVELDOWN NORANDOM \
		RANDOM CLOCKWISE COUNTERCLOCKWISE I J L O T S Z RESTART HINT SEQUENCE MACRO");
	
	pair<int, int> gridDimensions(18, 11);

	// Checking command line arguments
	for(int i=1; i<argc; ++i){
		string cmdLineArgument = string(argv[i]);
		if(cmdLineArgument == "-text"){
			textOnly = true;
		}
		else if(cmdLineArgument == "-scriptfile"){
			i += 1;
			blocksFileName = argv[i];
		}
		else if(cmdLineArgument == "-seed"){
			int seed;
			i += 1;
			stringstream tempIss(argv[i]);
			if(tempIss >> seed){
				srand(seed);
			}
		}
		else if(cmdLineArgument == "-startlevel"){
			i += 1;
			stringstream tempIss(argv[i]);
			if(tempIss >> startLevel){
				for (int j = 0; j < startLevel; ++j) {
					currLevel = PlusPlus(currLevel);
				}
			}
		}
		else if(cmdLineArgument == "-extraFeatureMacro"){
			extraFeatureMacro = true;
		}
		else if(cmdLineArgument == "-extraFeatureGrid"){
			try{
				i += 1; int row, col;
				stringstream rowIss(argv[i]);
				rowIss >> row;
				i += 1;
				stringstream colIss(argv[i]);
				colIss >> col;
				if(row >=6 && col >= 6){
					gridDimensions.first = row;
					gridDimensions.second = col;
				}
			}
			catch(...){
				cout << "Usage: ./quadris -extraFeatureGrid row col (row, col >=6)" << endl;
			}
			
		}
		else{
			cout << argv[i] << " not valid command-line argument";
			cout << "Usage:\n-text (for only text display)\n";
			cout << "-seed xxx (sets the random number generator’s seed to xxx)\n";
			cout << "-scriptfile xxx (uses file xxx  as a source of blocks for level 0)\n";
			cout << "-startlevel n (Starts the game in level n)\n" ;
			cout << "-extraFeatureMacro (use extra feature macro)\n";
			cout << "-extraFeatureMacro row col (use extra feature gridDimensions)\n" << endl;
		}
	}

	g = new Grid(gridDimensions.first, gridDimensions.second, !textOnly);

	g->SetShapes(' ', currLevel->ChooseShape());

	g->CreateNewShape(currLevel->ChooseShape(), currLevel->CurrentLevel());

	cout << *g;

	ReadCommands(cin);

	delete currLevel;

	return 0;	
}


// Takes in a string and removes the digits at the beginning of the string
// and converts it to lower case.
void GetCommand(string &command){
	// Finding index where command actually starts
	int commandStartIndex = 0;
	for(commandStartIndex; command[commandStartIndex] != '\0'; ++commandStartIndex){
		if(command[commandStartIndex] > 57 || // If command[commandStartIndex] isn't a 
			command[commandStartIndex] < 48){ // digit, then break
			break;
		}
	}

	// Removing the digits at the beginning
	command = command.substr(commandStartIndex);

	// Convert String to upper case.
	for(int i=0; i<command.length(); ++i)
		if(command[i]<='z' && command[i]>='a')
    		command[i] = command[i]+('Z'-'z');
}

int findScore(vector<std::vector<char>> b, int r){
	if(b[17][3] != ' ')
		return 10;

	else return 0;
}

double coefficients[] = {3, -0.1, -7, -3.5, 8}; // standard deviation, max height, number of holes, 
											// number of blockades, num lines cleared

int calculateFitness(vector<vector<char>> board, const int numCleared) {
	double average = 0;
	int maxHeight = 0;
	int numHoles = 0;
	int height = board.size();
	int width = board[0].size();
	vector<int> colHeights;
	for (int i = 0; i < width; i++) {
		bool startCounting = false;
		int currHeight = 0;
		for (int j = 0; j < height; j++) {
			if (board[j][i]) startCounting = true;
			if (startCounting) {
				currHeight++;
				if (board[j][i] == false) {
					numHoles++;
				}
			}
		}
		colHeights.push_back(currHeight);
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
		}
		average += currHeight;
	}
	average /= width;
	double averageSquaresDiff = 0;
	for (int i = 0; i < width; i++) {
		averageSquaresDiff += pow(colHeights[i] - average, 2);
	}
	averageSquaresDiff /= width;
	double SD = sqrt(averageSquaresDiff);

	int numBlockades = 0;
	for (int i = 0; i < width; i++) {
		bool startCounting = false;
		for (int j = height - 1; j >= 0; j--) {
			if (board[j][i] == 0) startCounting = true;
			if (startCounting && board[j][i] == true) {
				numBlockades++;
			}
		}
	}

	return coefficients[0] * SD + 
		coefficients[1] * maxHeight + 
		coefficients[2] * numHoles + 
		coefficients[3] * numBlockades + 
		coefficients[4] * numCleared;
}



// Reads in commands (from stdin/file) and calls InterpretCommands on each command
void ReadCommands(istream &in){
	int numRotate = 4;

	while(1){
		int maxFitness = 0;
		int maxFitnessRight = 0;
		int maxFitnessRotate = 0;
		for(int i=0; i<g->NUM_COLS-1; ++i){ // width can never be less than 1
			for(int j=0; j<numRotate; ++j){
				Grid tempGrid(g->NUM_ROWS, g->NUM_COLS, true);

				tempGrid = (*g);


				for(int k=0;k<j; ++k){
					tempGrid.RotateClockwise();
					cout << (*g) << tempGrid;
				}
				for(int k=0;k<i; ++k){
					tempGrid.TranslateWindowRight();
					cout << (*g) << tempGrid;
				}


				int rowsClearedNow = tempGrid.DropWindow(currLevel->CurrentLevel());
				cout << (*g) << tempGrid;
				int score = calculateFitness(tempGrid.td->allLetters, rowsClearedNow);
				std::cout <<  "score: " << score;
				// int x; 
				// cin>>x;
				if(score > maxFitness){
					maxFitness = score;
					maxFitnessRight = i;
					maxFitnessRotate = j;
				}
			}

		}

		for(int i=0; i<maxFitnessRight; ++i){
			g->TranslateWindowRight();
			cout << (*g);
		}
		for(int i=0; i<maxFitnessRotate; ++i){
			g->RotateClockwise();
			cout << (*g);
		}

		g->DropWindow(currLevel->CurrentLevel());
		std::cout << *g;
		int x; 
		cin>>x;

		bool hasCreatedNewShape = g->CreateNewShape(currLevel->ChooseShape(), currLevel->CurrentLevel());


		if(hasCreatedNewShape == false){
			std::cout << "Game over, hit anything to break out!!";
			int a; 
			cin>>a;
			break;
		}

		cout << *g;
		// createNextStates
		// 	for each createNextState 
		// 		calculate fitness
		// if(gameOver in all cases) int a; cin >> a; break;
		// make maxfitness Move


	}
}

void Restart() {
	if(norandomSequenceIndex != 0){
		norandomSequenceIndex = 1;
	}

	g->ClearGrid();

	delete currLevel;

	currLevel = new Level0;

	for (int j = 0; j < startLevel; ++j) {
		currLevel = PlusPlus(currLevel);
	}

	g->SetShapes(' ', currLevel->ChooseShape());

	g->CreateNewShape(currLevel->ChooseShape(), currLevel->CurrentLevel());
}

// Takes in a string and performs actions on grid, based on value of string
void InterpretCommand(const string &command){	
	if(command == "LEFT"){ g->TranslateWindowLeft(); }
	else if(command == "RIGHT"){ g->TranslateWindowRight(); }
	else if(command == "DOWN"){ g->TranslateWindowDown(); }
	else if(command == "DROP"){
		int rowsDeleted = g->DropWindow(currLevel->CurrentLevel());

		bool hasRowDeleted;
		if(rowsDeleted > 0 ) bool hasRowDeleted = true;
		if (hasRowDeleted == true) {
			currLevel->ResetStarCounter();
		} else {
			currLevel->IncrementCounter(*g);
		}

		bool hasCreatedNewShape = g->CreateNewShape(currLevel->ChooseShape(), currLevel->CurrentLevel());

		if (hasCreatedNewShape == false) {
			Restart();
		}
	}
	else if(command == "LEVELUP"){ currLevel = PlusPlus(currLevel); }
	else if(command == "LEVELDOWN"){ currLevel = MinusMinus(currLevel); }
	else if(command == "CLOCKWISE"){ g->RotateClockwise(); }
	else if(command == "COUNTERCLOCKWISE"){ g->RotateCounterClockwise(); }
	else if(command == "I"){ g->ChangeShape('I'); }
	else if(command == "J"){ g->ChangeShape('J'); }
	else if(command == "L"){ g->ChangeShape('L'); }
	else if(command == "O"){ g->ChangeShape('O'); }
	else if(command == "T"){ g->ChangeShape('T'); }
	else if(command == "S"){ g->ChangeShape('S'); }
	else if(command == "Z"){ g->ChangeShape('Z'); }
	else {cout << "Invalid Command." << endl; } // this should NEVER run
}


