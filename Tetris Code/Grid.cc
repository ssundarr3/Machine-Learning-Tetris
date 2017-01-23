#include "Grid.h"
#include "Info.h"
#include "Row.h"
#include "DroppedBlock.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "SubscriberType.h"
#include <sstream>
#include <iomanip>
#include "Level.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
extern Level* currLevel;
extern bool textOnly;

struct Orientation {
	int orient[4][4];
};

class Shape {
public:
	Shape() = default;
	virtual void RotateClockwise() = 0;
	virtual void RotateCounterClockwise() = 0;
	virtual char GetType() = 0;
	virtual Orientation GetRotation() = 0;
	virtual ~Shape() = 0;
};

Shape::~Shape() {}

class J: public Shape {
	int currState;
	const int numStates = 4;
	const char type = 'J';
	Orientation *rotations[4];
public:
	J() {
		currState = 0;

		rotations[0] = new Orientation{0,0,0,0,
	 				       0,0,0,0,
	 			  	       1,0,0,0,
	 			      	       1,1,1,0};

		rotations[1] = new Orientation{0,0,0,0,
					       1,1,0,0,
					       1,0,0,0,
					       1,0,0,0};

		rotations[2] = new Orientation{0,0,0,0,
					       0,0,0,0,
					       1,1,1,0,
					       0,0,1,0};

		rotations[3] = new Orientation{0,0,0,0,
					       0,1,0,0,
					       0,1,0,0,
					       1,1,0,0};
	}

	void RotateClockwise() override {
		currState = (currState + 1) % numStates;
	}

	void RotateCounterClockwise() override {
		currState = (currState + (numStates - 1)) % numStates;
	}

	char GetType() override {
		return type;
	}

	Orientation GetRotation() override {
		return *rotations[currState];
	}

	~J() override {
		for (int i = 0; i < numStates; ++i) {
			delete rotations[i];
		}
	}
};

class L: public Shape {
	int currState;
	const int numStates = 4;
	const char type = 'L';
	Orientation *rotations[4];
public:
	L() {
		currState = 0;

		rotations[0] = new Orientation{0,0,0,0,
					       0,0,0,0,
					       0,0,1,0,
					       1,1,1,0};

		rotations[1] = new Orientation{0,0,0,0,
					       1,0,0,0,
				     	       1,0,0,0,
					       1,1,0,0};

		rotations[2] = new Orientation{0,0,0,0,
					       0,0,0,0,
					       1,1,1,0,
					       1,0,0,0};

		rotations[3] = new Orientation{0,0,0,0,
					       1,1,0,0,
					       0,1,0,0,
					       0,1,0,0};
	}

	void RotateClockwise() override {
		currState = (currState + 1) % numStates;
	}

	void RotateCounterClockwise() override {
		currState = (currState + (numStates - 1)) % numStates;
	}

	char GetType() override {
		return type;
	}

	Orientation GetRotation() override {
		return *rotations[currState];
	}

	~L() override {
		for (int i = 0; i < numStates; ++i) {
			delete rotations[i];
		}
	}
};

class S: public Shape {
	int currState;
	const int numStates = 2;
	const char type = 'S';
	Orientation *rotations[2];
public:
	S() {
		currState = 0;

		rotations[0] = new Orientation{0,0,0,0,
					       0,0,0,0,
					       0,1,1,0,
					       1,1,0,0};

		rotations[1] = new Orientation{0,0,0,0,
					       1,0,0,0,
					       1,1,0,0,
					       0,1,0,0};
	}

	void RotateClockwise() override {
		currState = (currState + 1) % numStates;
	}

	void RotateCounterClockwise() override {
		currState = (currState + (numStates - 1)) % numStates;
	}

	char GetType() override {
		return type;
	}

	Orientation GetRotation() override {
		return *rotations[currState];
	}

	~S() override {
		for (int i = 0; i < numStates; ++i) {
			delete rotations[i];
		}
	}
};

