#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "board.h"
#include <iostream>
#include <time.h>       /* time */



using namespace std;

/** Global Variables **/
string pieces = "";
Board board(10, 20);

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
			}
			else {
				cout << ' ';
			}
		}
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
}
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
