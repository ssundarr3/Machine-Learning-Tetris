#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <iostream>
#include "Row.h"
#include "Cell.h"

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

	Grid& operator=(const Grid& other){
		for(int i=0; i<other.allRows.size(); ++i){
			for(int j=0; j<other.allRows[0]->columns.size(); ++j){
				(allRows[i]->columns)[j]->letter = (other.allRows[i]->columns)[j]->letter;
			}
		}

		if(other.currShapeChar == 'O'){(allRows[2]->columns)[0]->letter = ' '; (allRows[2]->columns)[1]->letter = ' '; (allRows[3]->columns)[0]->letter = ' '; (allRows[3]->columns)[1]->letter = ' ';}
		else if(other.currShapeChar == 'I'){(allRows[3]->columns)[0]->letter = ' '; (allRows[3]->columns)[1]->letter = ' '; (allRows[3]->columns)[2]->letter = ' '; (allRows[3]->columns)[3]->letter = ' ';}
		else if(other.currShapeChar == 'J'){(allRows[2]->columns)[0]->letter = ' '; (allRows[3]->columns)[1]->letter = ' '; (allRows[3]->columns)[2]->letter = ' '; (allRows[3]->columns)[0]->letter = ' ';}
		else if(other.currShapeChar == 'L'){(allRows[2]->columns)[2]->letter = ' '; (allRows[3]->columns)[1]->letter = ' '; (allRows[3]->columns)[2]->letter = ' '; (allRows[3]->columns)[0]->letter = ' ';}
		else if(other.currShapeChar == 'Z'){(allRows[2]->columns)[0]->letter = ' '; (allRows[2]->columns)[1]->letter = ' '; (allRows[3]->columns)[1]->letter = ' '; (allRows[3]->columns)[2]->letter = ' ';}
		else if(other.currShapeChar == 'S'){(allRows[2]->columns)[1]->letter = ' '; (allRows[2]->columns)[2]->letter = ' '; (allRows[3]->columns)[0]->letter = ' '; (allRows[3]->columns)[1]->letter = ' ';}
		else if(other.currShapeChar == 'T'){(allRows[2]->columns)[0]->letter = ' '; (allRows[2]->columns)[1]->letter = ' '; (allRows[2]->columns)[2]->letter = ' '; (allRows[3]->columns)[1]->letter = ' ';}

		currentHS = other.currentHS;
		HS = other.HS;

		SetShapes(' ', other.currShapeChar);
		CreateNewShape(other.nextShapeChar, 2);
	}

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





	//Note: grid MUST at least be 6x6 to be a valid grid.
	Grid(int, int, bool);
	void SetShapes(char, char);
	void ClearGrid();
	bool TranslateWindowLeft();
	bool TranslateWindowRight();
	bool TranslateWindowDown();
	bool RotateClockwise();
	bool RotateCounterClockwise();
	bool ChangeShape(char);
	int DropWindow(int);
	bool CreateNewShape(char, int);
	void Hint();
	~Grid();

	friend std::ostream &operator<<(std::ostream &, Grid &);
};

std::ostream &operator<<(std::ostream &, Grid &);

#endif
