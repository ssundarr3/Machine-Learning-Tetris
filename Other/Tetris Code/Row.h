#ifndef ROW_H
#define ROW_H

#include <vector>
#include "Subject.h"
#include "Observer.h"

class Cell;
class Info;
class TextDisplay;
class GraphicsDisplay;
class DroppedBlock;
enum class SubscriberType;
enum class SubjectType;

class Row : public Subject, public Observer {
	
public:
	std::vector<Cell *> columns;
	int columnsSize;
	int rowNum;

	
	Row(int, int, TextDisplay *, GraphicsDisplay *);
	void SetCell(int, char);
	void SetCell(int, DroppedBlock *);
	bool IsRowFilled();
	void DetachAllBlocks();
	void Notify(Subject &) override;
	SubscriberType GetSubscriberType() override;
	SubjectType GetSubjectType() override;
	Info GetInfo() override;
	Info GetInfo(int) override;
	~Row() override;
};

#endif
