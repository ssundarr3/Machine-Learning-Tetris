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


// int Board::addPiece(Board b, char piece, int position, char rotation) {
// 	int row = 0;
// 	switch (piece) {
// 	case 'I': {
// 		if (rotation == 1) { // upright
// 			b.grid[row][position] = true;
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 2][position] = true;
// 			b.grid[row + 3][position] = true;
// 			while (row + 4 < height) {
// 				if (b.grid[row + 4][position] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row + 4][position] = true;
// 					row++;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 		}
// 		else if (rotation == 2) { // sideways
// 			if (b.grid[row][position] == true ||
// 				b.grid[row][position + 1] ||
// 				b.grid[row][position + 2] ||
// 				b.grid[row][position + 3]) {
// 				return -1;
// 			}
// 			b.grid[row][position] = true;
// 			b.grid[row][position + 1] = true;
// 			b.grid[row][position + 2] = true;
// 			b.grid[row][position + 3] = true;
// 			while (row + 1 < height) {
// 				if (b.grid[row + 1][position] == false &&
// 					b.grid[row + 1][position + 1] == false &&
// 					b.grid[row + 1][position + 2] == false &&
// 					b.grid[row + 1][position + 3] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row][position + 1] = false;
// 					b.grid[row][position + 2] = false;
// 					b.grid[row][position + 3] = false;
// 					row++;
// 					b.grid[row][position] = true;
// 					b.grid[row][position + 1] = true;
// 					b.grid[row][position + 2] = true;
// 					b.grid[row][position + 3] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 		}
// 		break;
// 	}
// 	case 'O': {
// 		b.grid[row][position] = true;
// 		b.grid[row + 1][position] = true;
// 		b.grid[row][position + 1] = true;
// 		b.grid[row + 1][position + 1] = true;
// 		while (row + 2 < height) {
// 			if (b.grid[row + 2][position] == false && b.grid[row + 2][position + 1] == false) {
// 				b.grid[row][position] = false;
// 				b.grid[row][position + 1] = false;
// 				b.grid[row + 2][position] = true;
// 				b.grid[row + 2][position + 1] = true;
// 				row++;
// 			}
// 			else {
// 				break;
// 			}
// 		}
// 		break;
// 	}
// 	case 'L': {
// 		switch (rotation) {
// 		case 1: { // X
// 				  // X
// 				  // X X
// 			b.grid[row][position] = true;
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 2][position] = true;
// 			b.grid[row + 2][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 3][position] == false && b.grid[row + 3][position + 1] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row + 2][position + 1] = false;
// 					row++;
// 					b.grid[row + 2][position] = true;
// 					b.grid[row + 2][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   //    X X X
// 					//    X
// 			b.grid[row][position] = true;
// 			b.grid[row][position + 1] = true;
// 			b.grid[row][position + 2] = true;
// 			b.grid[row + 1][position] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 2][position] == false &&
// 					b.grid[row + 1][position + 1] == false &&
// 					b.grid[row + 1][position + 2] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row][position + 1] = false;
// 					b.grid[row][position + 2] = false;
// 					row++;
// 					b.grid[row][position + 1] = true;
// 					b.grid[row][position + 2] = true;
// 					b.grid[row + 1][position] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 3: {   //    X X
// 					//      X
// 					//      X
// 			b.grid[row][position] = true;
// 			b.grid[row][position + 1] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row + 2][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 3][position + 1] == false &&
// 					b.grid[row + 1][position] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row][position + 1] = false;
// 					row++;
// 					b.grid[row][position] = true;
// 					b.grid[row + 2][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 4: {   //        X
// 					//    X X X
// 			b.grid[row][position + 2] = true;
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row + 1][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b.grid[row + 2][position] == false &&
// 					b.grid[row + 2][position + 1] == false &&
// 					b.grid[row + 2][position + 2] == false) {
// 					b.grid[row][position + 2] = false;
// 					b.grid[row + 1][position] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					row++;
// 					b.grid[row + 1][position] = true;
// 					b.grid[row + 1][position + 1] = true;
// 					b.grid[row + 1][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	case 'J': {
// 		switch (rotation) {
// 		case 1: {   //   X
// 					//   X
// 					// X X
// 			b.grid[row][position + 1] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row + 2][position + 1] = true;
// 			b.grid[row + 2][position] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 3][position] == false && b.grid[row + 3][position + 1] == false) {
// 					b.grid[row][position + 1] = false;
// 					b.grid[row + 2][position] = false;
// 					row++;
// 					b.grid[row + 2][position] = true;
// 					b.grid[row + 2][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   //  X 
// 					//  X X X
// 			b.grid[row][position] = true;
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row + 1][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b.grid[row + 2][position] == false &&
// 					b.grid[row + 2][position + 1] == false &&
// 					b.grid[row + 2][position + 2] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					b.grid[row + 1][position + 2] = false;
// 					row++;
// 					b.grid[row + 1][position] = true;
// 					b.grid[row + 1][position + 1] = true;
// 					b.grid[row + 1][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 3: {   //   X X
// 					//   X
// 					//   X
// 			b.grid[row][position] = true;
// 			b.grid[row][position + 1] = true;
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 2][position] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 3][position] == false &&
// 					b.grid[row + 1][position + 1] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row][position + 1] = false;
// 					row++;
// 					b.grid[row][position + 1] = true;
// 					b.grid[row + 2][position] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 4: {   //    X X X
// 					//        X
// 			b.grid[row][position] = true;
// 			b.grid[row][position + 1] = true;
// 			b.grid[row][position + 2] = true;
// 			b.grid[row + 1][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b.grid[row + 1][position] == false &&
// 					b.grid[row + 1][position + 1] == false &&
// 					b.grid[row + 2][position + 2] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row][position + 1] = false;
// 					b.grid[row][position + 2] = false;
// 					row++;
// 					b.grid[row][position] = true;
// 					b.grid[row][position + 1] = true;
// 					b.grid[row + 1][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	case 'S': {
// 		switch (rotation) {
// 		case 1: {   //  X 
// 					//  X X 
// 					//    X
// 			b.grid[row][position] = true;
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row + 2][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 2][position] == false &&
// 					b.grid[row + 3][position + 1] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row + 1][position] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					b.grid[row + 2][position + 1] = false;
// 					row++;
// 					b.grid[row][position] = true;
// 					b.grid[row + 1][position] = true;
// 					b.grid[row + 1][position + 1] = true;
// 					b.grid[row + 2][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   //   X X
// 					// X X
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row][position + 1] = true;
// 			b.grid[row][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b.grid[row + 2][position] == false &&
// 					b.grid[row + 2][position + 1] == false &&
// 					b.grid[row + 1][position + 2] == false) {
// 					b.grid[row + 1][position] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					b.grid[row][position + 1] = false;
// 					b.grid[row][position + 2] = false;
// 					row++;
// 					b.grid[row + 1][position] = true;
// 					b.grid[row + 1][position + 1] = true;
// 					b.grid[row][position + 1] = true;
// 					b.grid[row][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	case 'Z': {
// 		switch (rotation) {
// 		case 1: {   //    X
// 					//  X X 
// 					//  X  
// 			b.grid[row + 2][position] = true;
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 3][position] == false &&
// 					b.grid[row + 2][position + 1] == false) {
// 					b.grid[row + 2][position] = false;
// 					b.grid[row + 1][position] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					b.grid[row][position + 1] = false;
// 					row++;
// 					b.grid[row + 2][position] = true;
// 					b.grid[row + 1][position] = true;
// 					b.grid[row + 1][position + 1] = true;
// 					b.grid[row][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   // X X 
// 					//   X X
// 			b.grid[row][position] = true;
// 			b.grid[row][position + 1] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row + 1][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b.grid[row + 1][position] == false &&
// 					b.grid[row + 2][position + 1] == false &&
// 					b.grid[row + 2][position + 2] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row][position + 1] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					b.grid[row + 1][position + 2] = false;
// 					row++;
// 					b.grid[row][position] = true;
// 					b.grid[row][position + 1] = true;
// 					b.grid[row + 1][position + 1] = true;
// 					b.grid[row + 1][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	case 'T': {
// 		switch (rotation) {
// 		case 1: {   //    X 
// 					//  X X 
// 					//    X
// 			b.grid[row][position + 1] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row + 2][position + 1] = true;
// 			b.grid[row + 1][position] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 3][position + 1] == false &&
// 					b.grid[row + 2][position] == false) {
// 					b.grid[row][position + 1] = false;
// 					b.grid[row + 1][position] = false;
// 					row++;
// 					b.grid[row + 2][position + 1] = true;
// 					b.grid[row + 1][position] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   //  X X X
// 					//    X 
// 			b.grid[row][position] = true;
// 			b.grid[row][position + 1] = true;
// 			b.grid[row][position + 2] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			while (row + 2 < height) {
// 				if (b.grid[row + 1][position] == false &&
// 					b.grid[row + 2][position + 1] == false &&
// 					b.grid[row + 1][position + 2] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row][position + 1] = false;
// 					b.grid[row][position + 2] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					row++;
// 					b.grid[row][position] = true;
// 					b.grid[row][position + 1] = true;
// 					b.grid[row][position + 2] = true;
// 					b.grid[row + 1][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 3: {   //   X 
// 					//   X X
// 					//   X
// 			b.grid[row][position] = true;
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 2][position] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b.grid[row + 3][position] == false &&
// 					b.grid[row + 2][position + 1] == false) {
// 					b.grid[row][position] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					row++;
// 					b.grid[row + 2][position] = true;
// 					b.grid[row + 1][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 4: {   //    X
// 					//  X X X
// 			b.grid[row + 1][position] = true;
// 			b.grid[row + 1][position + 1] = true;
// 			b.grid[row + 1][position + 2] = true;
// 			b.grid[row][position + 1] = true;
// 			while (row + 2 < height) {
// 				if (b.grid[row + 2][position] == false &&
// 					b.grid[row + 2][position + 1] == false &&
// 					b.grid[row + 2][position + 2] == false) {
// 					b.grid[row + 1][position] = false;
// 					b.grid[row + 1][position + 1] = false;
// 					b.grid[row + 1][position + 2] = false;
// 					b.grid[row][position + 1] = false;
// 					row++;
// 					b.grid[row + 1][position] = true;
// 					b.grid[row + 1][position + 1] = true;
// 					b.grid[row + 1][position + 2] = true;
// 					b.grid[row][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	}
// 	return calculateFitness(b);
// }


