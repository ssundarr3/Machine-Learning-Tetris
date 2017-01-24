#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <vector>
#include <string>
#include "Observer.h"
class Subject;
enum class SubscriberType;

class TextDisplay : public Observer {
	
public:

	std::vector<std::vector<char>> allLetters;
	const int NUM_ROWS;
	const int NUM_COLS;
	bool useGra;

	TextDisplay(int, int, bool);
	std::string PrintDisplay();
	void Notify(Subject &) override;
	SubscriberType GetSubscriberType() override;
	~TextDisplay() override;
};

#endif