class Z: public Shape {
	int currState;
	const int numStates = 2;
	const char type = 'Z';
	Orientation *rotations[2];
public:
	Z() {
		currState = 0;

		rotations[0] = new Orientation{0,0,0,0,
					       0,0,0,0,
					       1,1,0,0,
					       0,1,1,0};

		rotations[1] = new Orientation{0,0,0,0,
					       0,1,0,0,
				               1,1,0,0,
					       1,0,0,0};
	}

	void RotateClockwise() override {
		currState = (currState + 1) % numStates;
	}

	void RotateCounterClockwise() override {
		currState = (currState + (numStates - 1)) % numStates;
	}

	char GetType() override {
		return type;
	}

	Orientation GetRotation() override {
		return *rotations[currState];
	}

	~Z() override {
		for (int i = 0; i < numStates; ++i) {
			delete rotations[i];
		}
	}
};

class T: public Shape {
	int currState;
	const int numStates = 4;
	const char type = 'T';
	Orientation *rotations[4];
public:
	T() {
		currState = 0;

		rotations[0] = new Orientation{0,0,0,0,
					       0,0,0,0,
					       1,1,1,0,
					       0,1,0,0};

		rotations[1] = new Orientation{0,0,0,0,
					       0,1,0,0,
					       1,1,0,0,
					       0,1,0,0};

		rotations[2] = new Orientation{0,0,0,0,
					       0,0,0,0,
					       0,1,0,0,
					       1,1,1,0};

		rotations[3] = new Orientation{0,0,0,0,
					       1,0,0,0,
					       1,1,0,0,
					       1,0,0,0};
	}

	void RotateClockwise() override {
		currState = (currState + 1) % numStates;
	}

	void RotateCounterClockwise() override {
		currState = (currState + (numStates - 1)) % numStates;
	}

	char GetType() override {
		return type;
	}

	Orientation GetRotation() override {
		return *rotations[currState];
	}

	~T() override {
		for (int i = 0; i < numStates; ++i) {
			delete rotations[i];
		}
	}
};

class I: public Shape {
	int currState;
	const int numStates = 2;
	const char type = 'I';
	Orientation *rotations[2];
public:
	I() {
		currState = 0;

		rotations[0] = new Orientation{0,0,0,0,
					       0,0,0,0,
					       0,0,0,0,
					       1,1,1,1};

		rotations[1] = new Orientation{1,0,0,0,
					       1,0,0,0,
					       1,0,0,0,
					       1,0,0,0};
	}

	void RotateClockwise() override {
		currState = (currState + 1) % numStates;
	}

	void RotateCounterClockwise() override {
		currState = (currState + (numStates - 1)) % numStates;
	}

	char GetType() override {
		return type;
	}

	Orientation GetRotation() override {
		return *rotations[currState];
	}

	~I() override {
		for (int i = 0; i < numStates; ++i) {
			delete rotations[i];
		}
	}
};

class O: public Shape {
	const char type = 'O';
	Orientation *rotation;
public:
	O() {
		rotation = new Orientation{0,0,0,0,
					   0,0,0,0,
					   1,1,0,0,
					   1,1,0,0};
	}

	void RotateClockwise() override {}
	void RotateCounterClockwise() override {}

	char GetType() override {
		return type;
	}

	Orientation GetRotation() override {
		return *rotation;
	}

	~O() override {
		delete rotation;
	}
};

class Star: public Shape {
	const char type = '*';
	Orientation *rotation;
public:
	Star() {
		rotation = new Orientation{0,0,0,0,
					   0,0,0,0,
				 	   0,0,0,0,
				 	   1,0,0,0};
	}

	void RotateClockwise() override {}
	void RotateCounterClockwise() override {}

	char GetType() override {
		return type;
	}

	Orientation GetRotation() override {
		return *rotation;
	}

	~Star() override {
		delete rotation;
	}
};

