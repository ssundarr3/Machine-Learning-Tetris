/**************************************************************
 **  Graphical Demonstration of Tetris Machine Learning AI   **
 **************************************************************
 **  Author:  Raymond Zheng                                  **
 **                                                          **
 **  Purpose:  Demonstration of a Tetris Machine Learning AI **
 **                                                          **
 **  Date:  February 3rd, 2017                               **
 **************************************************************/
"use strict";

/**** CONSTANTS ****/
var BOARD_WIDTH = 10; // Num of Columns
var BOARD_HEIGHT = 20; // Number of Rows
var NUM_OF_COEFFICIENTS = 6; // Number of coefficients
var PIECES = [
       [[1,1],         // 0: O
        [1,1]],

       [[1],           // 1: I1
        [1],
        [1],
        [1]],

       [[1, 1, 1, 1]],  // 2: I2

       [[0,1],          // 3: J1
        [0,1],
        [1,1]],

       [[1,0,0],        // 4: J2
        [1,1,1]],

       [[1,1],          // 5: J3
        [1,0],
        [1,0]],

       [[1,1,1],        // 6: J4
        [0,0,1]],

       [[1,0],          // 7: L1
        [1,0],
        [1,1]],

       [[0,0,1],        // 8: L2
        [1,1,1]],

       [[1,1],          // 9: L3
        [0,1],
        [0,1]],

       [[1,1,1],        // 10: L4
        [1,0,0]],

       [[0,1,0],          // 11: T1
        [1,1,1]],

       [[1,0],        // 12: T2
        [1,1],
        [1,0]],

       [[1,1,1],          // 13: T3
        [0,1,0]],

       [[0,1],        // 14: T4
        [1,1],
        [0,1]],

       [[0,1,1],        // 15: S1
        [1,1,0]],

       [[1,0],          // 16: S2
        [1,1],
        [0,1]],

       [[1,1,0],        // 17: Z1
        [0,1,1]],

       [[0,1],          // 18: Z2
        [1,1],
        [1,0]]
    ];

/**** Global Variables ****/
// Board holds the state of the board as it is manipulated by the AI. Type: [char][char]
var Board = [];
var Heights = [];
var coefficients = [-0.1, -0.211556, -0.789805, -0.189805, 0.-0.181566, 0.811782];


/* HELPER FUNCTIONS */


// USING OLD FITNESS FUNCTION
function calculateFitness(board, numCleared){
    var totalHeight = 0, maxHeight = 0, numHoles = 0, numBlockades = 0, heightDifferences = 0;

    // Count from the top
    var heights = [BOARD_WIDTH];
    var prevHeight = 0;
    var currHeight = 0;
    for (var i = 0; i < BOARD_WIDTH; i++) {
        var startCountingHeight = false;
        prevHeight = currHeight;
        currHeight = 0;
        var lastHole = -1;
        for (var j = 0; j < BOARD_HEIGHT; j++) {
            if (board[j][i] != ' ') startCountingHeight = true;
            if (startCountingHeight) {
                currHeight++;
                // Data: Count holes
                if (board[j][i] == ' ') {
                    numHoles++;
                    lastHole = j;
                }
            }
        }
        // Data: Count maximum column height
        if (currHeight > maxHeight) maxHeight = currHeight;
        // Data: Count difference in adjacent column heights.
        if (i != 0) heightDifferences += (currHeight - prevHeight);
        // Data: Count total height.
        totalHeight += currHeight;
        // Data: Count blockades:
        if (lastHole != -1) {
            numBlockades += currHeight - (BOARD_HEIGHT - lastHole);
        }
        heights.push(currHeight);
    }

    // coefficients:   0 = totalHeight -0.1
    //                 1 = maxHeight -0.211556
    //                 2 = numHoles -0.789805
    //                 3 = numBlockades -0.189805
    //                 4 = heightDifferences -0.181566
    //                 5 = numCleared  0.811782

    return coefficients[0] * totalHeight +
           coefficients[1] * maxHeight +
           coefficients[2] * numHoles +
           coefficients[3] * numBlockades +
           coefficients[4] * heightDifferences +
           coefficients[5] * numCleared;
}

/* can be improved by only checking rows that the last piece was inserted in !!
 *  also by using something other than erase, insert.
 */
function removeClears(board, real) {
    var clears = 0;
    for(var i = 0; i < BOARD_HEIGHT; i++) {
        var rowFull = true;
        for(var j = 0; j < BOARD_WIDTH; j++) {
            if(board[i][j] == ' '){
                rowFull = false;
                break;
            }
        }
        if(rowFull){
            clears += 1;
            board.splice(i, 1);
            i--;
            var newRow = [];
            for (var k = 0; k < Heights.length; k++) {
                if (real && Heights[k] > 0) Heights[k]--;
                newRow.push(' ');
            }
            board.splice(0, 0, newRow);
        }
    }
    return clears;
}

