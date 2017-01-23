#include "Row.h"
#include "Cell.h"
#include "Info.h"
#include "SubjectType.h"
#include "SubscriberType.h"
#include "DroppedBlock.h"
#include "GraphicsDisplay.h"
#include "TextDisplay.h"
extern bool textOnly;

Row::Row(int columnsSize, int rowNum, TextDisplay *td, GraphicsDisplay *gd): columnsSize{columnsSize}, rowNum{rowNum} {
	for (int i = 0; i < columnsSize; ++i) {
		Cell *newCell = new Cell{rowNum, i};
		columns.emplace_back(newCell);

		columns[i]->Attach(td);
		if(!textOnly){
			columns[i]->Attach(gd);
		}
		
	}
}

void Row::SetCell(int colNum, char cellType) {
	columns[colNum]->SetCell(cellType);
}

void Row::SetCell(int colNum, DroppedBlock *observingBlocks) {
	columns[colNum]->Attach(observingBlocks);

	columns[colNum]->UpdateDropped();
}

bool Row::IsRowFilled() {
	int numNonEmptyColumns = 0;

	for (int i = 0; i < columns.size(); ++i) {
		if (columns[i]->GetInfo().letter != ' ') {
			++numNonEmptyColumns;
		}
	}

	if (numNonEmptyColumns == columnsSize) {
		for (int i = 0; i < columns.size(); ++i) {
			columns[i]->DeleteLetter();
			columns[i]->UpdateDropped();
		}

		NotifyObservers(SubscriberType::DISPLAY);
		NotifyObservers(SubscriberType::ROW);

		return true;
	} else {
		return false;
	}
}

void Row::DetachAllBlocks() {
	for (int i = 0; i < columns.size(); ++i) {
		columns[i]->Detach(SubscriberType::DROPPED);
	}
}

void Row::Notify(Subject &notifier) {
	NotifyObservers(SubscriberType::ROW);

	rowNum = notifier.GetInfo().row;

	for (int i = 0; i < columns.size(); ++i) {
		columns[i]->UpdateRow(rowNum);
	}
}

SubscriberType Row::GetSubscriberType() {
	return SubscriberType::ROW;
}

SubjectType Row::GetSubjectType() {
	return SubjectType::ROW;
}

Info Row::GetInfo() {
	Info tempInfo{rowNum, -1, ' '};

	return tempInfo;
}

Info Row::GetInfo(int colNum) {
	return columns[colNum]->GetInfo();
}

Row::~Row() {
	//Assumption: all elements in valid indices are allocating from the heap.
	for (int i = 0; i < columns.size(); ++i) {
		delete columns[i];
	}
}