bool Grid::IsMovePossible(Position tempWindow[4][4], Shape *tempShape) {
	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (tempShape->GetRotation().orient[i][j] == 1) {
				if (tempWindow[i][j].row < 0 || tempWindow[i][j].row >= NUM_ROWS || 
					tempWindow[i][j].col < 0 || tempWindow[i][j].col >= NUM_COLS) {
					return false;
				}

				Info tempInfo = allRows[tempWindow[i][j].row]->GetInfo(tempWindow[i][j].col);

				if (tempInfo.letter != ' ') {
					return false;
				}
			}
		}
	}

	return true;
}

Grid::Grid(){
	
}

Grid::Grid(int row, int col): NUM_ROWS{row}, NUM_COLS{col} {
	td = new TextDisplay{NUM_ROWS, NUM_COLS};
	if(!textOnly){
		gd = new GraphicsDisplay{NUM_ROWS, NUM_COLS};
	}else{
		gd = nullptr;
	}

	currentHS = 0;
	HS = 0;

	for (int i = 0; i < NUM_ROWS; ++i) {
		Row *newRow = new Row{NUM_COLS, i, td, gd};
		
		allRows.emplace_back(newRow);
	}

	for (int i = allRows.size() - 1; i > -1; --i) {
		allRows[i]->Attach(td);
		if(!textOnly){
			allRows[i]->Attach(gd);
		}

		if (i != 0) {
			allRows[i]->Attach(allRows[i - 1]);
		}
	}

	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			window[i][j].row = -1;
			window[i][j].col = -1;
		}
	}

	currShape = nullptr;

	currShapeChar = ' ';
	nextShapeChar = ' ';
}

void Grid::SetShapes(char currShapeChar, char nextShapeChar) {
	this->currShapeChar = currShapeChar;
	this->nextShapeChar = nextShapeChar;
}

void Grid::ClearGrid() {
	if (currentHS > HS) {
		HS = currentHS;
	}

	currentHS = 0;

	for (int i = 0; i < NUM_ROWS; ++i) {
		allRows[i]->DetachAllBlocks();
	}

	for (int i = 0; i < NUM_ROWS; ++i) {
		for (int j = 0; j < NUM_COLS; ++j) {
			allRows[i]->SetCell(allRows[i]->GetInfo(j).col, ' ');
		}
	}

	//Assumption: all elements in valid indices are allocating from the heap.
	for (int i = 0; i < droppedBlocks.size(); ++i) {
		delete droppedBlocks[i];
	}

	droppedBlocks.clear();

	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			window[i][j].row = -1;
			window[i][j].col = -1;
		}
	}

	//Assumption: in this function, currShape should already have been deleted,
	//this conditonal exists as an extra safety precaution.
	if (currShape != nullptr) {
		delete currShape;
	}

	currShapeChar = ' ';
	nextShapeChar = ' ';
}

//Assumption: all shapes are CONNECTED.
//Assumption: all shapes are composed of at least ONE block.
std::string Grid::MakeNextShape() {
	Shape *tempShape;

	if (nextShapeChar == 'I') {
		tempShape = new I;
	} else if (nextShapeChar == 'J') {
		tempShape = new J;
	} else if (nextShapeChar == 'L') {
		tempShape = new L;
	} else if (nextShapeChar == 'O') {
		tempShape = new O;
	} else if (nextShapeChar == 'S') {
		tempShape = new S;
	} else if (nextShapeChar == 'Z') {
		tempShape = new Z;
	} else if (nextShapeChar == 'T') {
		tempShape = new T;
	}

	int lastFilledRow = -1;

	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (tempShape->GetRotation().orient[i][j] == 1) {
				lastFilledRow = i;
				break; //Breaks for efficiency.
			}
		}
	}

	std::string nextPiece = "";

	for (int i = 0; i < WINDOW_SIZE; ++i) {
		std::string tempRow = "";

		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (tempShape->GetRotation().orient[i][j] == 1) {
				std::stringstream ss;

				ss << tempShape->GetType();

				std::string letter;

				ss >> letter;

				tempRow += letter;
			} else {
				tempRow += " ";
			}
		}

		int numTrailingWhitespace = 0;

		for (int j = (tempRow.size() - 1); j > -1; --j) {
			if (tempRow[j] == ' ') {
				++numTrailingWhitespace;
			} else {
				break;
			}
		}

		for (int j = 0; j < numTrailingWhitespace; ++j) {
			tempRow.pop_back();
		}

		if (tempRow.empty() == true) {
			//Do nothing.
		} else {
			nextPiece += tempRow;

			if (i != lastFilledRow) {
				nextPiece += "\n";
			} else {
				break;
			}
		}
	}

	delete tempShape;

	return nextPiece;
}

