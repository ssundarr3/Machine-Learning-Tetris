#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <string>
#include <climits>
using namespace std;

// GLOBAL variables are in caps
// B is our board
vector<vector<char>> B;
int R = 20, C = 10;
// H is a vector of heights of board B
vector<int> H;

// PMap is a hashmap of a character to a vector of rotations of that piece
unordered_map<char, vector<vector<vector<int>>>> PMap;
// PChar is a vector of all our pieces ('I', 'O' ...)
vector<char> PChar;
int PNum;


int seed = 1485360783;


int main(){
	// Function prototypes
	void initialize();
	int runSimulation(vector<vector<char>> board, vector<double>& weights);
		
	seed = time(NULL);
	// Set PMap, PChar, PNum, B
	initialize();

	vector<double> weights = {-3.71, -4.79, -0.2, -1.87};

	runSimulation(B, weights);

	return 0;
}

// Runs the simulation on board board, and using weights 'weights' and returns the _total_ number of lines cleared
int runSimulation(vector<vector<char>> board, vector<double>& weights){
	// function prototypes
	void printBoard(const vector<vector<char>> &v);
	int dropAndRemoveClears(vector<vector<char>>& v, const int col, const char c, const int rot);
	double calculateFitness(vector<vector<char>>& v, const vector<double>& coefficients, const int numCleared);
	char generatePiece();

	int totalLinesCleared = 0;

	while(1){
		bool GameNotOver = true;
		int maxRot = 0, maxRig = 0;
		double maxFitness = INT_MIN;

		char c = generatePiece();
		vector<vector<vector<int>>> pieceRotations = PMap[c];

		// Find maximum fitness
		for(int i=0; i<pieceRotations.size(); ++i){
			int pieceWidth = pieceRotations[i][0].size();
			for(int j=0; j<C-pieceWidth+1; ++j){
				vector<vector<char>> tempBoard = board;

				// rotation i, column j, piece c on tempBoard
				int numCleared = dropAndRemoveClears(tempBoard, j, c, i);

				double fitness;
	
				if(numCleared == -1) fitness = INT_MIN;
				else fitness = calculateFitness(tempBoard, weights, numCleared);


				if(fitness > maxFitness){
					maxFitness = fitness;
					maxRig = j;
					maxRot = i;
				}
			}
		}

		// make max move
		int numCleared = dropAndRemoveClears(board, maxRig, c, maxRot);
		

		if(numCleared == -1){
			cout << "Game Over!\n";
			cout << "Lines Cleard: " << totalLinesCleared << "\n";
			break;
		}

		printBoard(board);
		totalLinesCleared += numCleared;
	}
}

// Calculates fitness
double calculateFitness(vector<vector<char>>& v, const vector<double>& coefficients, const int numCleared){
	int totalHeight = 0;
	int maxHeight = 0;
	int numHoles = 0;
	int lastHeight;
	int heightDifferences = 0;
	vector<int> colHeights;
	for (int i = 0; i < C; i++) {
		bool startCounting = false;
		int currHeight = 0;
		for (int j = 0; j < C; j++) {
			if (v[j][i]) startCounting = true;
			if (startCounting) {
				currHeight++;
				if (v[j][i] == false) {
						numHoles++;
				}
			}
		}

		if (i == 0) lastHeight = currHeight;
		heightDifferences += abs(currHeight - lastHeight);
		lastHeight = currHeight;

		colHeights.push_back(currHeight);
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
		}

		totalHeight += currHeight;
	}
	/*int average = totalHeight / board.width;
	double averageSquaresDiff = 0;
	for (int i = 0; i < board.width; i++) {
		averageSquaresDiff += pow(colHeights[i] - totalHeight, 2);
	}
	averageSquaresDiff /= board.width;
	double SD = sqrt(averageSquaresDiff);*/

	int numBlockades = 0;
	for (int i = 0; i < C; i++) {
		bool startCounting = false;
		for (int j = R - 1; j >= 0; j--) {
			if (v[j][i] == 0) startCounting = true;
			if (startCounting && v[j][i] == true) {
				numBlockades++;
			}
		}
	}
	// coefficients = {"heightDifferences" . "numHoles" . "maxHeight" . "numClears" };
	return coefficients[0] * heightDifferences +
		coefficients[1] * numHoles +
		coefficients[2] * maxHeight +
		coefficients[3] * numCleared;
}

// returns number of lines cleared, -1 if game over
int dropAndRemoveClears(vector<vector<char>>& v, const int col, const char c, const int rot){
	// function prototypes
	bool dropPieceAtCol(vector<vector<char>>& v, const int col, const char c, const int rot);
	int removeClears(vector<vector<char>>& v);

	bool gameNotOver = dropPieceAtCol(v, col, c, rot);

	if(gameNotOver){
		return removeClears(v);
	}
	else return -1;
}

// can be improved by only checking rows that the last piece was inserted in !!
// also by using something other than erase, insert.
int removeClears(vector<vector<char>>& v) {
	// function prototypes
	vector<char> getEmptyRow();

	int clears = 0;
	for(int i=0; i<R; ++i){
		bool rowFull = true;
		for(int j=0; j<C; ++j){
			if(v[i][j] == ' '){
				rowFull = false;
				break;
			}
		}
		if(rowFull){
			clears += 1;
			v.erase(v.begin() + i);
			v.insert(v.begin(), getEmptyRow());
		}
	}

	return clears;

	// Ray's clear Row
	// some bugs !!
	// int clears = 0;
	// for (int i=0; i<R; ++i){
	// 	int sum = 0;
	// 	for (int j=0; j<C; ++j){
	// 		sum += (v[i][j] == ' ' ? 0 : 1);
	// 	}
	// 	if (sum == C) {
	// 		clears++;
	// 		for (int m = i; m > 0; m--) {
	// 			v[m] = v[m - 1];
	// 		}
	// 		for (int m = 0; m < C; m++) {
	// 			v[0][m] = ' ';
	// 		}
	// 		i++;
	// 	}
	// }
	// return clears;
}

