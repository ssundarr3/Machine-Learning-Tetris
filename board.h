#include <vector>

class Board{
public:
	std::vector<std::vector<bool>> grid;
	const int width;
	const int height;
	int score;
	Board();
	Board(int w, int h);
	//~Board() {
		// do nothing
	//}
	//adds a piece to the board and returns the resulting board's fitness.
	// int addPiece(Board b, char piece, int position, char rotation);
	// void addPiece(Board * b, char piece, int position, char rotation);
};