//Assumption: currShape cannot be nullptr.
bool Grid::TranslateWindowLeft() {
	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (currShape->GetRotation().orient[i][j] == 1) {
				allRows[window[i][j].row]->SetCell(window[i][j].col, ' ');
			}
		}
	}

	Position tempWindow[4][4];

	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			tempWindow[i][j].row = window[i][j].row;
			tempWindow[i][j].col = window[i][j].col - 1;
		}
	}

	bool isMovePossible = IsMovePossible(tempWindow, currShape);

	if (isMovePossible == true) {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				window[i][j].col = window[i][j].col - 1;
			}
		}

		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return true;
	} else {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return false;
	}
}

//Assumption: currShape cannot be nullptr.
bool Grid::TranslateWindowRight() {
	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (currShape->GetRotation().orient[i][j] == 1) {
				allRows[window[i][j].row]->SetCell(window[i][j].col, ' ');
			}
		}
	}

	Position tempWindow[4][4];

	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			tempWindow[i][j].row = window[i][j].row;
			tempWindow[i][j].col = window[i][j].col + 1;
		}
	}

	bool isMovePossible = IsMovePossible(tempWindow, currShape);

	if (isMovePossible == true) {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				window[i][j].col = window[i][j].col + 1;
			}
		}

		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return true;
	} else {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return false;
	}
}

//Assumption: currShape cannot be nullptr.
bool Grid::TranslateWindowDown() {
	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (currShape->GetRotation().orient[i][j] == 1) {
				allRows[window[i][j].row]->SetCell(window[i][j].col, ' ');
			}
		}
	}

	Position tempWindow[4][4];

	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			tempWindow[i][j].row = window[i][j].row + 1;
			tempWindow[i][j].col = window[i][j].col;
		}
	}

	bool isMovePossible = IsMovePossible(tempWindow, currShape);

	if (isMovePossible == true) {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				window[i][j].row = window[i][j].row + 1;
			}
		}

		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return true;
	} else {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return false;
	}
}

//Assumption: currShape cannot be nullptr.
bool Grid::RotateClockwise() {
	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (currShape->GetRotation().orient[i][j] == 1) {
				allRows[window[i][j].row]->SetCell(window[i][j].col, ' ');
			}
		}
	}

	currShape->RotateClockwise();

	bool isMovePossible = IsMovePossible(window, currShape);

	if (isMovePossible == false) {
		currShape->RotateCounterClockwise();

		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return false;
	} else {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return true;
	}
}

//Assumption: currShape cannot be nullptr.
bool Grid::RotateCounterClockwise() {
	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (currShape->GetRotation().orient[i][j] == 1) {
				allRows[window[i][j].row]->SetCell(window[i][j].col, ' ');
			}
		}
	}

	currShape->RotateCounterClockwise();

	bool isMovePossible = IsMovePossible(window, currShape);

	if (isMovePossible == false) {
		currShape->RotateClockwise();

		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return false;
	} else {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return true;
	}
}

