#ifndef LEVEL4_H
#define LEVEL4_H

#include "Level.h"
class Grid;

class Level4: public Level {
	// An integer which keeps track of how many blocks have been dropped 
	// without clearning at least one row
	int numBlocksWithoutClear;
	const int NUM_BAD_TURNS = 5;
public:
	Level4();
	int CurrentLevel() override;
	char ChooseShape() override;
	void PostUpdate(Grid &) override;
	void ResetStarCounter() override;
	void IncrementCounter(Grid &) override;

	~Level4() override;
};

#endif
