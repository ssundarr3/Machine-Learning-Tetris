#ifndef LEVEL0_H
#define LEVEL0_H

#include "Level.h"
#include <string>

class Level0: public Level {
	// A string containing entire block sequence in global sequence file
	// Stored consecutively
	std::string blockSequence = "";
public:
	Level0();
	int CurrentLevel() override;
	char ChooseShape() override;
	~Level0() override;
};

#endif