//Assumption: currShape cannot be nullptr.
bool Grid::ChangeShape(char newLetter) {
	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			if (currShape->GetRotation().orient[i][j] == 1) {
				allRows[window[i][j].row]->SetCell(window[i][j].col, ' ');
			}
		}
	}

	Shape *tempShape;

	if (newLetter == 'I') {
		tempShape = new I;
	} else if (newLetter == 'J') {
		tempShape = new J;
	} else if (newLetter == 'L') {
		tempShape = new L;
	} else if (newLetter == 'O') {
		tempShape = new O;
	} else if (newLetter == 'S') {
		tempShape = new S;
	} else if (newLetter == 'Z') {
		tempShape = new Z;
	} else if (newLetter == 'T') {
		tempShape = new T;
	}

	bool isMovePossible = IsMovePossible(window, tempShape);

	delete tempShape;

	if (isMovePossible == true) {
		currShapeChar = newLetter;

		delete currShape;
		currShape = nullptr;
	
		if (newLetter == 'I') {
			currShape = new I;
		} else if (newLetter == 'J') {
			currShape = new J;
		} else if (newLetter == 'L') {
			currShape = new L;
		} else if (newLetter == 'O') {
			currShape = new O;
		} else if (newLetter == 'S') {
			currShape = new S;
		} else if (newLetter == 'Z') {
			currShape = new Z;
		} else if (newLetter == 'T') {
			currShape = new T;
		}

		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return true;
	} else {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		return false;
	}
}

void Grid::CalculateHS(int currLevel, int numRowsKilled) {
	int gainedPoints = 0;

	int rowsKilledScore = currLevel + numRowsKilled;
	rowsKilledScore *= rowsKilledScore;

	int killedBlockScores = 0;

	//Note: careful, if we deleted droppedBlocks' elements while in this loop, we would mess up the droppedBlocks.size().
	for (int i = 0; i < droppedBlocks.size(); ++i) {
		bool areAllBlocksEmpty = droppedBlocks[i]->AreAllBlocksEmpty();

		if (areAllBlocksEmpty == true) {
			int killedBlockScore = droppedBlocks[i]->GetLevelGen() + 1;
			killedBlockScore *= killedBlockScore;

			killedBlockScores += killedBlockScore;
		}
	}

	gainedPoints = rowsKilledScore + killedBlockScores;

	while(1) {
		int badIndex = -1;

		for (int i = 0; i < droppedBlocks.size(); ++i) {
			bool areAllBlocksEmpty = droppedBlocks[i]->AreAllBlocksEmpty();

			if (areAllBlocksEmpty == true) {
				badIndex = i;
				break;
			}
		}

		if (badIndex != -1) {
			delete droppedBlocks[badIndex];
			droppedBlocks.erase(droppedBlocks.begin() + badIndex);
		} else {
			break;
		}
	}

	currentHS += gainedPoints;
}

//Assumption: all rows present, and no row deleted YET.
void Grid::DetachRows(int rowToDelete) {
	if (rowToDelete == 0 || rowToDelete == (allRows.size() - 1)) {
		//Do nothing.
	} else {
		allRows[rowToDelete + 1]->Detach(SubscriberType::ROW);
	}
}

//Assumption: all rows present.
void Grid::ReattachRows(int rowDeleted) {
	if (rowDeleted == 0 || rowDeleted == (allRows.size() - 1)) {
		//Do nothing.
	} else {
		allRows[rowDeleted + 1]->Attach(allRows[rowDeleted]);
	}

	allRows[1]->Attach(allRows[0]);
}

bool Grid::RowAnnihilation(int currLevel) {
	bool hasRowRemoved = false;
	int numRowsKilled = 0;

	for (int i = 0; i < allRows.size(); ++i) {
		bool isFilled = allRows[i]->IsRowFilled();

		if (isFilled == true) {
			DetachRows(i);

			//Fundamentally, the loop is safe here, because even though the .size()
			//of the allRows vector changes temporarily, it is returned back
			//to its original .size() after modification.
			delete allRows[i];
			allRows.erase(allRows.begin() + i);
			Row *newRow = new Row{NUM_COLS, 0, td, gd};
			
			allRows.insert(allRows.begin(), newRow);
			allRows[0]->Attach(td);
			if(!textOnly){
				allRows[0]->Attach(gd);
			}

			ReattachRows(i);

			hasRowRemoved = true;
			++numRowsKilled;
		}
	}

	if (numRowsKilled > 0) {
		CalculateHS(currLevel, numRowsKilled);
	}

	return hasRowRemoved;
}

