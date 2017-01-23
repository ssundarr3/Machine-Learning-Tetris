#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <iostream>
class Row;
class DroppedBlock;
class TextDisplay;
class GraphicsDisplay;

struct Position {
	int row;
	int col;
};

class Shape;

class Grid {
	
public:
	// START: WAS PRIVATE
	std::vector<Row *> allRows;
	Shape *currShape;
	Position window[4][4];
	const int WINDOW_SIZE = 4;
	std::vector<DroppedBlock *> droppedBlocks;
	TextDisplay *td;
	GraphicsDisplay *gd;
	int currentHS;
	int HS;

	char currShapeChar;
	char nextShapeChar;

	const int NUM_ROWS;
	const int NUM_COLS;

	void CalculateHS(int, int);
	void DetachRows(int);
	void ReattachRows(int);
	bool IsMovePossible(Position tempWindow[4][4], Shape *);
	bool RowAnnihilation(int);
	std::string MakeNextShape();
	// END: WAS PRIVATE




	//Note: grid MUST at least be 6x6 to be a valid grid.
	Grid();
	Grid(int, int);
	void SetShapes(char, char);
	void ClearGrid();
	bool TranslateWindowLeft();
	bool TranslateWindowRight();
	bool TranslateWindowDown();
	bool RotateClockwise();
	bool RotateCounterClockwise();
	bool ChangeShape(char);
	bool DropWindow(int);
	bool CreateNewShape(char, int);
	void Hint();
	~Grid();

	friend std::ostream &operator<<(std::ostream &, Grid &);
};

std::ostream &operator<<(std::ostream &, Grid &);

#endif
