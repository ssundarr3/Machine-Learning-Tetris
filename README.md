# Machine-Learning-Tetris
A Machine Learning Algorithm that learns to play Tetris

to simply run use ./out

Uses a fitness function to compute the score of a board.
The fitness computes the score by calculating various features of the board (like max height, number of holes etc).
The fitness function receives a set of weights that determine how important each feature is.
The final score is computed by multiplying a weight with its corresponding feature for each feature.

The algorithm runs the fitness function on all possible next boards, and does the move that has greatest fitness.
(a next board is the current board, with the current piece added in any way)

Uses a genetic algorithm to fine-tune the weights that correspond to the features, to find the perfect set of weights that result in maximum height.

Command line arguments
-play for showing a single game
	(the following are only applicable if -play has also been given
	-coefficient to give your own coefficients (between -1, 1)
	-graphics adds graphics (not yet implemented)
	
-seed to set the seed (initial value is time(NULL))

