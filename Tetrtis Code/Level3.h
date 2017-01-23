#ifndef LEVEL3_H
#define LEVEL3_H

#include "Level.h"
class Grid;

class Level3: public Level {
public:
	Level3();
	int CurrentLevel() override;
	char ChooseShape() override;
	void PostUpdate(Grid &) override;
	~Level3() override;
};

#endif
