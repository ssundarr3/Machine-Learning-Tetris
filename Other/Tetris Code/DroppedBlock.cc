#include "DroppedBlock.h"
#include "Subject.h"
#include "Info.h"
#include "SubscriberType.h"

DroppedBlock::DroppedBlock(int levelGen): LEVEL_GEN{levelGen} {
	for (int i = 0; i < NUM_BLOCKS; ++i) {
		droppedBlocks[i] = nullptr;
	}
}

bool DroppedBlock::AreAllBlocksEmpty() {
	int numBlocksEmpty = 0;

	for (int i = 0; i < NUM_BLOCKS; ++i) {
		if (droppedBlocks[i] == nullptr) {
			++numBlocksEmpty;
		}
	}

	if (numBlocksEmpty == NUM_BLOCKS) {
		return true;
	} else {
		return false;
	}
}

int DroppedBlock::GetLevelGen() {
	return LEVEL_GEN;
}

//Assumption: this function is used under extremely specific circumstances by other classes.
//If not used correctly it would cause problems.
//Assumption: no copy blocks can be stored at more than one index of the droppedBlocks array.
void DroppedBlock::Notify(Subject &notifier) {
	if (notifier.GetInfo().letter != ' ') {
		for (int i = 0; i < NUM_BLOCKS; ++i) {
			if (droppedBlocks[i] == nullptr) {
				droppedBlocks[i] = &notifier;
				break;
			}
		}
	} else {
		for (int i = 0; i < NUM_BLOCKS; ++i) {
			if (droppedBlocks[i] == &notifier) {
				droppedBlocks[i] = nullptr;
				break; //This break added for consistency.
			}
		}
	}
}

SubscriberType DroppedBlock::GetSubscriberType() {
	return SubscriberType::DROPPED;
}

DroppedBlock::~DroppedBlock() {}