// returns a vector of empty chars of length C 
vector<char> getEmptyRow(){
	vector<char> v;
	v.resize(C);
	for(int i=0; i<C; ++i) v[i] = ' ';
	return(v);
}

// Drop piece at location (can be improved with hashmap of heights !! )
bool dropPieceAtCol(vector<vector<char>>& v, const int col, const char c, const int rot){
	// function prototypes

	
	void dropPieceAt(vector<vector<char>>& v, const int row, const int col, const char c, const int rot);
	bool canDropPieceAt(const vector<vector<char>>& v, const int row, const int col, const char c, const int rot);

	vector<vector<int>>& pieceVector = PMap[c][rot];

	for(int i=0; i<=R-pieceVector.size(); ++i){
		if(!canDropPieceAt(v, i, col, c, rot)){
			if(i == 0) return false;
			dropPieceAt(v, i-1, col, c, rot);
			return true;
		}
	}

	if(canDropPieceAt(v, R-pieceVector.size(), col, c, rot)){
		dropPieceAt(v, R-pieceVector.size(), col, c, rot);
		return true;
	}

	return false;
}

// Returns true if piece can be dropped in row, col
bool canDropPieceAt(const vector<vector<char>>& v, const int row, const int col, const char c, const int rot){
	vector<vector<int>>& pieceVector = PMap[c][rot];

	for(int i=0; i<pieceVector.size(); ++i){
		for(int j=0; j<pieceVector[i].size(); ++j){
			if(pieceVector[i][j] && v[row+i][col+j] != ' ') return false;
		}
	}
	return true;
}

// Drops piece at location row, col with character pieceChar, rotation rot
void dropPieceAt(vector<vector<char>>& v, const int row, const int col, const char c, const int rot){
	vector<vector<int>>& pieceVector = PMap[c][rot];

	for(int i=0; i<pieceVector.size(); ++i){
		for(int j=0; j<pieceVector[i].size(); ++j){
			if(pieceVector[i][j]) v[row+i][col+j] = c;
		}
	}
}

// A function to initialize global variables
void initialize(){
	// functions used here
	void reserveSpace(vector<vector<char>>&);
	void setPieces();

	// Reserve space for B
	reserveSpace(B);

	// reserving column space for H
	H.resize(C);
	// Initializing Heights
	for(int i=0; i<C; ++i) H[i] = 0;

	// Set pieces used
	setPieces();

	// Setting the seed
	// seed = time(NULL);
	srand(seed);
}

// Reserves R rows and C cols for v and sets them to ' '
void reserveSpace(vector<vector<char>>& v){
	v.resize(R);
	for(int i=0; i<R; ++i){
		v[i].resize(C);
		for(int j=0; j<C; ++j){
			v[i][j] = ' ';
		}
	}
}

// Sets PNum, PChar, PMap
void setPieces(){
	PChar = {'O', 'I', 'J', 'L', 'S', 'T', 'Z'};
	PNum = PChar.size();

	// Setting Piece Maps
	PMap['O'] = {
		{
			{1,1},
			{1,1}
		}
	};

	PMap['I'] = {
		{
			{1},
			{1},
			{1},
			{1}
		},
		{
			{1,1,1,1}
		}
	};

	PMap['J'] = {
		{
			{0,1},
			{0,1},
			{1,1}
		},
		{
			{1,0,0},
			{1,1,1},
		},
		{
			{1,1},
			{1,0},
			{1,0}
		},
		{
			{1,1,1},
			{0,0,1},
		}
	};

	PMap['L'] = {
		{
			{1,0},
			{1,0},
			{1,1}
		},
		{
			{0,0,1},
			{1,1,1},
		},
		{
			{1,1},
			{0,1},
			{0,1}
		},
		{
			{1,1,1},
			{1,0,0},
		}
	};

	PMap['S'] = {
		{
			{0,1,1},
			{1,1,0}
		},
		{
			{1,0},
			{1,1},
			{0,1}
		}
	};

	PMap['T'] = {
		{
			{0,1,0},
			{1,1,1}
		},
		{
			{1,0},
			{1,1},
			{1,0}
		},
		{
			{1,1,1},
			{0,1,0}
		},
		{
			{0,1},
			{1,1},
			{0,1}
		}
	};

	PMap['Z'] = {
		{
			{1,1,0},
			{0,1,1}
		},
		{
			{0,1},
			{1,1},
			{1,0}
		}
	};
}

// Generates a random piece from PChar
char generatePiece(){
	return (PChar[rand() % PNum]);
}

// Prints the board v
void printBoard(const vector<vector<char>> &v){
	for(int i=0; i<C+2; ++i) cout << "-";
	cout << endl;
	for (int i = 0; i<R; i++) {
		cout << "|";
		for (int j = 0; j<C; j++) {
			cout << v[i][j];
		}
		cout << "|" << endl;
	}
	for(int i=0; i<C+2; ++i) cout << "-";
	cout << endl;
}

