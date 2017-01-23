#ifndef LEVEL2_H
#define LEVEL2_H

#include "Level.h"

class Level2: public Level {
public:
	Level2();
	int CurrentLevel() override;
	char ChooseShape() override;
	~Level2() override;
};

#endif
