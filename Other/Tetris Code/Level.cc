#include "Level.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"

Level::Level() {}

void Level::PostUpdate(Grid &g) {}

void Level::ResetStarCounter() {}

void Level::IncrementCounter(Grid &g) {}

Level::~Level() {}

Level *PlusPlus(Level *l){
	if(l->CurrentLevel() == 0){
		delete l;
		l = new Level1();
	}
	else if(l->CurrentLevel() == 1){
		delete l;
		l = new Level2();
	}
	else if(l->CurrentLevel() == 2){
		delete l;
		l = new Level3();
	}
	else if(l->CurrentLevel() == 3){
		delete l;
		l = new Level4();
	}
	else if(l->CurrentLevel() == 4){
		//Do nothing.
	}

	return l;
}

Level *MinusMinus(Level *l){
	if(l->CurrentLevel() == 0){
		//Do nothing.
	}
	else if(l->CurrentLevel() == 1){
		delete l;
		l = new Level0();
	}
	else if(l->CurrentLevel() == 2){
		delete l;
		l = new Level1();
	}
	else if(l->CurrentLevel() == 3){
		delete l;
		l = new Level2();
	}
	else if(l->CurrentLevel() == 4){
		delete l;
		l = new Level3();
	}

	return l;
}
