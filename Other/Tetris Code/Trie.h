#ifndef TRIE_H
#define TRIE_H
#include <string>
#define numberOfAlphabets 26

class Trie{
	bool wordEnd;
	Trie *letters[numberOfAlphabets];
	void InsertWords(std::string wordToInsert);
public:
	Trie();
	~Trie();
	void Insert(const std::string &wordsToInsert);
	std::string Find(std::string wordToFind);
};

#endif

