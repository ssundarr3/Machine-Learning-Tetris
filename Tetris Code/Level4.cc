#include "Level4.h"
#include "Grid.h"
#include <iostream>
extern std::string norandomBlockSequence;
extern int norandomSequenceIndex;


Level4::Level4(): numBlocksWithoutClear{0}{}

Level4::~Level4(){}

int Level4::CurrentLevel(){ return(4);}

// Called when Row is annihilated
void Level4::ResetStarCounter(){
	numBlocksWithoutClear = 0;
}

// Called when Block is dropped *WITHOUT ANY ANNIHILATE*
void Level4::IncrementCounter(Grid &g){
	// Block has been dropped without clearing row
	// => increment numBlocksWithoutClear
	numBlocksWithoutClear += 1;
	// If numBlocksWithoutClear is equal to NUM_BAD_TURNS, create and drop a '*' block
	if(numBlocksWithoutClear >= NUM_BAD_TURNS){
		g.CreateNewShape('*', CurrentLevel());
		g.DropWindow(CurrentLevel());
		// Reset numBlocksWithoutClear to 0
		ResetStarCounter();
	}
}

void Level4::PostUpdate(Grid &g){
	g.TranslateWindowDown(); // After each command to move or rotate, Postupdate
}

char Level4::ChooseShape(){
	if(norandomSequenceIndex){
		// norandomSequenceIndex initially 1
		char nextShape = norandomBlockSequence[norandomSequenceIndex-1];
		norandomSequenceIndex += 1;
		if(norandomSequenceIndex == (norandomBlockSequence.length() +1)){
			norandomSequenceIndex = 1;
		}
		return(nextShape);
		
	}
	else{
		// 9 Possibilities from rand()
		int randomShapeNum = (rand() % 9) + 1;
		// S and Z have 2/9th chance of occuring
		// Rest of the blocks have 1/9th chance of occuring
		if(randomShapeNum == 1 || randomShapeNum == 2){
			return 'S';
		}
		else if(randomShapeNum == 3 || randomShapeNum == 4){
			return 'Z';
		}
		else if(randomShapeNum == 5){
			return 'T';
		}
		else if(randomShapeNum == 6){
			return 'I';
		}
		else if(randomShapeNum == 7){
			return 'O';
		}
		else if(randomShapeNum == 8){
			return 'L';
		}
		else if(randomShapeNum == 9){
			return 'J';
		}
	}
}
