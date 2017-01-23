#ifndef LEVEL_H
#define LEVEL_H

class Grid;

class Level {
public:
	Level();
	virtual int CurrentLevel() = 0; // Returns the level this is on
	virtual char ChooseShape() = 0; // Chooses next shape to create 
									// (either from file or randomly)
	virtual void PostUpdate(Grid &); // Updates for when block is moved or rotated
	virtual void ResetStarCounter(); // Called when Row is annihilated
	virtual void IncrementCounter(Grid &); // Called when Block is dropped 
												// *WITHOUT ANY ANNIHILATE*
	virtual ~Level() = 0; // Destructor
};

Level *PlusPlus(Level *); // Increments the Level if possible
Level *MinusMinus(Level *); // Decrements the Level if possible

#endif
