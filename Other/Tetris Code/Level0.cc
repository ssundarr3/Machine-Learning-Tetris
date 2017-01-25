#include "Level0.h"
#include <fstream>
extern std::string blocksFileName;

Level0::Level0(){}

char Level0::ChooseShape(){
	if(blockSequence == ""){
		// No more blocks, re-read from file
		std::ifstream file(blocksFileName);
		std::string s;
		while(file >> s){ 
			blockSequence += s;
		}
		file.close();
	}
	// Get first block in blockSequence
	char nextShape = blockSequence[0];
	// Remove the first blockSequence 
	blockSequence = blockSequence.substr(1);
	return(nextShape);
}

int Level0::CurrentLevel(){
	return(0);
}

Level0::~Level0(){}
