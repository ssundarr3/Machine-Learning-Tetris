#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "board.cpp"
#include <iostream>

using namespace std;

/** Global Variables **/
double coefficients[] = { 3, -0.1, -7, -3.5, 8 }; // standard deviation, max height, number of holes, 
											// number of blockades, num lines cleared
Board board(10, 20);

char generatePiece() {
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

int calculateFitness(Board board, const int numCleared) {
	double average = 0;
	int maxHeight = 0;
	int numHoles = 0;
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
		colHeights.push_back(currHeight);
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
		}
		average += currHeight;
	}
	average /= board.width;
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

	return coefficients[0] * SD + 
		coefficients[1] * maxHeight + 
		coefficients[2] * numHoles + 
		coefficients[3] * numBlockades + 
		coefficients[4] * numCleared;
}

int main() {
	board.addPiece('O', 4, 2);
	board.addPiece('L', 3, 1);
	board.addPiece('L', 4, 2);
	board.addPiece('L', 4, 3);
	board.addPiece('L', 4, 4);

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (board.grid[i][j]) {
				cout << 'X';
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
	cout << calculateFitness(board, 5);


	int x;
	cin >> x;
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
