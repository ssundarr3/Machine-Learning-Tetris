#include "board.h"

using namespace std;

// global variables
double coefficients[] = { -1, -1, -7.5, -3.5, 8, -1 }; // standard deviation, height Differeces, number of holes, 
												  // number of blockades, num lines cleared, max Height

Board::Board() : width(10), height(20), score(0) {
	for (int i = 0; i < height; i++) {
		vector<bool> row;
		for (int j = 0; j < width; j++) {
			row.push_back(false);
		}
		grid.push_back(row);
	}
}

Board::Board(int w, int h) : width(w), height(h), score(0) {
	for (int i = 0; i < height; i++) {
		vector<bool> row;
		for (int j = 0; j < width; j++) {
			row.push_back(false);
		}
		grid.push_back(row);
	}
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
			}
			for (int m = 0; m < b->width; m++) {
				b->grid[0][m] = false;
			}
			i++;
		}
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


int Board::addPiece(Board b, char piece, int position, char rotation) {
	int row = 0;
	switch (piece) {
	case 'I': {
		if (rotation == 1) { // upright
			b.grid[row][position] = true;
			b.grid[row + 1][position] = true;
			b.grid[row + 2][position] = true;
			b.grid[row + 3][position] = true;
			while (row + 4 < height) {
				if (b.grid[row + 4][position] == false) {
					b.grid[row][position] = false;
					b.grid[row + 4][position] = true;
					row++;
				}
				else {
					break;
				}
			}
		}
		else if (rotation == 2) { // sideways
			if (b.grid[row][position] == true ||
				b.grid[row][position + 1] ||
				b.grid[row][position + 2] ||
				b.grid[row][position + 3]) {
				return -1;
			}
			b.grid[row][position] = true;
			b.grid[row][position + 1] = true;
			b.grid[row][position + 2] = true;
			b.grid[row][position + 3] = true;
			while (row + 1 < height) {
				if (b.grid[row + 1][position] == false &&
					b.grid[row + 1][position + 1] == false &&
					b.grid[row + 1][position + 2] == false &&
					b.grid[row + 1][position + 3] == false) {
					b.grid[row][position] = false;
					b.grid[row][position + 1] = false;
					b.grid[row][position + 2] = false;
					b.grid[row][position + 3] = false;
					row++;
					b.grid[row][position] = true;
					b.grid[row][position + 1] = true;
					b.grid[row][position + 2] = true;
					b.grid[row][position + 3] = true;
				}
				else {
					break;
				}
			}
		}
		break;
	}
	case 'O': {
		b.grid[row][position] = true;
		b.grid[row + 1][position] = true;
		b.grid[row][position + 1] = true;
		b.grid[row + 1][position + 1] = true;
		while (row + 2 < height) {
			if (b.grid[row + 2][position] == false && b.grid[row + 2][position + 1] == false) {
				b.grid[row][position] = false;
				b.grid[row][position + 1] = false;
				b.grid[row + 2][position] = true;
				b.grid[row + 2][position + 1] = true;
				row++;
			}
			else {
				break;
			}
		}
		break;
	}
	case 'L': {
		switch (rotation) {
		case 1: { // X
				  // X
				  // X X
			b.grid[row][position] = true;
			b.grid[row + 1][position] = true;
			b.grid[row + 2][position] = true;
			b.grid[row + 2][position + 1] = true;
			while (row + 3 < height) {
				if (b.grid[row + 3][position] == false && b.grid[row + 3][position + 1] == false) {
					b.grid[row][position] = false;
					b.grid[row + 2][position + 1] = false;
					row++;
					b.grid[row + 2][position] = true;
					b.grid[row + 2][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   //    X X X
					//    X
			b.grid[row][position] = true;
			b.grid[row][position + 1] = true;
			b.grid[row][position + 2] = true;
			b.grid[row + 1][position] = true;
			while (row + 3 < height) {
				if (b.grid[row + 2][position] == false &&
					b.grid[row + 1][position + 1] == false &&
					b.grid[row + 1][position + 2] == false) {
					b.grid[row][position] = false;
					b.grid[row][position + 1] = false;
					b.grid[row][position + 2] = false;
					row++;
					b.grid[row][position + 1] = true;
					b.grid[row][position + 2] = true;
					b.grid[row + 1][position] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 3: {   //    X X
					//      X
					//      X
			b.grid[row][position] = true;
			b.grid[row][position + 1] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row + 2][position + 1] = true;
			while (row + 3 < height) {
				if (b.grid[row + 3][position + 1] == false &&
					b.grid[row + 1][position] == false) {
					b.grid[row][position] = false;
					b.grid[row][position + 1] = false;
					row++;
					b.grid[row][position] = true;
					b.grid[row + 2][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 4: {   //        X
					//    X X X
			b.grid[row][position + 2] = true;
			b.grid[row + 1][position] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row + 1][position + 2] = true;
			while (row + 2 < height) {
				if (b.grid[row + 2][position] == false &&
					b.grid[row + 2][position + 1] == false &&
					b.grid[row + 2][position + 2] == false) {
					b.grid[row][position + 2] = false;
					b.grid[row + 1][position] = false;
					b.grid[row + 1][position + 1] = false;
					row++;
					b.grid[row + 1][position] = true;
					b.grid[row + 1][position + 1] = true;
					b.grid[row + 1][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	case 'J': {
		switch (rotation) {
		case 1: {   //   X
					//   X
					// X X
			b.grid[row][position + 1] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row + 2][position + 1] = true;
			b.grid[row + 2][position] = true;
			while (row + 3 < height) {
				if (b.grid[row + 3][position] == false && b.grid[row + 3][position + 1] == false) {
					b.grid[row][position + 1] = false;
					b.grid[row + 2][position] = false;
					row++;
					b.grid[row + 2][position] = true;
					b.grid[row + 2][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   //  X 
					//  X X X
			b.grid[row][position] = true;
			b.grid[row + 1][position] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row + 1][position + 2] = true;
			while (row + 2 < height) {
				if (b.grid[row + 2][position] == false &&
					b.grid[row + 2][position + 1] == false &&
					b.grid[row + 2][position + 2] == false) {
					b.grid[row][position] = false;
					b.grid[row + 1][position + 1] = false;
					b.grid[row + 1][position + 2] = false;
					row++;
					b.grid[row + 1][position] = true;
					b.grid[row + 1][position + 1] = true;
					b.grid[row + 1][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 3: {   //   X X
					//   X
					//   X
			b.grid[row][position] = true;
			b.grid[row][position + 1] = true;
			b.grid[row + 1][position] = true;
			b.grid[row + 2][position] = true;
			while (row + 3 < height) {
				if (b.grid[row + 3][position] == false &&
					b.grid[row + 1][position + 1] == false) {
					b.grid[row][position] = false;
					b.grid[row][position + 1] = false;
					row++;
					b.grid[row][position + 1] = true;
					b.grid[row + 2][position] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 4: {   //    X X X
					//        X
			b.grid[row][position] = true;
			b.grid[row][position + 1] = true;
			b.grid[row][position + 2] = true;
			b.grid[row + 1][position + 2] = true;
			while (row + 2 < height) {
				if (b.grid[row + 1][position] == false &&
					b.grid[row + 1][position + 1] == false &&
					b.grid[row + 2][position + 2] == false) {
					b.grid[row][position] = false;
					b.grid[row][position + 1] = false;
					b.grid[row][position + 2] = false;
					row++;
					b.grid[row][position] = true;
					b.grid[row][position + 1] = true;
					b.grid[row + 1][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	case 'S': {
		switch (rotation) {
		case 1: {   //  X 
					//  X X 
					//    X
			b.grid[row][position] = true;
			b.grid[row + 1][position] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row + 2][position + 1] = true;
			while (row + 3 < height) {
				if (b.grid[row + 2][position] == false &&
					b.grid[row + 3][position + 1] == false) {
					b.grid[row][position] = false;
					b.grid[row + 1][position] = false;
					b.grid[row + 1][position + 1] = false;
					b.grid[row + 2][position + 1] = false;
					row++;
					b.grid[row][position] = true;
					b.grid[row + 1][position] = true;
					b.grid[row + 1][position + 1] = true;
					b.grid[row + 2][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   //   X X
					// X X
			b.grid[row + 1][position] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row][position + 1] = true;
			b.grid[row][position + 2] = true;
			while (row + 2 < height) {
				if (b.grid[row + 2][position] == false &&
					b.grid[row + 2][position + 1] == false &&
					b.grid[row + 1][position + 2] == false) {
					b.grid[row + 1][position] = false;
					b.grid[row + 1][position + 1] = false;
					b.grid[row][position + 1] = false;
					b.grid[row][position + 2] = false;
					row++;
					b.grid[row + 1][position] = true;
					b.grid[row + 1][position + 1] = true;
					b.grid[row][position + 1] = true;
					b.grid[row][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	case 'Z': {
		switch (rotation) {
		case 1: {   //    X
					//  X X 
					//  X  
			b.grid[row + 2][position] = true;
			b.grid[row + 1][position] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row][position + 1] = true;
			while (row + 3 < height) {
				if (b.grid[row + 3][position] == false &&
					b.grid[row + 2][position + 1] == false) {
					b.grid[row + 2][position] = false;
					b.grid[row + 1][position] = false;
					b.grid[row + 1][position + 1] = false;
					b.grid[row][position + 1] = false;
					row++;
					b.grid[row + 2][position] = true;
					b.grid[row + 1][position] = true;
					b.grid[row + 1][position + 1] = true;
					b.grid[row][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   // X X 
					//   X X
			b.grid[row][position] = true;
			b.grid[row][position + 1] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row + 1][position + 2] = true;
			while (row + 2 < height) {
				if (b.grid[row + 1][position] == false &&
					b.grid[row + 2][position + 1] == false &&
					b.grid[row + 2][position + 2] == false) {
					b.grid[row][position] = false;
					b.grid[row][position + 1] = false;
					b.grid[row + 1][position + 1] = false;
					b.grid[row + 1][position + 2] = false;
					row++;
					b.grid[row][position] = true;
					b.grid[row][position + 1] = true;
					b.grid[row + 1][position + 1] = true;
					b.grid[row + 1][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	case 'T': {
		switch (rotation) {
		case 1: {   //    X 
					//  X X 
					//    X
			b.grid[row][position + 1] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row + 2][position + 1] = true;
			b.grid[row + 1][position] = true;
			while (row + 3 < height) {
				if (b.grid[row + 3][position + 1] == false &&
					b.grid[row + 2][position] == false) {
					b.grid[row][position + 1] = false;
					b.grid[row + 1][position] = false;
					row++;
					b.grid[row + 2][position + 1] = true;
					b.grid[row + 1][position] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   //  X X X
					//    X 
			b.grid[row][position] = true;
			b.grid[row][position + 1] = true;
			b.grid[row][position + 2] = true;
			b.grid[row + 1][position + 1] = true;
			while (row + 2 < height) {
				if (b.grid[row + 1][position] == false &&
					b.grid[row + 2][position + 1] == false &&
					b.grid[row + 1][position + 2] == false) {
					b.grid[row][position] = false;
					b.grid[row][position + 1] = false;
					b.grid[row][position + 2] = false;
					b.grid[row + 1][position + 1] = false;
					row++;
					b.grid[row][position] = true;
					b.grid[row][position + 1] = true;
					b.grid[row][position + 2] = true;
					b.grid[row + 1][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 3: {   //   X 
					//   X X
					//   X
			b.grid[row][position] = true;
			b.grid[row + 1][position] = true;
			b.grid[row + 2][position] = true;
			b.grid[row + 1][position + 1] = true;
			while (row + 3 < height) {
				if (b.grid[row + 3][position] == false &&
					b.grid[row + 2][position + 1] == false) {
					b.grid[row][position] = false;
					b.grid[row + 1][position + 1] = false;
					row++;
					b.grid[row + 2][position] = true;
					b.grid[row + 1][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 4: {   //    X
					//  X X X
			b.grid[row + 1][position] = true;
			b.grid[row + 1][position + 1] = true;
			b.grid[row + 1][position + 2] = true;
			b.grid[row][position + 1] = true;
			while (row + 2 < height) {
				if (b.grid[row + 2][position] == false &&
					b.grid[row + 2][position + 1] == false &&
					b.grid[row + 2][position + 2] == false) {
					b.grid[row + 1][position] = false;
					b.grid[row + 1][position + 1] = false;
					b.grid[row + 1][position + 2] = false;
					b.grid[row][position + 1] = false;
					row++;
					b.grid[row + 1][position] = true;
					b.grid[row + 1][position + 1] = true;
					b.grid[row + 1][position + 2] = true;
					b.grid[row][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	}
	return calculateFitness(b);
}


void Board::addPiece(Board * b, char piece, int position, char rotation) {
	int row = 0;
	switch (piece) {
	case 'I': {
		if (rotation == 1) { // upright
			b->grid[row][position] = true;
			b->grid[row + 1][position] = true;
			b->grid[row + 2][position] = true;
			b->grid[row + 3][position] = true;
			while (row + 4 < height) {
				if (b->grid[row + 4][position] == false) {
					b->grid[row][position] = false;
					b->grid[row + 4][position] = true;
					row++;
				}
				else {
					break;
				}
			}
		}
		else if (rotation == 2) { // sideways
			if (b->grid[row][position] == true ||
				b->grid[row][position + 1] ||
				b->grid[row][position + 2] ||
				b->grid[row][position + 3]) {
				return;
			}
			b->grid[row][position] = true;
			b->grid[row][position + 1] = true;
			b->grid[row][position + 2] = true;
			b->grid[row][position + 3] = true;
			while (row + 1 < height) {
				if (b->grid[row + 1][position] == false &&
					b->grid[row + 1][position + 1] == false &&
					b->grid[row + 1][position + 2] == false &&
					b->grid[row + 1][position + 3] == false) {
					b->grid[row][position] = false;
					b->grid[row][position + 1] = false;
					b->grid[row][position + 2] = false;
					b->grid[row][position + 3] = false;
					row++;
					b->grid[row][position] = true;
					b->grid[row][position + 1] = true;
					b->grid[row][position + 2] = true;
					b->grid[row][position + 3] = true;
				}
				else {
					break;
				}
			}
		}
		break;
	}
	case 'O': {
		b->grid[row][position] = true;
		b->grid[row + 1][position] = true;
		b->grid[row][position + 1] = true;
		b->grid[row + 1][position + 1] = true;
		while (row + 2 < height) {
			if (b->grid[row + 2][position] == false && b->grid[row + 2][position + 1] == false) {
				b->grid[row][position] = false;
				b->grid[row][position + 1] = false;
				b->grid[row + 2][position] = true;
				b->grid[row + 2][position + 1] = true;
				row++;
			}
			else {
				break;
			}
		}
		break;
	}
	case 'L': {
		switch (rotation) {
		case 1: { // X
				  // X
				  // X X
			b->grid[row][position] = true;
			b->grid[row + 1][position] = true;
			b->grid[row + 2][position] = true;
			b->grid[row + 2][position + 1] = true;
			while (row + 3 < height) {
				if (b->grid[row + 3][position] == false && b->grid[row + 3][position + 1] == false) {
					b->grid[row][position] = false;
					b->grid[row + 2][position + 1] = false;
					row++;
					b->grid[row + 2][position] = true;
					b->grid[row + 2][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   //    X X X
					//    X
			b->grid[row][position] = true;
			b->grid[row][position + 1] = true;
			b->grid[row][position + 2] = true;
			b->grid[row + 1][position] = true;
			while (row + 3 < height) {
				if (b->grid[row + 2][position] == false &&
					b->grid[row + 1][position + 1] == false &&
					b->grid[row + 1][position + 2] == false) {
					b->grid[row][position] = false;
					b->grid[row][position + 1] = false;
					b->grid[row][position + 2] = false;
					row++;
					b->grid[row][position + 1] = true;
					b->grid[row][position + 2] = true;
					b->grid[row + 1][position] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 3: {   //    X X
					//      X
					//      X
			b->grid[row][position] = true;
			b->grid[row][position + 1] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row + 2][position + 1] = true;
			while (row + 3 < height) {
				if (b->grid[row + 3][position + 1] == false &&
					b->grid[row + 1][position] == false) {
					b->grid[row][position] = false;
					b->grid[row][position + 1] = false;
					row++;
					b->grid[row][position] = true;
					b->grid[row + 2][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 4: {   //        X
					//    X X X
			b->grid[row][position + 2] = true;
			b->grid[row + 1][position] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row + 1][position + 2] = true;
			while (row + 2 < height) {
				if (b->grid[row + 2][position] == false &&
					b->grid[row + 2][position + 1] == false &&
					b->grid[row + 2][position + 2] == false) {
					b->grid[row][position + 2] = false;
					b->grid[row + 1][position] = false;
					b->grid[row + 1][position + 1] = false;
					row++;
					b->grid[row + 1][position] = true;
					b->grid[row + 1][position + 1] = true;
					b->grid[row + 1][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	case 'J': {
		switch (rotation) {
		case 1: {   //   X
					//   X
					// X X
			b->grid[row][position + 1] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row + 2][position + 1] = true;
			b->grid[row + 2][position] = true;
			while (row + 3 < height) {
				if (b->grid[row + 3][position] == false && b->grid[row + 3][position + 1] == false) {
					b->grid[row][position + 1] = false;
					b->grid[row + 2][position] = false;
					row++;
					b->grid[row + 2][position] = true;
					b->grid[row + 2][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   //  X 
					//  X X X
			b->grid[row][position] = true;
			b->grid[row + 1][position] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row + 1][position + 2] = true;
			while (row + 2 < height) {
				if (b->grid[row + 2][position] == false &&
					b->grid[row + 2][position + 1] == false &&
					b->grid[row + 2][position + 2] == false) {
					b->grid[row][position] = false;
					b->grid[row + 1][position + 1] = false;
					b->grid[row + 1][position + 2] = false;
					row++;
					b->grid[row + 1][position] = true;
					b->grid[row + 1][position + 1] = true;
					b->grid[row + 1][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 3: {   //   X X
					//   X
					//   X
			b->grid[row][position] = true;
			b->grid[row][position + 1] = true;
			b->grid[row + 1][position] = true;
			b->grid[row + 2][position] = true;
			while (row + 3 < height) {
				if (b->grid[row + 3][position] == false &&
					b->grid[row + 1][position + 1] == false) {
					b->grid[row][position] = false;
					b->grid[row][position + 1] = false;
					row++;
					b->grid[row][position + 1] = true;
					b->grid[row + 2][position] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 4: {   //    X X X
					//        X
			b->grid[row][position] = true;
			b->grid[row][position + 1] = true;
			b->grid[row][position + 2] = true;
			b->grid[row + 1][position + 2] = true;
			while (row + 2 < height) {
				if (b->grid[row + 1][position] == false &&
					b->grid[row + 1][position + 1] == false &&
					b->grid[row + 2][position + 2] == false) {
					b->grid[row][position] = false;
					b->grid[row][position + 1] = false;
					b->grid[row][position + 2] = false;
					row++;
					b->grid[row][position] = true;
					b->grid[row][position + 1] = true;
					b->grid[row + 1][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	case 'S': {
		switch (rotation) {
		case 1: {   //  X 
					//  X X 
					//    X
			b->grid[row][position] = true;
			b->grid[row + 1][position] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row + 2][position + 1] = true;
			while (row + 3 < height) {
				if (b->grid[row + 2][position] == false &&
					b->grid[row + 3][position + 1] == false) {
					b->grid[row][position] = false;
					b->grid[row + 1][position] = false;
					b->grid[row + 1][position + 1] = false;
					b->grid[row + 2][position + 1] = false;
					row++;
					b->grid[row][position] = true;
					b->grid[row + 1][position] = true;
					b->grid[row + 1][position + 1] = true;
					b->grid[row + 2][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   //   X X
					// X X
			b->grid[row + 1][position] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row][position + 1] = true;
			b->grid[row][position + 2] = true;
			while (row + 2 < height) {
				if (b->grid[row + 2][position] == false &&
					b->grid[row + 2][position + 1] == false &&
					b->grid[row + 1][position + 2] == false) {
					b->grid[row + 1][position] = false;
					b->grid[row + 1][position + 1] = false;
					b->grid[row][position + 1] = false;
					b->grid[row][position + 2] = false;
					row++;
					b->grid[row + 1][position] = true;
					b->grid[row + 1][position + 1] = true;
					b->grid[row][position + 1] = true;
					b->grid[row][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	case 'Z': {
		switch (rotation) {
		case 1: {   //    X
					//  X X 
					//  X  
			b->grid[row + 2][position] = true;
			b->grid[row + 1][position] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row][position + 1] = true;
			while (row + 3 < height) {
				if (b->grid[row + 3][position] == false &&
					b->grid[row + 2][position + 1] == false) {
					b->grid[row + 2][position] = false;
					b->grid[row + 1][position] = false;
					b->grid[row + 1][position + 1] = false;
					b->grid[row][position + 1] = false;
					row++;
					b->grid[row + 2][position] = true;
					b->grid[row + 1][position] = true;
					b->grid[row + 1][position + 1] = true;
					b->grid[row][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   // X X 
					//   X X
			b->grid[row][position] = true;
			b->grid[row][position + 1] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row + 1][position + 2] = true;
			while (row + 2 < height) {
				if (b->grid[row + 1][position] == false &&
					b->grid[row + 2][position + 1] == false &&
					b->grid[row + 2][position + 2] == false) {
					b->grid[row][position] = false;
					b->grid[row][position + 1] = false;
					b->grid[row + 1][position + 1] = false;
					b->grid[row + 1][position + 2] = false;
					row++;
					b->grid[row][position] = true;
					b->grid[row][position + 1] = true;
					b->grid[row + 1][position + 1] = true;
					b->grid[row + 1][position + 2] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	case 'T': {
		switch (rotation) {
		case 1: {   //    X 
					//  X X 
					//    X
			b->grid[row][position + 1] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row + 2][position + 1] = true;
			b->grid[row + 1][position] = true;
			while (row + 3 < height) {
				if (b->grid[row + 3][position + 1] == false &&
					b->grid[row + 2][position] == false) {
					b->grid[row][position + 1] = false;
					b->grid[row + 1][position] = false;
					row++;
					b->grid[row + 2][position + 1] = true;
					b->grid[row + 1][position] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 2: {   //  X X X
					//    X 
			b->grid[row][position] = true;
			b->grid[row][position + 1] = true;
			b->grid[row][position + 2] = true;
			b->grid[row + 1][position + 1] = true;
			while (row + 2 < height) {
				if (b->grid[row + 1][position] == false &&
					b->grid[row + 2][position + 1] == false &&
					b->grid[row + 1][position + 2] == false) {
					b->grid[row][position] = false;
					b->grid[row][position + 1] = false;
					b->grid[row][position + 2] = false;
					b->grid[row + 1][position + 1] = false;
					row++;
					b->grid[row][position] = true;
					b->grid[row][position + 1] = true;
					b->grid[row][position + 2] = true;
					b->grid[row + 1][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 3: {   //   X 
					//   X X
					//   X
			b->grid[row][position] = true;
			b->grid[row + 1][position] = true;
			b->grid[row + 2][position] = true;
			b->grid[row + 1][position + 1] = true;
			while (row + 3 < height) {
				if (b->grid[row + 3][position] == false &&
					b->grid[row + 2][position + 1] == false) {
					b->grid[row][position] = false;
					b->grid[row + 1][position + 1] = false;
					row++;
					b->grid[row + 2][position] = true;
					b->grid[row + 1][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		case 4: {   //    X
					//  X X X
			b->grid[row + 1][position] = true;
			b->grid[row + 1][position + 1] = true;
			b->grid[row + 1][position + 2] = true;
			b->grid[row][position + 1] = true;
			while (row + 2 < height) {
				if (b->grid[row + 2][position] == false &&
					b->grid[row + 2][position + 1] == false &&
					b->grid[row + 2][position + 2] == false) {
					b->grid[row + 1][position] = false;
					b->grid[row + 1][position + 1] = false;
					b->grid[row + 1][position + 2] = false;
					b->grid[row][position + 1] = false;
					row++;
					b->grid[row + 1][position] = true;
					b->grid[row + 1][position + 1] = true;
					b->grid[row + 1][position + 2] = true;
					b->grid[row][position + 1] = true;
				}
				else {
					break;
				}
			}
			break;
		}
		}
		break;
	}
	}
	removeClears(b);
}