#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "board.h"
#include <iostream>
#include <time.h>       /* time */


using namespace std;

/** Global Variables **/
Board board(10, 20);

char generatePiece() {
	srand(time(NULL));
	int pieceID = rand() % 7;
	switch (pieceID) {
		case 0:
			return 'I'; //cyan I-block
		case 1:
			return 'Z'; //red
		case 2:
			return 'S'; //green
		case 3:
			return 'O'; //yellow square
		case 4:
			return 'L'; //orange
		case 5:
			return 'J'; //blue
		case 6:
			return 'T'; //purple T-block
	}
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
	int asdf;
	cin >> asdf;
	int xx = 0;
	while (true) {
		char c = generatePiece();
		int maxFitness = -1000000;
		int maxPosition = -1;
		int maxRotation = -1;
		if (c == 'I') {
			for (int i = 0; i <= 9; i++) {
				int curr = board.addPiece(board, c, i, 1);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 1;
				}
			}
			for (int i = 0; i <= 6; i++) {
				int curr = board.addPiece(board, c, i, 2);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 2;
				}
			}
		}
		else if (c == 'O') {
			for (int i = 0; i <= 8; i++) {
				int curr = board.addPiece(board, c, i, 1);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 1;
				}
			}
		}
		else if (c == 'S' || c == 'Z') {
			for (int i = 0; i <= 8; i++) {
				int curr = board.addPiece(board, c, i, 1);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 1;
				}
			}
			for (int i = 0; i <= 7; i++) {
				int curr = board.addPiece(board, c, i, 2);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 2;
				}
			}
		}
		else if (c == 'T' || c == 'L' || c == 'J') {
			for (int i = 0; i <= 8; i++) {
				int curr = board.addPiece(board, c, i, 1);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 1;
				}
			}
			for (int i = 0; i <= 7; i++) {
				int curr = board.addPiece(board, c, i, 2);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 2;
				}
			}
			for (int i = 0; i <= 8; i++) {
				int curr = board.addPiece(board, c, i, 3);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 3;
				}
			}
			for (int i = 0; i <= 7; i++) {
				int curr = board.addPiece(board, c, i, 4);
				if (curr > maxFitness) {
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 4;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*bool largestIsD = false;
		char d = generatePiece();
		if (d == 'I') {
			for (int i = 0; i <= 9; i++) {
				int curr = board.addPiece(board, d, i, 1);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 1;
				}
			}
			for (int i = 0; i <= 6; i++) {
				int curr = board.addPiece(board, d, i, 2);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 2;
				}
			}
		}
		else if (d == 'O') {
			for (int i = 0; i <= 8; i++) {
				int curr = board.addPiece(board, d, i, 1);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 1;
				}
			}
		}
		else if (d == 'S' || d == 'Z') {
			for (int i = 0; i <= 8; i++) {
				int curr = board.addPiece(board, d, i, 1);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 1;
				}
			}
			for (int i = 0; i <= 7; i++) {
				int curr = board.addPiece(board, d, i, 2);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 2;
				}
			}
		}
		else if (d == 'T' || d == 'L' || d == 'J') {
			for (int i = 0; i <= 8; i++) {
				int curr = board.addPiece(board, d, i, 1);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 1;
				}
			}
			for (int i = 0; i <= 7; i++) {
				int curr = board.addPiece(board, d, i, 2);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 2;
				}
			}
			for (int i = 0; i <= 8; i++) {
				int curr = board.addPiece(board, d, i, 3);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 3;
				}
			}
			for (int i = 0; i <= 7; i++) {
				int curr = board.addPiece(board, d, i, 4);
				if (curr > maxFitness) {
					largestIsD = true;
					maxFitness = curr;
					maxPosition = i;
					maxRotation = 4;
				}
			}
		}
		if (largestIsD) {
			c = d;
		}*/
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		board.addPiece(&board, c, maxPosition, maxRotation);
		printBoard(board);
		bool gameLost = false;
		for (int i = 0; i < board.width; i++) {
			if (board.grid[0][i] == true) {
				cout << "You lose!!!" << endl;
				cout << "Final score: " << board.score;
				cout << endl;
				gameLost = true;
			}
		}
		if (gameLost) break;
	}
	cin >> xx;
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
