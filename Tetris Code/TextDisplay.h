#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <vector>
#include <string>
#include "Observer.h"
class Subject;
enum class SubscriberType;

class TextDisplay : public Observer {
	std::vector<std::vector<char>> allLetters;
	const int NUM_ROWS;
	const int NUM_COLS;
public:
	TextDisplay(int, int);
	std::string PrintDisplay();
	void Notify(Subject &) override;
	SubscriberType GetSubscriberType() override;
	~TextDisplay() override;
};

#endif
