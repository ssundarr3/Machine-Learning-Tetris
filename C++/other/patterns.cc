#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <string>
#include <climits>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;


// !!
// NOTE: R, C, Gen, numWeights, gamesPerWeight, seed changed without breaking the program!
// !!


// -0.294046    -1.3458  0.0847383   0.091462 resulted in 4200 lines
// GLOBAL variables are in caps. 
// B is our board
vector<vector<char>> B;
int R = 50, C = 21;
// H is a vector of heights of board B
vector<int> H;

// current and next piece
char CurrPiece, NextPiece;
bool SecondLevel = false;

// PMap is a hashmap of a character to a vector of rotations of that piece
unordered_map<char, vector<vector<vector<int>>>> PMap;
// PChar is a vector of all our pieces ('I', 'O' ...)
vector<char> PChar;
int PNum;

int seed = 0;

int numGeneration = 10000;
int numWeights = 20;
int gamesPerWeight = 3;
const int numCoefficient = 7;


bool graphics = false;
bool play = false;
bool coefficient = false;


vector<vector<char>> G;

int main(){
	// function prototypes
	void initialize();
	bool createPoint(int loc, char pieceToDrop);
	initialize();

	createPoint(4, 'T');

}


// Drops a single Point
bool createPoint(int loc, char pieceToDrop) {
	// function prototypes
	void printBoard(const vector<vector<char>>&);
	int dropAndRemoveClears(vector<vector<char>>&, const int, const char, const int);
	// bool search(vector<vector<char>>, int);
	vector<vector<int>> search(vector<int>);


	// check left and right for special case 1 (Two L-Pieces)
	// Case 0: loc = 0
	// ...  O-Block on top
	// Case 1: loc = 1
	// ...  Side-T Block
	// Case 2: loc = 2
	// ...  L-J block
	// Case 3: loc = 3
	// ...  Start placing S-Blocks
	//
	// while (not found) { increase size and call <search> to find a solution-matrix {
	// char[][] newMatrix = b * w - 3 = 4n
	// char newMatrix = char[3][21];
	// //TESTING:
	// newMatrix[2][loc] = 'A';
	// newMatrix[2][loc + 1] = 'A';
	// newMatrix[2][loc + 2] = 'A';
	dropAndRemoveClears(B, loc, pieceToDrop, 2);

	vector<vector<char>> matrix;
	// matrix.resize(4);

	// // copy values into matrix
	// for(int i=0; i<4; ++i){
	// 	matrix[i].resize(C);
	// 	for(int j=0; j<C; ++j){
	// 		matrix[i][j] = B[R-4+i][j]; // TESTING< C = 21 >
	// 	}
	// }

	// printBoard(matrix);
	cout << "ASHFUOWQYRIUQWYOIRUYIOQWURYOIQWURIOQWYROIUQWYIORYQWIOE" << endl;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3); 
	search(v);
	cout << "ASHFIUWQYRIOUQWYOI" << endl;
	// search(matrix, B[0].size() * (matrix.size() - 1) - 3);
}

vector<vector<int>> search(vector<int> v) {
	cout << "Entry" << endl;
	v.size();
	cout << "Exit" << endl;
	cout << "Watthefuk" << endl;
	vector<vector<int>> test;
	return test;
}

int attempts = 0;
int maxAttempts = 10000;


// island algorithm
bool countSpaces(vector<vector<char>>& v){

}

// bool validPlacement(int row, int col, vector<vector<char>> v, char c, int rot) {
// 	bool canDropPieceAt(const vector<vector<char>>&, const int, const int, const char, const int);
// 	bool freeLocation = canDropPieceAt(v, row, col, c, rot);

// 	bool hasAnchor = false;
// 	vector<vector<int>>& piece = PMap[c][rot];
// 	for (int row = 0; row < piece.size(); row++) {
// 		for (int col = 0; col < piece[0].size() - 1; col++) {
// 			int diff1 = piece[row][col] - piece[row][col + 1];
			
// 			int diff2 = v[row][col] - v[row][col + 1];
// 		}
// 	}
// }