function dropPiece(id, col, pieceName) {
    var piece = PIECES[id];
    var row = 20;
    for (var i = 0; i < piece[0].length; i++) {
        var pieceColHeight = 0;
        for (var j = 0; j < piece.length; j++) {
            if (piece[j][i] == 1) {
                pieceColHeight = j;
            }
        }
        var diff = BOARD_HEIGHT - Heights[col + i] - pieceColHeight;
        if (diff < row) {
            row = diff;
        }
    }
    row--;
    for (var i = 0; i < piece.length; i++) {
        for (var j = 0; j < piece[0].length; j++) {
            if (piece[i][j]) {
                Board[row + i][col + j] = pieceName;
                Heights[col + j]++;
            }
        }
    }
}

function removePiece() {
    for (var i = 0; i < Board.length; i++) {
        for (var j = 0; j < Board[0].length; j++) {
            if (Board[i][j] == 'N') {
                Board[i][j] = ' ';
                Heights[j]--;
            }
        }
    }
}

function gameOver() {
    for (var i = 0; i < BOARD_WIDTH; i++) {
        if (Board[1][i] + "" != ' ') return true;
    }
    return false;
}

function findBest(pieceIDs, pieceName) {
    var bestID = pieceIDs[0], bestCol = 0, bestScore = -500;
    for (var i = 0; i < pieceIDs.length; i++) {
        for (var j = 0; j < BOARD_WIDTH - PIECES[pieceIDs[i]][0].length; j++) {
            dropPiece(pieceIDs[i], j, 'N');
            var board = [];
            for (var a = 0; a < Board.length; a++) {
                var newRow = [];
                for (var b = 0; b < Board[0].length; b++) {
                    newRow.push(Board[a][b]);
                }
                board.push(newRow);
            }
            var numCleared = removeClears(board, false);
            var score = calculateFitness(board, numCleared);
            removePiece();
            if (score > bestScore) {
                bestID = pieceIDs[i];
                bestCol = j;
                bestScore = score;
            }
        }
    }
    dropPiece(bestID, bestCol, pieceName);
    removeClears(Board, true);
}

function generateFindBest() {
    var piece = Math.floor((Math.random() * 7) + 1);
    if (piece == 1) findBest([0], 0);                   // O
    else if (piece == 2) findBest([1, 2], 1);           // I
    else if (piece == 3) findBest([3, 4, 5, 6], 2);     // J
    else if (piece == 4) findBest([7, 8, 9, 10], 3);    // L
    else if (piece == 5) findBest([11, 12, 13, 14], 4); // T
    else if (piece == 6) findBest([15, 16], 5);         // S
    else if (piece == 7) findBest([17, 18], 6);         // Z
}


function draw() {
    for (var i = 0; i < BOARD_HEIGHT; i++) {
        for (var j = 0; j < BOARD_WIDTH; j++) {
            if (Board[i][j] >= "0" && Board[i][j] <= "6") {
                drawPiece(j, i, Board[i][j]);
            }
        }
    }
}

function initialize() {
    if (Heights.length != 0) {
        for (var i = 0; i < Heights.length; i++) {
            Heights.pop();
        }
    }
    for (var i = 0; i < BOARD_WIDTH; i++) {
        Heights.push(0);
    }

    for (var i = 0; i < BOARD_HEIGHT; i++) {
        var newRow = [];
        for (var j = 0; j < BOARD_WIDTH; j++) {
            newRow.push(' ');
        }
        Board.push(newRow);
    }
}

function printBoard() {
    var output = "____________\n";
    for (var i = 0; i < BOARD_HEIGHT; i++) {
        output += i+"|";
        for (var j = 0; j < BOARD_WIDTH ; j++) {
            output += Board[i][j];
        }
        output += "|\n";
    }
    output += "____________";
    console.log(output);
}

var gameInterval;

// Runs the simulation on board board, and using weights 'weights' and returns the _total_ number of lines cleared
function runSimulation() {
    generateFindBest();
    draw();
    printBoard();
    if (gameOver()) {
        console.log("Game Over.");
        clearInterval(gameInterval);
    }
}

initialize();
printBoard()
draw();
console.log("Game Start!\n");
setTimeout(function() {
    gameInterval = setInterval(runSimulation, 1);
}, 2000);