//Req: currShape is not already freed and nullptr, and will always be freed and set to nullptr.
bool Grid::DropWindow(int currLevel) {
	while(TranslateWindowDown() == true) {}

	if (currShapeChar != '*') {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, droppedBlocks[droppedBlocks.size() - 1]);
				}
			}
		}
	}

	for (int i = 0; i < WINDOW_SIZE; ++i) {
		for (int j = 0; j < WINDOW_SIZE; ++j) {
			window[i][j].row = -1;
			window[i][j].col = -1;
		}
	}

	delete currShape;
	currShape = nullptr;

	return RowAnnihilation(currLevel);
}

//Assumption: currShape IS nullptr.
bool Grid::CreateNewShape(char newLetter, int currLevel) {
	if (newLetter == '*') {
		currShapeChar = newLetter;
	} else {
		currShapeChar = nextShapeChar;
		nextShapeChar = newLetter;
	}

	if (currShapeChar == 'I') {
		currShape = new I;
	} else if (currShapeChar == 'J') {
		currShape = new J;
	} else if (currShapeChar == 'L') {
		currShape = new L;
	} else if (currShapeChar == 'O') {
		currShape = new O;
	} else if (currShapeChar == 'S') {
		currShape = new S;
	} else if (currShapeChar == 'Z') {
		currShape = new Z;
	} else if (currShapeChar == 'T') {
		currShape = new T;
	} else if (currShapeChar == '*') {
		currShape = new Star;
	}

	if (currShapeChar == '*') {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				window[i][j].row = i;
				window[i][j].col = j + (NUM_COLS / 2);
			}
		}
	} else {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				window[i][j].row = i;
				window[i][j].col = j;
			}
		}
	}

	bool isMovePossible = IsMovePossible(window, currShape); 

	if (isMovePossible == true) {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				if (currShape->GetRotation().orient[i][j] == 1) {
					allRows[window[i][j].row]->SetCell(window[i][j].col, currShape->GetType());
				}
			}
		}

		if (currShapeChar != '*') {
			DroppedBlock *newDP = new DroppedBlock{currLevel};

			droppedBlocks.emplace_back(newDP);
		}

		return true;
	} else {
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				window[i][j].row = -1;
				window[i][j].col = -1;
			}
		}

		delete currShape;
		currShape = nullptr;

		return false;
	}
}

void Grid::Hint() {}

Grid::~Grid() {
	//Assumption: all elements in valid indices are allocating from the heap.
	for (int i = 0; i < droppedBlocks.size(); ++i) {
		delete droppedBlocks[i];
	}

	if (currShape != nullptr) {
		delete currShape;
	}

	//Assumption: all elements in valid indices are allocating from the heap.
	for (int i = 0; i < allRows.size(); ++i) {
		delete allRows[i];
	}

	//Display pointers ARE only EVER to be deleted in the destructor.
	delete td;
	
	delete gd;
	
}

std::ostream &operator<<(std::ostream &out, Grid &g) {
	out << "Level:    " << std::setw(4) << currLevel->CurrentLevel() << std::endl;
	out << "Score:    " << std::setw(4) << g.currentHS << std::endl;
	out << "Hi Score: " << std::setw(4) << g.HS << std::endl;

	for (int i = 0; i < g.NUM_COLS; ++i) {
		out << "_";
	}

	out << std::endl;

	out << g.td->PrintDisplay() << std::endl;
	

	for (int i = 0; i < g.NUM_COLS; ++i) {
		out << "_";
	}

	out << std::endl;

	out << "Next:" << std::endl;
	std::string nextShape = g.MakeNextShape();
	out << nextShape << std::endl;


	if(!textOnly){
		g.gd->PrintDisplay(currLevel->CurrentLevel(), g.currentHS, g.HS, nextShape);
	}

	return out;
}
