#ifndef CELL_H
#define CELL_H

#include "Subject.h"
class Info;
enum class SubjectType;

class Cell : public Subject {
	char letter;
	int row;
	int col;
public:
	Cell(int, int);
	void SetCell(char);
	void UpdateDropped();
	void UpdateRow(int);
	void DeleteLetter();
	SubjectType GetSubjectType() override;
	Info GetInfo() override;
	~Cell() override;
};

#endif
