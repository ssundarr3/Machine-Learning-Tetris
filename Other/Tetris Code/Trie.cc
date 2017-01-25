#include "Trie.h"
#include <sstream>

// Constructor which initializes each array
Trie::Trie(){
	for(int i = 0; i < numberOfAlphabets; i++){
		letters[i] = 0;
	}
	wordEnd = false;
}

// Inserts words into Trie. Each word in wordsToInsert is separated by whitespace
void Trie::Insert(const std::string &wordsToInsert){
	std::stringstream iss(wordsToInsert);
	std::string wordToInsert;
	while(iss >> wordToInsert){
		InsertWords(wordToInsert);
	}
}

// Inserts wordToInsert in Trie
void Trie::InsertWords(std::string wordToInsert){
	int letterInsertPosition = toupper(wordToInsert[0]) - 'A';
	if (!letters[letterInsertPosition]){ 
		letters[letterInsertPosition] = new Trie;
	}

	if (wordToInsert.length() == 1){
		letters[letterInsertPosition]->wordEnd = true;
	} else{
		letters[letterInsertPosition]->InsertWords(wordToInsert.substr(1));
	}
}

// Finds command, and returns the complete command
// If there are multiple possible complete commands or if command DNE, returns ""
std::string Trie::Find(std::string wordToFind){
	Trie *cur = this;
	std::string fullWord;
	for (int i = 0; wordToFind[i] != '\0'; i++) {
		int pos =  wordToFind[i] - 'A';
		if (pos < 0 || pos > 25 || !cur->letters[pos]) return ""; // Return if word not found
		cur = cur->letters[pos];
		fullWord += wordToFind[i];
	}
	// If word ends at end of wordToFind, return it.
	if(cur->wordEnd) return fullWord;
	// Otherwise, find the rest of the letters of the command
	int numDiffWords = 0;
	int indexLetter = -1;
	while(!cur->wordEnd){
		numDiffWords = 0;
		for(int i=0; i<numberOfAlphabets; ++i){
			if(cur->letters[i]){
				numDiffWords += 1;
				indexLetter = i;
			}
		}
		// If there are more than one possible commands, return ""
		if(numDiffWords > 1){
			return "";
		}
		cur = cur->letters[indexLetter];
		fullWord += ('A' + indexLetter);
	}
	return fullWord;
}

// Destructor, deletes all Nodes in Trie
Trie::~Trie(){
	for (int i = 0; i < numberOfAlphabets; i++) { 
		if (this->letters[i]) {
			delete this->letters[i]; 
		}
	}
}


