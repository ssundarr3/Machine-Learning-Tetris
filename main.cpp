#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "board.h"
#include <iostream>
#include <time.h>       /* time */
<<<<<<< HEAD



=======
#include <unordered_map>
#include <limits.h>
>>>>>>> origin/master
using namespace std;

/** Global Variables **/
string pieces = "";
Board board(10, 20);

<<<<<<< HEAD
char generatePiece() {
	int pieceID = rand() % 7;
	char piece;
	switch (pieceID) {
		case 0:
			piece = 'I'; //cyan I-block
			break;
		case 1:
			piece = 'Z'; //red
			break;
		case 2:
			piece = 'S'; //green
			break;
		case 3:
			piece = 'O'; //yellow square
			break;
		case 4:
			piece = 'L'; //orange
			break;
		case 5:
			piece = 'J'; //blue
			break;
		case 6:
			piece = 'T'; //purple T-block
			break;
	}
	pieces = pieces + piece;
	return piece;
}


void printBoard(Board b) {
	cout << "____________" << endl;
	for (int i = 0; i < 20; i++) {
		cout << "|";
		for (int j = 0; j < 10; j++) {
			if (b.grid[i][j]) {
				cout << 'X';
=======

// char represents a character
// vector.size() represents the number of rotations possible
// vector[2] represents the number of 'rights' there are in the second rotation
unordered_map<char, vector<vector<vector<int>>>> P; 

void initialize(){
	P['O'] = {
		{
			{1,1},
			{1,1}
		}
	};

	P['I'] = {
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

	P['J'] = {
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

	P['L'] = {
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

	P['S'] = {
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

	P['T'] = {
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

	P['Z'] = {
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


int removeClears(Board * b) {
	int clears = 0;
	for (int i = 0; i < b->height; i++) {
		int sum = 0;
		for (int j = 0; j < b->width; j++) {
			sum += b->grid[i][j];
		}
		if (sum == b->width) {
			clears++;
			b->score++;
			for (int m = i; m > 0; m--) {
				b->grid[m] = b->grid[m - 1];
>>>>>>> origin/master
			}
			for (int m = 0; m < b->width; m++) {
				b->grid[0][m] = false;
			}
			i++;
		}
<<<<<<< HEAD
		cout << "|" << endl;
	}
	cout << "____________" << endl;
}

void compareFitness(char c, int maxWidth, int rotation, double& mFitness, int& mPosition, int& mRotation) {
	for (int i = 0; i <= maxWidth; i++) {
		double curr = board.addPiece(board, c, i, rotation);
		if (curr > mFitness) {
			mFitness = curr;
			mPosition = i;
			mRotation = rotation;
		}
	}
}

bool gameLost(vector<bool> row) {
	for (int i = 0; i < row.size(); i++) {
		if (row[i] == true) {
			return true;
		}
	}
	return false;
}

int runGame() {
	while (true) {
		char c = generatePiece();
		double maxFitness = -1000000;
		int maxPosition = -1;
		int maxRotation = -1;
		if (c == 'I') {
			compareFitness(c, 9, 1, maxFitness, maxPosition, maxRotation);
			compareFitness(c, 6, 2, maxFitness, maxPosition, maxRotation);
		}
		else if (c == 'O') {
			compareFitness(c, 8, 1, maxFitness, maxPosition, maxRotation);
		}
		else if (c == 'S' || c == 'Z') {
			compareFitness(c, 8, 1, maxFitness, maxPosition, maxRotation);
			compareFitness(c, 7, 2, maxFitness, maxPosition, maxRotation);
		}
		else if (c == 'T' || c == 'L' || c == 'J') {
			compareFitness(c, 8, 1, maxFitness, maxPosition, maxRotation);
			compareFitness(c, 7, 2, maxFitness, maxPosition, maxRotation);
			compareFitness(c, 8, 3, maxFitness, maxPosition, maxRotation);
			compareFitness(c, 7, 4, maxFitness, maxPosition, maxRotation);
		}
		board.addPiece(&board, c, maxPosition, maxRotation);
		//printBoard(board);
		if (gameLost(board.grid[0])) {
		//	cout << "You lose!!!" << endl;
			cout << "Final score: " << board.score << endl;
		//	cout << "Piece progression: " << pieces << endl;
			break;
		}
	}
	pieces = "";
	int sc = board.score;
	board.init();
	return sc;
}

int main() {
	int timeSeed = time(NULL);
	int asdf;
	cin >> asdf;
	
	int score1 = 0;
	int score2 = 0;
	double coefficient1[4];
	double coefficient2[4];
	updateCoefficients(0, -0.2);
	updateCoefficients(1, -0.2);
	updateCoefficients(2, -0.2);
	updateCoefficients(3, -0.2);
	for (int a = 0; a < 3; a++) {
		updateCoefficients(0, 0.1);
		for (int b = 0; b < 3; b++) {
			updateCoefficients(1, 0.1);
			for (int c = 0; c < 3; c++) {
				updateCoefficients(2, 0.1);
				for (int d = 0; d < 3; d++) {
					updateCoefficients(3, 0.1);
					
					srand(timeSeed);
					int newScore = runGame();
					if (newScore > score1) {
						score2 = score1;
						score1 = newScore;
						for (int i = 0; i < 4; i++) {
							coefficient2[i] = coefficient1[i];
							coefficient1[i] = getCoefficient(i);
						}
					}
					else if (newScore > score2) {
						score2 = newScore;
						for (int i = 0; i < 4; i++) {
							coefficient2[i] = getCoefficient(i);
						}
					}
				}
				updateCoefficients(3, -0.3);
			}
			updateCoefficients(2, -0.3);
		}
		updateCoefficients(1, -0.3);
	}
	
	cout << "Highest score: " << score1 << endl;
	cout << "Next Highest Score: " << score2 << endl;
	cout << "Coefficient 1: " << endl;
	cout << "   ";
	for (int i = 0; i < 4; i++) {
		cout << coefficient1[i] << " " << endl;
	}
	cout << "Coefficient 2: " << endl;
	cout << "   ";
	for (int i = 0; i < 4; i++) {
		cout << coefficient2[i] << " " << endl;
	}

	int asdff = 0;
	cin >> asdff;
=======
	}
	return clears;
}


int calculateFitness(Board board) {
	int numCleared = removeClears(&board);
	double average = 0;
	int maxHeight = 0;
	int numHoles = 0;
	int lastHeight;
	int heightDifferences = 0;
	vector<int> colHeights;
	for (int i = 0; i < board.width; i++) {
		bool startCounting = false;
		int currHeight = 0;
		for (int j = 0; j < board.height; j++) {
			if (board.grid[j][i]) startCounting = true;
			if (startCounting) {
				currHeight++;
				if (board.grid[j][i] == false) {
					numHoles++;
				}
			}
		}
		///////////////////////////////////////////////
		if (i == 0) lastHeight = currHeight;
		heightDifferences += abs(currHeight - lastHeight);
		lastHeight = currHeight;
		//////////////////////////////////////////////
		colHeights.push_back(currHeight);
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
		}
		average += currHeight;
	}
	//average /= board.width;
	double averageSquaresDiff = 0;
	for (int i = 0; i < board.width; i++) {
		averageSquaresDiff += pow(colHeights[i] - average, 2);
	}
	averageSquaresDiff /= board.width;
	double SD = sqrt(averageSquaresDiff);

	int numBlockades = 0;
	for (int i = 0; i < board.width; i++) {
		bool startCounting = false;
		for (int j = board.height - 1; j >= 0; j--) {
			if (board.grid[j][i] == 0) startCounting = true;
			if (startCounting && board.grid[j][i] == true) {
				numBlockades++;
			}
		}
	}
	/*
	return coefficients[0] * SD +
		coefficients[1] * heightDifferences+
		coefficients[2] * numHoles +   
		coefficients[3] * numBlockades +
		coefficients[4] * numCleared +
		coefficients[5] * maxHeight ;*/
	double a = average;
	double b = numCleared;
	double c = numHoles;
	double d = heightDifferences;
	double e = maxHeight;
	return e * -1 + b * 0.76 + c * -0.35 + d * -0.18;
}


double dropPieceReturnFitness(Board b, vector<vector<int>> &pieceToDrop, int positionToDrop){
	int i;
	bool placePiece = true;
	for(i=b.grid.size()-pieceToDrop.size(); i >= 0; --i){
		for(int j=0; j<pieceToDrop.size(); ++j){
			if(!placePiece) break;
			for(int k=0; k<pieceToDrop[0].size(); ++k){
				if(b.grid[i+j][i+k] == true){
					placePiece = false;
					break;
				}
			}
		}
		if(placePiece) break;
	}

	// game is over
	if(!placePiece) return INT_MIN; // this results in a game over... 

	for(int j=0; j<pieceToDrop.size(); ++j){
		for(int k=0; k<pieceToDrop[0].size(); ++k){
			if(pieceToDrop[j][k]){
				b.grid[i+j][i+k] = true;
			}
		}
	}
	return (calculateFitness(b));
}


bool dropPieceReturnFitness(Board *b, vector<vector<int>> &pieceToDrop, int positionToDrop){
	int i;
	bool placePiece = true;
	std::cout << "dropPiece1\n";
	for(i=b->grid.size()-pieceToDrop.size(); i >= 0; --i){
		for(int j=0; j<pieceToDrop.size(); ++j){
			if(!placePiece) break;
			for(int k=0; k<pieceToDrop[0].size(); ++k){
				if(b->grid[i+j][i+k] == true){
					placePiece = false;
					break;
				}
			}
		}
		if(placePiece) break;
	}

	std::cout << "dropPiece1\n";


	if(!placePiece) return true;
	for(int j=0; j<pieceToDrop.size(); ++j){
		for(int k=0; k<pieceToDrop[0].size(); ++k){
			if(pieceToDrop[j][k]){
				b->grid[i+j][i+k] = true;
			}
		}
	}
	return false;
}






char generatePiece(){
	int pieceID = rand() % 7;
	if(pieceID == 0){ return 'I'; } //cyan I-block
	if(pieceID == 1){ return 'Z'; } //red
	if(pieceID == 2){ return 'S'; } //green
	if(pieceID == 3){ return 'O'; } //yellow square
	if(pieceID == 4){ return 'L'; } //orange
	if(pieceID == 5){ return 'J'; } //blue
	if(pieceID == 6){ return 'T'; } //purple T-block
}








void printBoard(Board b) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (b.grid[i][j]) {
				cout << 'X';
			} 
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}



int main() {
	srand(time(NULL));
	initialize();
	int xx = 0;
	while (true) {
		char c = generatePiece();
		// double calculateFitness(Board);
		vector<vector<vector<int>>> pieces = P[c];

		double maxFitness = 0, fitness = 0;
		int rotNum, rigNum;

		// pieces.size() is the number of rotations
		for(int i=0; i<pieces.size(); ++i){
			// numRights is the cols - (max-width of pieces[rotation]) + 1
			int numRights = board.width - pieces[i][0].size() + 1;
			for(int j=0; j<numRights; ++j){
				fitness = dropPieceReturnFitness(board, pieces[i], j);
				std::cout << fitness;
				if(fitness > maxFitness){
					maxFitness = fitness;
					rotNum = i; rigNum = j;
				}
			}
		}

		// make move on b
		printBoard(board);
		std::cout << "board here...\n";
		bool gameLost = dropPieceReturnFitness(&board, pieces[rotNum], rigNum);		

		if(gameLost){
			cout << "You lose!!!" << endl;
			cout << "Final score: " << board.score;
			cout << endl;
			gameLost = true;
			break;
		}
	}
>>>>>>> origin/master
}
		// int maxFitness = INT_MIN;
		// int maxPosition = -1;
		// int maxRotation = -1;
		// if (c == 'I') {
		// 	for (int i = 0; i <= 9; i++) {
		// 		int curr = board.addPiece(board, c, i, 1);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 1;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 6; i++) {
		// 		int curr = board.addPiece(board, c, i, 2);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 2;
		// 		}
		// 	}
		// }
		// else if (c == 'O') {
		// 	for (int i = 0; i <= 8; i++) {
		// 		int curr = board.addPiece(board, c, i, 1);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 1;
		// 		}
		// 	}
		// }
		// else if (c == 'S' || c == 'Z') {
		// 	for (int i = 0; i <= 8; i++) {
		// 		int curr = board.addPiece(board, c, i, 1);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 1;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 7; i++) {
		// 		int curr = board.addPiece(board, c, i, 2);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 2;
		// 		}
		// 	}
		// }
		// else if (c == 'T' || c == 'L' || c == 'J') {
		// 	for (int i = 0; i <= 8; i++) {
		// 		int curr = board.addPiece(board, c, i, 1);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 1;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 7; i++) {
		// 		int curr = board.addPiece(board, c, i, 2);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 2;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 8; i++) {
		// 		int curr = board.addPiece(board, c, i, 3);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 3;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 7; i++) {
		// 		int curr = board.addPiece(board, c, i, 4);
		// 		if (curr > maxFitness) {
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 4;
		// 		}
		// 	}
		// }
		// //////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// bool largestIsD = false;
		// char d = generatePiece();
		// if (d == 'I') {
		// 	for (int i = 0; i <= 9; i++) {
		// 		int curr = board.addPiece(board, d, i, 1);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 1;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 6; i++) {
		// 		int curr = board.addPiece(board, d, i, 2);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 2;
		// 		}
		// 	}
		// }
		// else if (d == 'O') {
		// 	for (int i = 0; i <= 8; i++) {
		// 		int curr = board.addPiece(board, d, i, 1);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 1;
		// 		}
		// 	}
		// }
		// else if (d == 'S' || d == 'Z') {
		// 	for (int i = 0; i <= 8; i++) {
		// 		int curr = board.addPiece(board, d, i, 1);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 1;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 7; i++) {
		// 		int curr = board.addPiece(board, d, i, 2);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 2;
		// 		}
		// 	}
		// }
		// else if (d == 'T' || d == 'L' || d == 'J') {
		// 	for (int i = 0; i <= 8; i++) {
		// 		int curr = board.addPiece(board, d, i, 1);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 1;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 7; i++) {
		// 		int curr = board.addPiece(board, d, i, 2);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 2;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 8; i++) {
		// 		int curr = board.addPiece(board, d, i, 3);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 3;
		// 		}
		// 	}
		// 	for (int i = 0; i <= 7; i++) {
		// 		int curr = board.addPiece(board, d, i, 4);
		// 		if (curr > maxFitness) {
		// 			largestIsD = true;
		// 			maxFitness = curr;
		// 			maxPosition = i;
		// 			maxRotation = 4;
		// 		}
		// 	}
		// }
		// if (largestIsD) {
		// 	c = d;
		// }
		// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// board.addPiece(&board, c, maxPosition, maxRotation);
		
/*
void rotate(string piece) {

}

void permuteDrops(string piece) {

}

void updateFittestMove(int newFitness) {

}

void addPiece(Board boardCopy, char piece, int position) {

}

int main() {
	while (true) {
		// generate Piece
		void rotate();
		void dropin9();
		char piece = generatePiece();
		char BestPiece;
		int bestPosition;
		for (int position = 1; position < 9; position++) {
			addPiece(board, piece, position);
		}
		updateScore();
		if (gameOver()) {
			break;
		}




		findTopFitnessMove() {
			if (new > old) {
				old = new;
			}
		}
	}
}*/
