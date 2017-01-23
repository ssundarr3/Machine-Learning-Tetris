#include <string>
#include <vector>
#include <math.h>

using namespace std;

/*class Board {
public:
	vector<vector<bool>> grid;
	Board() { };
};

Board board;*/
int coefficients[] = { -1, -2, -2, -1, 3 }; // standard deviation, max height, number of holes, number of blockades, num lines cleared

int calculateFitness(vector<vector<bool>> grid, const int numRows, const int numCols, const int numCleared) {
	int average = 0;
	int maxHeight = 0;
	int numHoles = 0;
	vector<int> colHeights;
	for (int i = 0; i < numCols; i++) {
		bool startCounting = false;
		int currHeight = 0;
		for (int j = numRows - j; j >= 0; j--) {
			if (grid[j][i]) startCounting = true;
			if (startCounting) {
				currHeight++;
				if (grid[j][i] == false) {
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
	average /= numCols;
	int averageSquaresDiff = 0;
	for (int i = 0; i < numCols; i++) {
		averageSquaresDiff += pow(colHeights[i] - average, 2);
	}
	averageSquaresDiff /= numCols;
	int SD = sqrt(averageSquaresDiff);

	int numBlockades = 0;
	for (int i = 0; i < numCols; i++) {
		bool startCounting = false;
		for (int j = 0; j < numRows; j++) {
			if (grid[j][i] == 0) startCounting = true;
			if (startCounting && grid[j][i] == true) {
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
}