bool validPlacement(vector<vector<char>> v, int row, int col, char c, int rot){
	bool dropPieceAtCol(vector<vector<char>>& v, const int col, const char c, const int rot);

	// bool dropPieceAtCol(vector<vector<char>>& v, const int col, const char c, const int rot);

	dropPieceAtCol(v, col, c, rot);

	int numAtBottom = 0;
	for(int j=0; j<v[0].size(); ++j){
		if(v[v.size()-1][j] != ' '){
			++numAtBottom;
		}
	}
	if(numAtBottom > 1) return false;

	for(int j=0; j<v[0].size(); ++j){
		bool spaces = false;
		for(int i=0; i<v.size(); ++i){
			if(v[i][j] == ' '){
				spaces = true;
			}
			if(spaces && v[i][j] != ' '){
				return false;
			}
		}
	}

	return true;
}


vector<int> bottomS(const vector<vector<char>>& v){
	void printBoard(const vector<vector<char>> &v);

	vector<int> result;

	for (int col = 0; col < v[0].size(); col++) {

		if (validPlacement(v, v.size() - 3, col, 'S', 0)) {
			result.push_back(col);
		}
	}
	return result;
}

vector<int> bottomZ(const vector<vector<char>>& v){
	vector<int> result;
	for (int col = 0; col < v[0].size(); col++) {
		if (validPlacement(v, v.size() - 3, col, 'Z', 0)){
			result.push_back(col);
		}
	}
	return result;
}


pair<int, char> chooseSZ(const vector<vector<char>>& v){


	vector<int> S = bottomS(v);


	vector<int> Z = bottomZ(v);

	int randomNum = rand() % (S.size() + Z.size()); // returns a number [0, A.size()+Z.size()-1]

	pair<int, char> result;

	if(randomNum >= S.size()){
		result.first = Z[randomNum % S.size()];
		result.second = 'Z';
	}
	else{
		result.first = S[randomNum];
		result.second = 'S';
	}

	return result;
}



// searches a random permutation of of all possible next pieces. 
vector<vector<char>> search(vector<vector<char>> v, int rem) { // (char[][] matrice, char pieceType) { ... }
	
	bool dropPieceAtCol(vector<vector<char>>&, const int, const char, const int);

	// if(rem == 0){
	// 	return v;
	// }

	// attempts += 1;
	// if(attempts > maxAttempts){
	// 	// throw "too many attempts!";
	// 	cout << "Too many attempts" << endl;
	// 	return v;
	// }
	
	cout << "A Peanut" << endl;
	v.push_back({'a'});
	cout << "A" << endl;

	// v.emplace_back('a');
	cout << v.size() << endl;
	cout << "B" << endl;

	pair<int, char> p = chooseSZ(v);
	dropPieceAtCol(v, p.first, p.second, 0);

	p = chooseSZ(v);
	dropPieceAtCol(v, p.first, p.second, 0);

	p = chooseSZ(v);
	dropPieceAtCol(v, p.first, p.second, 0);

	p = chooseSZ(v);
	dropPieceAtCol(v, p.first, p.second, 0);

	return v;
}





// changes current piece
void changeCurrPiece(char newPiece){
	CurrPiece = newPiece;
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
	for(int i=0; i<v.size(); ++i){
		bool rowFull = true;
		for(int j=0; j<v[i].size(); ++j){
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

	for(int i=0; i<=v.size()-pieceVector.size(); ++i){
		if(!canDropPieceAt(v, i, col, c, rot)){
			if(i == 0) return false;
			dropPieceAt(v, i-1, col, c, rot);
			return true;
		}
	}

	if(canDropPieceAt(v, v.size()-pieceVector.size(), col, c, rot)){
		dropPieceAt(v, v.size()-pieceVector.size(), col, c, rot);
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
	void getDataFromFile(vector<vector<char>>&, string);

	// Get Data from file
	// getDataFromFile(G, "filename");

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

void getDataFromFile(vector<vector<char>>& v, string fileName){
	fstream file(fileName);
	string line;
	int i=0;
	while(getline(file, line)){
		v.resize(i+1);
		for(int j=0; j<line.size(); ++j){
			v[i].emplace_back(line[j]);
		}
		++i;
	}
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
	for (int i = 0; i<v.size(); i++) {
		cout << "|";
		for (int j = 0; j<v[i].size(); j++) {
			cout << v[i][j];
		}
		cout << "|" << endl;
	}
	for(int i=0; i<C+2; ++i) cout << "-";
	cout << endl;
}


