#include "Level2.h"
#include <iostream>

Level2::Level2(){}

Level2::~Level2(){}

int Level2::CurrentLevel(){ return(2);}

char Level2::ChooseShape(){
	// 7 possibilities from rand()
	int randomShapeNum = (rand() % 7) + 1;
	// Each block has equal probability of occuring
	if(randomShapeNum == 1){
		return 'S';
	}
	else if(randomShapeNum == 2){
		return 'Z';
	}
	else if(randomShapeNum == 3){
		return 'T';
	}
	else if(randomShapeNum == 4){
		return 'I';
	}
	else if(randomShapeNum == 5){
		return 'O';
	}
	else if(randomShapeNum == 6){
		return 'L';
	}
	else if(randomShapeNum == 7){
		return 'J';
	}
}
