#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

// GLOBAL variables are in caps
// B is our board
vector<vector<char>> B;
int R = 20, C = 10;

// PMap is a hashmap of a character to a vector of rotations of that piece
unordered_map<char, vector<vector<vector<bool>>>> PMap;
// PChar is a vector of all our pieces ('I', 'O' ...)
vector<char> PChar;
int PNum;

int main(){


	return 0;
}



// A function to initialize global variables
void initialize(){
	// functions used here
	void reserve(vector<vector<char>>);
	void setPieces();

	// Reserve space for B
	reserve(B);

	// Set pieces used
	setPieces();

	// Setting the seed
	srand(time(NULL));
}

// Reserves R rows and C cols for v 
void reserveSpace(vector<vector<char>> &v){
	v.reserve(R);
	for(int i=0; i<R; ++i) v[i].reserve(C);
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
void printBoard(vector<vector<char>> &v){
	for(int i=0; i<C+2; ++i) cout << "_";
	cout << endl;
	for (int i = 0; i<R; i++) {
		cout << "|";
		for (int j = 0; j<C; j++) {
			if (v[i][j]){cout << 'X';}
			else {cout << ' ';}
		}
		cout << "|" << endl;
	}
	for(int i=0; i<C+2; ++i) cout << "_";
	cout << endl;
}

// // Drops piece at location row, col
// void dropPieceAtLocation