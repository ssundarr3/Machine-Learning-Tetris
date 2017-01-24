#include "board.h"

using namespace std;

class Board {
public:
	vector<vector<bool>> grid;
	const int width;
	const int height;
	Board() : width(10), height(20) {
		for (int i = 0; i < height; i++) {
			vector<bool> row;
			for (int j = 0; j < width; j++) {
				row.push_back(false);
			}
			grid.push_back(row);
		}
	}
	Board(int w, int h) : width(w), height(h) {
		for (int i = 0; i < height; i++) {
			vector<bool> row;
			for (int j = 0; j < width; j++) {
				row.push_back(false);
			}
			grid.push_back(row);
		}
	}
	~Board() {
		// do nothing
	}
	//adds a piece to the board and returns the resulting board's fitness.
	int addPiece(char piece, int position, char rotation) {
		int row = 0;
		switch (piece) {
			case 'I': {
				if (rotation == 1) { // upright
					grid[row][position] = true;
					grid[row + 1][position] = true;
					grid[row + 2][position] = true;
					grid[row + 3][position] = true;
					while (row + 4 < height) {
						if (grid[row + 4][position] == false) {
							grid[row][position] = false;
							grid[row + 4][position] = true;
							row++;
						}
						else {
							break;
						}
					}
				}
				else if (rotation == 2) { // sideways
					if (grid[row][position] == true ||
						grid[row][position + 1] ||
						grid[row][position + 2] ||
						grid[row][position + 3]) {
						return -1;
					}
					grid[row][position] = true;
					grid[row][position + 1] = true;
					grid[row][position + 2] = true;
					grid[row][position + 3] = true;
					while (row + 1 < height) {
						if (grid[row + 1][position] == false &&
							grid[row + 1][position + 1] == false &&
							grid[row + 1][position + 2] == false &&
							grid[row + 1][position + 3] == false) {
							grid[row][position] = false;
							grid[row][position + 1] = false;
							grid[row][position + 2] = false;
							grid[row][position + 3] = false;
							row++;
							grid[row][position] = true;
							grid[row][position + 1] = true;
							grid[row][position + 2] = true;
							grid[row][position + 3] = true;
						}
						else {
							break;
						}
					}
				}
				break;
			}
			case 'O': {
				grid[row][position] = true;
				grid[row + 1][position] = true;
				grid[row][position + 1] = true;
				grid[row + 1][position + 1] = true;
				while (row + 2 < height) {
					if (grid[row + 2][position] == false && grid[row + 2][position + 1] == false) {
						grid[row][position] = false;
						grid[row][position + 1] = false;
						grid[row + 2][position] = true;
						grid[row + 2][position + 1] = true;
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
					case 1: { // L
						grid[row][position] = true;
						grid[row + 1][position] = true;
						grid[row + 2][position] = true;
						grid[row + 2][position + 1] = true;
						while (row + 3 < height) {
							if (grid[row + 3][position] == false && grid[row + 3][position + 1] == false) {
								grid[row][position] = false;
								grid[row + 2][position + 1] = false;
								row++;
								grid[row + 2][position] = true;
								grid[row + 2][position + 1] = true;
							}
							else {
								break;
							}
						}
						break;
					}
					case 2: { //    X X X
						      //    X
						grid[row][position] = true;
						grid[row][position + 1] = true;
						grid[row][position + 2] = true;
						grid[row + 1][position] = true;
						while (row + 3 < height) {
							if (grid[row + 2][position] == false && 
								grid[row + 1][position + 1] == false && 
								grid[row + 1][position + 2] == false) {
								grid[row][position] = false;
								grid[row][position + 1] = false;
								grid[row][position + 2] = false;
								row++;
								grid[row][position + 1] = true;
								grid[row][position + 2] = true;
								grid[row + 1][position] = true;
							}
							else {
								break;
							}
						}
						break;
					}
					case 3: { //    X X
						      //      X
							  //      X
						grid[row][position] = true;
						grid[row][position + 1] = true;
						grid[row + 1][position + 1] = true;
						grid[row + 2][position + 1] = true;
						while (row + 4 < height) {
							if (grid[row + 3][position + 1] == false &&
								grid[row + 1][position] == false) {
								grid[row][position] = false;
								grid[row][position + 1] = false;
								row++;
								grid[row][position] = true;
								grid[row + 2][position + 1] = true;
							}
							else {
								break;
							}
						}
						break;
					}
					case 4: { //        X
						      //    X X X
						grid[row][position + 2] = true;
						grid[row + 1][position] = true;
						grid[row + 1][position + 1] = true;
						grid[row + 1][position + 2] = true;
						while (row + 2 < height) {
							if (grid[row + 2][position] == false &&
								grid[row + 2][position + 1] == false &&
								grid[row + 2][position + 2] == false) {
								grid[row][position + 2] = false;
								grid[row + 1][position] = false;
								grid[row + 1][position + 1] = false;
								row++;
								grid[row + 1][position] = true;
								grid[row + 1][position + 1] = true;
								grid[row + 1][position + 2] = true;
							}
							else {
								break;
							}
						}
						break;
					}
				}
			}
		}
	}
};