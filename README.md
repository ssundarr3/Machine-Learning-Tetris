# Machine-Learning-Tetris
A Machine Learning Algorithm that learns to play Tetris

![alt text](https://github.com/ssundarr3/Machine-Learning-Tetris/blob/master/pics/TetrisMachineLearning.gif "Machine Learning GIF")



## How it works
### Fitness Function
Uses a fitness function to compute the score of a board.
The fitness function computes the score by calculating various features of the board (like max height, number of holes etc), and multiplies each of these features with a set of weights that determine how important each feature is. It returns the sum of these products.

The algorithm runs the fitness function on all possible next boards, and makes the move that produces greatest fitness.

### Genetic Algorithm
Initially, in a generation, we have a list of say, 30 random weights(A weight is a list of numbers that determine how important each feature is). We run each weight using the fitness function, and map the score(number of lines cleared) to that weight. Then, to get the next list of 30 weights, we mutate the weights.

### Mutated Weights
The best(determined by their score(number of lines cleared)) two weights are taken into the next generation. 

Then, coefficients(a coefficient is a number in a weight) from these two weights are randomly copied to create new weights, until we have the desired number of weights(30 in this example).

Next, random mutations are randomly put in all weights. The amount by which a mutation changes a coefficient is a function of the average score for a generation. Further, mutations which create small changes occur more often, while mutations that create large changes occur less frequently.

Finally, we run the algorithm again, to determine the score for each weight, and continue the process.

Because we are only taking the set of weights that produce the best score, the set of weights will converge on to values that result in the highest number of lines cleared. This is how the algorithm 'learns' to play better with time.

## Understanding output

    score0: .....
    .
    .
    .
    score0:   282 score1:   398 score2:   364 Gen: 9 W: -0.0590602  -0.288204  0.0293877   0.519238 AvgScore(of 3): 348
    score0:  1270 score1:   676 score2:    64 Gen: 9 W: -0.0590602  -0.281186  0.0447034   0.676541 AvgScore(of 3): 670
    score0:   101 score1:  2951 score2:   540 Gen: 9 W: -0.0590602  -0.333541  0.0293877   0.392932 AvgScore(of 3): 1197.33
    --MaxOneAvgScore: 1596.33 MaxOneIndex: 15 MaxOneWeights -0.0591585  -0.288204  0.0367518   0.473326 --
    --MaxTwoAvgScore: 1223.33 MaxTwoIndex: 7 MaxTwoWeights -0.0590602  -0.288204  0.0367518   0.473326 --
    ------- Gen: 9 MaxAvgWtScore: 1596.33 AvgGenScore: 513.253 --------

score0, score1, score2 are the scores from running the weights W: weight1, weight2, ... AvgScore(of 3) is the average of score0, score1, ...

MaxOneAvgScore is the maximum average of the list of weights. MaxOneIndex is the index of the weight being used, MaxOneWeights are the weights of the maximum average.

Gen is the generation number, MaxAvgWtScore is the maximumAverage of the generation, AvgGenScore is the average score of the weights

##Command line arguments

./out to run

-gen numberOfGenerations (default is 100) (might take some time on default settings)

-wts numberOfWeightsPerGeneration (default is 30)

-gpw numberOfGamesPerWeight (default is 3)


-seed to set the seed (initial value is time(NULL))


-play to show the play of a single game

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The following are only applicable if -play has also been given:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-coefficient to give your own coefficients (between -1, 1)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-graphics adds graphics (not yet implemented)


