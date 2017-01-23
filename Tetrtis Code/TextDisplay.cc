#include "TextDisplay.h"
#include <sstream>
#include "Subject.h"
#include "Info.h"
#include "SubjectType.h"
#include "SubscriberType.h"

TextDisplay::TextDisplay(int numRows, int numCols): NUM_ROWS{numRows}, NUM_COLS{numCols} {
	for (int i = 0; i < NUM_ROWS; ++i) {
		std::vector<char> newRow;

		for (int j = 0; j < NUM_COLS; ++j) {
			newRow.emplace_back(' ');
		}

		allLetters.emplace_back(newRow);
	}
}

std::string TextDisplay::PrintDisplay() {
	std::string textOut = "";

	for (int i = 0; i < NUM_ROWS; ++i) {
		std::string tempRow = "";

		for (int j = 0; j < NUM_COLS; ++j) {
			std::stringstream ss;

			ss << allLetters[i][j];

			std::string tempStr;

			ss >> tempStr;

			if (allLetters[i][j] != ' ') {
				textOut += tempStr;
			} else {
				textOut += " ";
			}
		}

		if (i != (NUM_ROWS - 1)) {
			textOut += "\n";
		}
	}

	return textOut;
}

void TextDisplay::Notify(Subject &notifier) {
	if (notifier.GetSubjectType() == SubjectType::ROW) {
		allLetters.erase(allLetters.begin() + notifier.GetInfo().row);

		std::vector<char> newRow;

		for (int i = 0; i < NUM_COLS; ++i) {
			newRow.emplace_back(' ');
		}

		allLetters.insert(allLetters.begin(), newRow);
	} else if (notifier.GetSubjectType() == SubjectType::CELL) {
		allLetters[notifier.GetInfo().row][notifier.GetInfo().col] = notifier.GetInfo().letter;
	}
}

SubscriberType TextDisplay::GetSubscriberType() {
	return SubscriberType::DISPLAY;
}

TextDisplay::~TextDisplay() {}
