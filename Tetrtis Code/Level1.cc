#include "Level1.h"
#include <iostream>

Level1::Level1(){}
Level1::~Level1(){}
int Level1::CurrentLevel(){
	return(1);
}

char Level1::ChooseShape(){
	// 7 possibilities from rand()
	int randomShapeNum = (rand() % 12) + 1;
	// S and Z have 1/12th chance of occuring
	// Rest of the blocks have 1/6th chance of occuring
	if(randomShapeNum == 1){
		return 'S';
	}
	else if(randomShapeNum == 2){
		return 'Z';
	}
	else if(randomShapeNum == 3 || randomShapeNum == 4){
		return 'T';
	}
	else if(randomShapeNum == 5 || randomShapeNum == 6){
		return 'I';
	}
	else if(randomShapeNum == 7 || randomShapeNum == 8){
		return 'O';
	}
	else if(randomShapeNum == 9 || randomShapeNum == 10){
		return 'L';
	}
	else if(randomShapeNum == 11 || randomShapeNum == 12){
		return 'J';
	}
}

