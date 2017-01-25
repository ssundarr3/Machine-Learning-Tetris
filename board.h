#include <vector>


void updateCoefficients(int index, double x);

int getCoefficient(int index);

class Board {
public:
	std::vector<std::vector<bool>> grid;
	const int width;
	const int height;
	int score;
	void init();
	Board();
	Board(int w, int h);
	//~Board() {
		// do nothing
	//}
	//adds a piece to the board and returns the resulting board's fitness.
	double addPiece(Board b, char piece, int position, int rotation);
	void addPiece(Board * b, char piece, int position, int rotation);
};