// void Board::addPiece(Board * b, char piece, int position, char rotation) {
// 	int row = 0;
// 	switch (piece) {
// 	case 'I': {
// 		if (rotation == 1) { // upright
// 			b->grid[row][position] = true;
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 2][position] = true;
// 			b->grid[row + 3][position] = true;
// 			while (row + 4 < height) {
// 				if (b->grid[row + 4][position] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row + 4][position] = true;
// 					row++;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 		}
// 		else if (rotation == 2) { // sideways
// 			if (b->grid[row][position] == true ||
// 				b->grid[row][position + 1] ||
// 				b->grid[row][position + 2] ||
// 				b->grid[row][position + 3]) {
// 				return;
// 			}
// 			b->grid[row][position] = true;
// 			b->grid[row][position + 1] = true;
// 			b->grid[row][position + 2] = true;
// 			b->grid[row][position + 3] = true;
// 			while (row + 1 < height) {
// 				if (b->grid[row + 1][position] == false &&
// 					b->grid[row + 1][position + 1] == false &&
// 					b->grid[row + 1][position + 2] == false &&
// 					b->grid[row + 1][position + 3] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row][position + 1] = false;
// 					b->grid[row][position + 2] = false;
// 					b->grid[row][position + 3] = false;
// 					row++;
// 					b->grid[row][position] = true;
// 					b->grid[row][position + 1] = true;
// 					b->grid[row][position + 2] = true;
// 					b->grid[row][position + 3] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 		}
// 		break;
// 	}
// 	case 'O': {
// 		b->grid[row][position] = true;
// 		b->grid[row + 1][position] = true;
// 		b->grid[row][position + 1] = true;
// 		b->grid[row + 1][position + 1] = true;
// 		while (row + 2 < height) {
// 			if (b->grid[row + 2][position] == false && b->grid[row + 2][position + 1] == false) {
// 				b->grid[row][position] = false;
// 				b->grid[row][position + 1] = false;
// 				b->grid[row + 2][position] = true;
// 				b->grid[row + 2][position + 1] = true;
// 				row++;
// 			}
// 			else {
// 				break;
// 			}
// 		}
// 		break;
// 	}
// 	case 'L': {
// 		switch (rotation) {
// 		case 1: { // X
// 				  // X
// 				  // X X
// 			b->grid[row][position] = true;
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 2][position] = true;
// 			b->grid[row + 2][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 3][position] == false && b->grid[row + 3][position + 1] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row + 2][position + 1] = false;
// 					row++;
// 					b->grid[row + 2][position] = true;
// 					b->grid[row + 2][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   //    X X X
// 					//    X
// 			b->grid[row][position] = true;
// 			b->grid[row][position + 1] = true;
// 			b->grid[row][position + 2] = true;
// 			b->grid[row + 1][position] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 2][position] == false &&
// 					b->grid[row + 1][position + 1] == false &&
// 					b->grid[row + 1][position + 2] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row][position + 1] = false;
// 					b->grid[row][position + 2] = false;
// 					row++;
// 					b->grid[row][position + 1] = true;
// 					b->grid[row][position + 2] = true;
// 					b->grid[row + 1][position] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 3: {   //    X X
// 					//      X
// 					//      X
// 			b->grid[row][position] = true;
// 			b->grid[row][position + 1] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row + 2][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 3][position + 1] == false &&
// 					b->grid[row + 1][position] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row][position + 1] = false;
// 					row++;
// 					b->grid[row][position] = true;
// 					b->grid[row + 2][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 4: {   //        X
// 					//    X X X
// 			b->grid[row][position + 2] = true;
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row + 1][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b->grid[row + 2][position] == false &&
// 					b->grid[row + 2][position + 1] == false &&
// 					b->grid[row + 2][position + 2] == false) {
// 					b->grid[row][position + 2] = false;
// 					b->grid[row + 1][position] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					row++;
// 					b->grid[row + 1][position] = true;
// 					b->grid[row + 1][position + 1] = true;
// 					b->grid[row + 1][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	case 'J': {
// 		switch (rotation) {
// 		case 1: {   //   X
// 					//   X
// 					// X X
// 			b->grid[row][position + 1] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row + 2][position + 1] = true;
// 			b->grid[row + 2][position] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 3][position] == false && b->grid[row + 3][position + 1] == false) {
// 					b->grid[row][position + 1] = false;
// 					b->grid[row + 2][position] = false;
// 					row++;
// 					b->grid[row + 2][position] = true;
// 					b->grid[row + 2][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   //  X 
// 					//  X X X
// 			b->grid[row][position] = true;
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row + 1][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b->grid[row + 2][position] == false &&
// 					b->grid[row + 2][position + 1] == false &&
// 					b->grid[row + 2][position + 2] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					b->grid[row + 1][position + 2] = false;
// 					row++;
// 					b->grid[row + 1][position] = true;
// 					b->grid[row + 1][position + 1] = true;
// 					b->grid[row + 1][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 3: {   //   X X
// 					//   X
// 					//   X
// 			b->grid[row][position] = true;
// 			b->grid[row][position + 1] = true;
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 2][position] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 3][position] == false &&
// 					b->grid[row + 1][position + 1] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row][position + 1] = false;
// 					row++;
// 					b->grid[row][position + 1] = true;
// 					b->grid[row + 2][position] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 4: {   //    X X X
// 					//        X
// 			b->grid[row][position] = true;
// 			b->grid[row][position + 1] = true;
// 			b->grid[row][position + 2] = true;
// 			b->grid[row + 1][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b->grid[row + 1][position] == false &&
// 					b->grid[row + 1][position + 1] == false &&
// 					b->grid[row + 2][position + 2] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row][position + 1] = false;
// 					b->grid[row][position + 2] = false;
// 					row++;
// 					b->grid[row][position] = true;
// 					b->grid[row][position + 1] = true;
// 					b->grid[row + 1][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	case 'S': {
// 		switch (rotation) {
// 		case 1: {   //  X 
// 					//  X X 
// 					//    X
// 			b->grid[row][position] = true;
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row + 2][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 2][position] == false &&
// 					b->grid[row + 3][position + 1] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row + 1][position] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					b->grid[row + 2][position + 1] = false;
// 					row++;
// 					b->grid[row][position] = true;
// 					b->grid[row + 1][position] = true;
// 					b->grid[row + 1][position + 1] = true;
// 					b->grid[row + 2][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   //   X X
// 					// X X
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row][position + 1] = true;
// 			b->grid[row][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b->grid[row + 2][position] == false &&
// 					b->grid[row + 2][position + 1] == false &&
// 					b->grid[row + 1][position + 2] == false) {
// 					b->grid[row + 1][position] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					b->grid[row][position + 1] = false;
// 					b->grid[row][position + 2] = false;
// 					row++;
// 					b->grid[row + 1][position] = true;
// 					b->grid[row + 1][position + 1] = true;
// 					b->grid[row][position + 1] = true;
// 					b->grid[row][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	case 'Z': {
// 		switch (rotation) {
// 		case 1: {   //    X
// 					//  X X 
// 					//  X  
// 			b->grid[row + 2][position] = true;
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 3][position] == false &&
// 					b->grid[row + 2][position + 1] == false) {
// 					b->grid[row + 2][position] = false;
// 					b->grid[row + 1][position] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					b->grid[row][position + 1] = false;
// 					row++;
// 					b->grid[row + 2][position] = true;
// 					b->grid[row + 1][position] = true;
// 					b->grid[row + 1][position + 1] = true;
// 					b->grid[row][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   // X X 
// 					//   X X
// 			b->grid[row][position] = true;
// 			b->grid[row][position + 1] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row + 1][position + 2] = true;
// 			while (row + 2 < height) {
// 				if (b->grid[row + 1][position] == false &&
// 					b->grid[row + 2][position + 1] == false &&
// 					b->grid[row + 2][position + 2] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row][position + 1] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					b->grid[row + 1][position + 2] = false;
// 					row++;
// 					b->grid[row][position] = true;
// 					b->grid[row][position + 1] = true;
// 					b->grid[row + 1][position + 1] = true;
// 					b->grid[row + 1][position + 2] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	case 'T': {
// 		switch (rotation) {
// 		case 1: {   //    X 
// 					//  X X 
// 					//    X
// 			b->grid[row][position + 1] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row + 2][position + 1] = true;
// 			b->grid[row + 1][position] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 3][position + 1] == false &&
// 					b->grid[row + 2][position] == false) {
// 					b->grid[row][position + 1] = false;
// 					b->grid[row + 1][position] = false;
// 					row++;
// 					b->grid[row + 2][position + 1] = true;
// 					b->grid[row + 1][position] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 2: {   //  X X X
// 					//    X 
// 			b->grid[row][position] = true;
// 			b->grid[row][position + 1] = true;
// 			b->grid[row][position + 2] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			while (row + 2 < height) {
// 				if (b->grid[row + 1][position] == false &&
// 					b->grid[row + 2][position + 1] == false &&
// 					b->grid[row + 1][position + 2] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row][position + 1] = false;
// 					b->grid[row][position + 2] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					row++;
// 					b->grid[row][position] = true;
// 					b->grid[row][position + 1] = true;
// 					b->grid[row][position + 2] = true;
// 					b->grid[row + 1][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 3: {   //   X 
// 					//   X X
// 					//   X
// 			b->grid[row][position] = true;
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 2][position] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			while (row + 3 < height) {
// 				if (b->grid[row + 3][position] == false &&
// 					b->grid[row + 2][position + 1] == false) {
// 					b->grid[row][position] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					row++;
// 					b->grid[row + 2][position] = true;
// 					b->grid[row + 1][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		case 4: {   //    X
// 					//  X X X
// 			b->grid[row + 1][position] = true;
// 			b->grid[row + 1][position + 1] = true;
// 			b->grid[row + 1][position + 2] = true;
// 			b->grid[row][position + 1] = true;
// 			while (row + 2 < height) {
// 				if (b->grid[row + 2][position] == false &&
// 					b->grid[row + 2][position + 1] == false &&
// 					b->grid[row + 2][position + 2] == false) {
// 					b->grid[row + 1][position] = false;
// 					b->grid[row + 1][position + 1] = false;
// 					b->grid[row + 1][position + 2] = false;
// 					b->grid[row][position + 1] = false;
// 					row++;
// 					b->grid[row + 1][position] = true;
// 					b->grid[row + 1][position + 1] = true;
// 					b->grid[row + 1][position + 2] = true;
// 					b->grid[row][position + 1] = true;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		}
// 		break;
// 	}
// 	}
// 	removeClears(b);
// }