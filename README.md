# Machine-Learning-Tetris
A Machine Learning Algorithm that learns to play Tetris

to simply run use ./out

## How it works
### Fitness Function
Uses a fitness function to compute the score of a board.
The fitness computes the score by calculating various features of the board (like max height, number of holes etc).
The fitness function receives a set of weights that determine how important each feature is.
The final score is computed by multiplying a weight with its corresponding feature for each feature.

The algorithm runs the fitness function on all possible next boards, and does the move that has greatest fitness.
(a next board is the current board, with the current piece added in any way)

### Genetic Algorithm
Uses a genetic algorithm to fine-tune the weights that correspond to the features, to find the perfect set of weights that result in maximum height.

### Mutated Weights
The best two weights are taken into the next generation. 

First, coefficients from the two weights are randomly taken to create new weights

Then, random mutations are put in all weights. The amount by which a mutation changes the value is a function of the average score for a generation. Further, mutations which create small changes occur more often, while mutations that create large changes occur less frequently.



##Command line arguments

./out to run

-play to show the play of a single game

   (the following are only applicable if -play has also been given)
	
    -coefficient to give your own coefficients (between -1, 1)
	
    -graphics adds graphics (not yet implemented)
	

-seed to set the seed (initial value is time(NULL))



