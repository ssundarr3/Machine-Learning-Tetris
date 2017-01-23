#ifndef DROPPED_BLOCK_H
#define DROPPED_BLOCK_H

#include "Observer.h"

class Subject;
enum class SubscriberType;

class DroppedBlock : public Observer {
	const Subject *droppedBlocks[4];
	const int NUM_BLOCKS = 4;
	const int LEVEL_GEN;

public:
	explicit DroppedBlock(int);
	bool AreAllBlocksEmpty();
	int GetLevelGen();
	void Notify(Subject &) override;
	SubscriberType GetSubscriberType() override;
	~DroppedBlock() override;
};

#endif
