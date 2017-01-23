#include "Cell.h"
#include "Info.h"
#include "SubjectType.h"
#include "SubscriberType.h"

Cell::Cell(int row, int col): row{row}, col{col} {
	letter = ' ';
}

void Cell::SetCell(char letter) {
	this->letter = letter;

	NotifyObservers(SubscriberType::DISPLAY);
}

void Cell::UpdateDropped() {
	NotifyObservers(SubscriberType::DROPPED);
}

void Cell::UpdateRow(int row) {
	this->row = row;
}

void Cell::DeleteLetter() {
	letter = ' ';
}

SubjectType Cell::GetSubjectType() {
	return SubjectType::CELL;
}

Info Cell::GetInfo() {
	Info tempInfo{row, col, letter};

	return tempInfo;
}

Cell::~Cell() {}
