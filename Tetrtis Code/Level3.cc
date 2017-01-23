#include "Level3.h"
#include "Grid.h"
#include <iostream>
extern std::string norandomBlockSequence;
extern int norandomSequenceIndex;

Level3::Level3(){}

Level3::~Level3(){}

int Level3::CurrentLevel(){ return(3);}

void Level3::PostUpdate(Grid &g){
	g.TranslateWindowDown(); // After each command to move or rotate, Postupdate
}

char Level3::ChooseShape(){
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
