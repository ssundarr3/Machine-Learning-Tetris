#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
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


int main(){
	// Function prototypes
	void initialize();
	void printBoard(const vector<vector<char>> &v);
	bool dropPieceAtCol(vector<vector<char>>& v, const int& col, const int& c, const int& rot);
	int removeClears(vector<vector<char>>& v);


	// Set PMap, PChar, PNum, B
	initialize();
	// printBoard(B);



	dropPieceAtCol(B, 6, 'I', 1);
	dropPieceAtCol(B, 4, 'O', 0);
	dropPieceAtCol(B, 0, 'I', 1);
	dropPieceAtCol(B, 2, 'J', 1);

	dropPieceAtCol(B, 6, 'I', 1);

	dropPieceAtCol(B, 4, 'O', 0);

	dropPieceAtCol(B, 0, 'I', 1);


	removeClears(B);


	printBoard(B);

	return 0;
}

// int runSimulation(){
// 	while(1){
// 		bool isGameOver = true;
// 		if(isGameOver){
// 			cout << "Game Over!\n";
// 			cout << "Lines Cleard: " << L << "\n";
// 			// cout << "Num "; // Perhaps number of doubles, triples....
// 			break;
// 		}
// 	}
// }

// 
// int dropPieceAndDeleteRow(vector<vector<char>>& v,)


// Removes completed row and returns number of rows deleted
// int removeCompletedRow(vector<vector<char>>& v, const int& row, const int& c, const int& rot){
// 	vector<vector<char>> pieceVector = PMap[c][rot];

// 	for(int i=row, int j=pieceVector.size()-1; j>=0; --j, ++i){
// 		bool rowCompleted = true;
// 		for(int k=0; k<C; ++k){
// 			if(v[i][k] == ' '){
// 				rowCompleted = false;
// 				break;
// 			}
// 		}
// 		if(rowCompleted){
// 			v.erase(i);
// 		}
// 	}

// 	return();
// }


// Ray's clear Row
// can be improved by only checking rows that the last piece was inserted in !!
int removeClears(vector<vector<char>>& v) {
	int clears = 0;
	for (int i=0; i<R; ++i){
		int sum = 0;
		for (int j=0; j<C; ++j){
			sum += (v[i][j] == ' ' ? 0 : 1);
		}
		if (sum == C) {
			clears++;
			for (int m = i; m > 0; m--) {
				v[m] = v[m - 1];
			}
			for (int m = 0; m < C; m++) {
				v[0][m] = ' ';
			}
			i++;
		}
	}
	return clears;
}

// Drop piece at location (can be improved with hashmap of heights !! )
bool dropPieceAtCol(vector<vector<char>>& v, const int& col, const int& c, const int& rot){
	// function prototypes
	void dropPieceAt(vector<vector<char>>& v, const int& row, const int& col, const char& c, const int& rot);
	bool canDropPieceAt(vector<vector<char>>& v, const int& row, const int& col, const char& c, const int& rot);

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
bool canDropPieceAt(vector<vector<char>>& v, const int& row, const int& col, const char& c, const int& rot){
	vector<vector<int>>& pieceVector = PMap[c][rot];

	for(int i=0; i<pieceVector.size(); ++i){
		for(int j=0; j<pieceVector[i].size(); ++j){
			if(pieceVector[i][j] && v[row+i][col+j] != ' ') return false;
		}
	}
	return true;
}

// Drops piece at location row, col with character pieceChar, rotation rot
void dropPieceAt(vector<vector<char>>& v, const int& row, const int& col, const char& c, const int& rot){
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
	H.reserve(C);
	// Initializing Heights
	for(int i=0; i<C; ++i) H[i] = 0;

	// Set pieces used
	setPieces();

	// Setting the seed
	srand(time(NULL));
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
	for(int i=0; i<C+2; ++i) cout << "_";
	cout << endl;
	for (int i = 0; i<R; i++) {
		cout << "|";
		for (int j = 0; j<C; j++) {
			cout << v[i][j];
		}
		cout << "|" << endl;
	}
	for(int i=0; i<C+2; ++i) cout << "_";
	cout << endl;
}

