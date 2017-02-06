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
var NUM_OF_COEFFICIENTS = 7; // Number of coefficients
var NUM_EXTRA_PIECES = 0;
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
        [1,0]]//,
      //
      // [[1, 0],
      //  [1, 1]]
    ];
var nameToIDMap = [[0],                     // O
                   [1,2],                   // I
                   [3, 4, 5, 6],            // J
                   [7, 8, 9, 10],           // L
                   [11, 12, 13, 14],        // T
                   [15, 16],                // S
                   [17, 18]];               // Z
                                            // X Initialized in Initialization.

/**** Global Variables ****/
// Board holds the state of the board as it is manipulated by the AI. Type: [char][char]
var Board = [];
var totalScore = 0;
var gameSpeed = 1;

// Coefficients:
//     coefficients[0] * heightDifferences +
//     coefficients[1] * numHoles +
//     coefficients[2] * (BOARD_HEIGHT - maxHeight) +
//     coefficients[3] * numCleared +
//     coefficients[4] * firstHeight +
//     coefficients[5] * lastHeight +
//     coefficients[6] * numBlockades;
var coefficients = [
    -0.192716,
    -1,
    0.00742194,
    0.292781,
    0.182602,
    0.175692,
    -0.0439177];

/* can be improved by only checking rows that the last piece was inserted in !!
 *  also by using something other than erase, insert.*/
function removeClears(board, real) {
    var clears = 0;
    for(var i = 0; i < BOARD_HEIGHT; i++) {
        var rowFull = true;
        for(var j = 0; j < BOARD_WIDTH; j++) {
            if(board[i][j] == -1){
                rowFull = false;
                break;
            }
        }
        if(rowFull){
            clears += 1;
            board.splice(i, 1);
            i--;
            var newRow = [];
            for (var k = 0; k < board[0].length; k++) {
                newRow.push(-1);
            }
            board.splice(0, 0, newRow);
        }
    }
    return clears;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function dropPiece(board, pieceID, col, pieceName){

    var piece = PIECES[pieceID];

    for(var i = 0; i <= BOARD_HEIGHT - piece.length; i++){
        if ( !canDropPiece(board, i, col, pieceID)) {
            if(i == 0) {
                // clearInterval(gameInterval);
                return false;
            }
            else {
                if (i <= 1) return false;
                dropPieceAt(board, i - 1, col, pieceID, pieceName);
                return true;
            }
        }
    }

    if(canDropPiece(board, BOARD_HEIGHT - piece.length, col, pieceID)){
        dropPieceAt(board, BOARD_HEIGHT - piece.length, col, pieceID, pieceName);
        return true;
    }

    return false;
}

// Returns true if piece can be dropped in row, col. If pieceName != 8, then makes the actual drop.
function canDropPiece(board, row, col, pieceID){

    var piece = PIECES[pieceID];

    for(var i = 0; i < piece.length; i++) {
        for (var j = 0; j < piece[i].length; j++) {
            if (piece[i][j] && Board[row + i][col + j] != -1) return false;
        }
    }
    return true;

}

// Drops piece at location row, col with character pieceChar, rotation rot
function dropPieceAt(board, row, col, pieceID, pieceName){
    var piece = PIECES[pieceID];

    for(var i = 0; i < piece.length; i++){
        for(var j = 0; j < piece[i].length; j++){
            if(piece[i][j]) board[row + i][col + j] = pieceName;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function removePiece() {
    for (var i = 0; i < Board.length; i++) {
        for (var j = 0; j < Board[i].length; j++) {
            if (Board[i][j] == 8) {
                Board[i][j] = -1;
                // Heights[j]--;
            }
        }
    }
}

function gameOver() {
    for (var i = 0; i < BOARD_WIDTH; i++) {
        if (Board[0][i] + "" != -1) return true;
    }
    return false;
}

function generateRandomPiece() {
    return Math.floor(Math.random() * nameToIDMap.length);
}

var manualTest = {
// MANUAL TESTING
// var randString = "4 2 5 4 7 4 1 6 2 3 2 3 4 5 5 7 6 6 7 6 5 2 4 5 1 3 3 4 3 6 5 5 5 2 2 6 6 7 1 4 2 7 4 4 5 3 3 3 6 7 5 3 5 7 5 7 2 1 1 4 4 5 7 2 7 1 6 3 7 6 4 7 4 1 3 7 1 6 1 3 2 4 4 7 3 2 4 3 1 6 4 4 1 4 3 1 4 7 1 2 2 4 1 4 2 1 1 2 3 1 3 4 2 5 3 6 6 6 6 6 2 1 1 2 4 4 7 5 1 6 6 1 2 6 2 3 3 2 3 6 1 3 1 2 1 1 4 6 6 1 3 4 2 1 4 3 2 3 1 3 5 6 3 7 7 4 7 2 3 7 4 3 2 4 3 7 3 5 3 7 7 3 4 5 3 7 1 6 7 2 6 6 4 7 2 2 1 7 1 3 5 6 4 5 5 5 6 1 2 7 1 5 2 2 4 3 5 6 7 6 4 2 1 6 5 7 5 5 5 7 5 6 2 7 1 7 3 6 1 6 3 5 3 2 6 6 4 3 7 1 6 3 2 3 6 7 3 2 3 1 5 7 3 7 5 3 5 2 1 4 4 1 7 4 2 4 1 4 4 7 4 2 7 4 2 3 3 4 4 4 6 2 3 7 1 1 3 4 7 1 1 1 5 6 6 7 2 3 1 3 1 6 2 7 1 4 2 1 7 3 4 4 4 4 2 4 6 2 1 2 7 5 3 6 1 7 2 7 2 3 3 7 6 4 7 3 7 5 3 6 2 6 5 3 1 6 7 3 5 6 6 6 1 7 7 1 4 2 1 3 2 1 3 5 4 7 1 2 3 1 4 2 6 2 6 4 7 4 5 3 5 1 5 5 6 6 4 1 4 4 4 6 4 4 3 5 3 1 6 6 2 5 7 4 7 4 7 4 6 4 7 3 4 6 1 7 2 4 7 4 5 1 1 7 4 2 3 5 2 6 2 3 3 5 6 1 2 4 4 5 6 3 5 7 6 4 5 6 6 6 1 3 4 5 1 7 7 3 4 7 5 6 2 1 1 5 1 2 1 6 6 6 6 3 4 1 4 2 6 1 6 3 4 1 1 2 6 5 2 1 6 7 3 4 1 3 1 5 2 1 1 4 3 4 5 6 4 7 4 5 1 1 1 4 5 5 3 4 4 4 2 1 4 6 3 2 6 3 6 6 3 5 1 3 2 6 7 3 4 4 5 4 2 5 6 1 2 7 2 4 4 3 2 7 6 4 5 3 5 3 7 5 5 7 2 6 4 5 7 1 2 6 2 4 1 7 2 1 5 3 4 2 6 6 5 3 2 4 3 7 6 2 4 3 5 6 1 1 3 6 5 3 3 7 4 1 5 6 1 6 6 2 4 7 7 3 2 5 4 2 3 1 3 5 4 7 3 2 6 4 5 3 4 5 2 7 7 5 2 6 3 5 6 5 6 4 5 6 7 3 5 2 3 7 1 4 4 1 6 1 4 4 3 7 7 2 4 4 7 6 2 7 1 4 5 4 7 2 1 5 4 5 6 6 3 6 1 5 5 4 5 7 6 5 6 4 1 1 1 6 4 7 6 2 3 1 6 7 2 6 3 5 2 7 3 4 6 1 1 1 2 5 7 5 3 2 1 3 1 5 7 4 6 4 6 6 2 1 2 4 6 4 2 4 1 2 5 6 7 5 3 7 2 1 3 4 2 3 4 2 5 2 3 3 3 5 6 6 5 5 1 1 2 7 6 1 5 1 6 3 4 5 2 6 5 6 7 6 6 1 7 4 2 2 4 6 6 2 2 3 7 2 4 7 5 5 7 4 5 2 5 2 6 5 4 3 3 1 1 7 2 6 3 1 4 7 6 2 5 4 4 3 3 6 7 1 3 4 2 1 5 5 7 1 4 2 4 4 2 2 3 1 4 4 2 7 1 4 1 4 1 3 5 3 7 5 2 3 2 3 1 6 1 5 5 2 7 7 6 1 5 5 2 2 7 1 5 7 4 7 1 4 7 5 6 4 2 5 4 2 5 6 5 6 3 2 5 2 5 4 7 4 7 5 6 5 5 4 6 3 1 3 4 6 1 1 1 1 4 6 2 3 7 7 7 2 7 3 1 6 4 7 2 3 5 4 1 2 6 3 4 3 6 5 7 5 4 5 4 1 3 6 1 2 2 6 1 1 7 5 5 4 6 6 5 1 5 6 3 4 7 4 4 6 2 4 1 4 7 4 4 7 5 2 5 7 5 5 1 3 2 4 4 4 5 1 6 4 6 6 6 2 1 2 4 1 3 2 4 2 6 6 1 1 4 4 1 7 7 5 2 1 2 4 4 6 4 5 1 5 3 4 7 2 6 2 7 6 3 1 4 5 6 2 5 1 6 5 7 4 4 5 4 3 2 7 7 3 4 5 5 5 2 5 6 4 7 2 5 2 2 2 6 4 3 4 4 7 2 1 1 5 6 4 5 4 1 5 7 4 2 6 1 1 1 3 2 6 6 7 6 5 1 2 3 1 6 4 6 6 3 6 1 7 5 5 3 5 2 2 1 3 6 5 1 3 1 2 1 6 1 3 2 5 4 2 5 7 3 1 4 6 6 4 4 3 2 7 7 2 5 6 2 1 3 3 4 3 4 2 5 3 4 6 1 6 5 6 4 1 6 6 4 3 1 7 3 1 4 7 2 1 4 3 1 5 3 2 2 7 3 6 2 4 2 7 2 6 4 3 3 2 1 5 2 5 5 2 5 7 2 6 7 6 5 1 4 1 7 3 6 1 7 4 4 5 2 3 3 6 4 6 4 4 4 3 7 7 6 4 5 4 1 5 1 4 4 2 3 1 4 7 1 1 2 6 5 3 6 5 6 1 4 2 2 6 2 2 4 5 6 7 2 3 3 1 6 5 2 7 7 4 4 6 4 6 2 1 6 7 5 3 6 7 2 7 2 3 5 6 2 3 3 1 3 6 5 7 2 1 4 5 4 1 3 6 3 6 3 5 2 2 1 4 5 2 3 1 4 1 3 3 1 6 2 2 1 7 5 2 6 3 7 5 1 2 4 1 4 5 5 3 6 4 7 2 6 2 2 7 1 4 7 5 7 1 6 7 5 4 5 3 4 6 7 2 4 3 2 1 5 5 3 2 2 7 3 6 7 2 4 7 6 3 3 2 2 1 5 6 4 4 6 6 5 4 5 3 4 7 1 1 3 3 2 6 3 2 2 2 3 3 5 6 3 5 7 2 5 3 5 7 7 4 4 3 7 2 6 4 7 6 2 2 5 3 4 5 4 3 6 4 6 1 1 1 5 6 2 3 1 5 2 6 2 4 7 5 6 3 7 2 6 1 2 3 3 6 5 4 1 3 7 3 1 1 3 7 3 3 7 3 1 1 7 7 2 6 6 6 7 3 5 2 3 7 6 4 3 1 6 3 2 6 3 2 3 5 5 6 5 6 5 4 4 3 3 6 7 6 2 4 7 5 5 3 3 1 4 6 5 1 6 7 6 1 7 6 4 6 1 7 1 5 3 2 1 3 4 5 7 4 7 7 2 6 7 2 3 3 7 2 3 2 5 5 7 6 1 3 1 1 2 5 4 2 7 3 4 1 1 4 4 7 1 3 3 6 6 3 7 2 4 7 1 3 6 1 6 4 3 6 4 3 3 1 4 7 3 5 1 1 7 2 7 7 3 7 4 6 3 1 5 4 6 4 4 1 4 2 4 6 4 7 7 6 6 1 4 7 5 2 7 6 2 6 2 4 2 3 1 4 3 4 1 5 7 2 5 2 3 2 5 6 1 6 2 5 3 3 3 7 3 1 4 4 3 4 6 4 5 3 5 7 4 4 6 3 6 3 4 5 2 7 3 2 4 4 6 6 4 5 4 5 5 6 7 5 1 4 2 6 5 6 4 2 1 5 3 5 5 4 4 7 4 4 1 6 7 4 2 1 2 3 7 6 1 5 3 1 1 2 6 4 6 5 4 6 4 4 1 2 7 2 5 1 6 6 4 2 1 3 3 7 5 2 2 5 6 2 4 6 1 7 2 6 6 6 3 7 1 3 5 6 6 6 4 2 2 7 4 7 2 5 5 7 6 7 3 2 1 7 7 1 5 5 5 3 3 5 7 1 1 5 6 3 3 1 3 2 6 4 1 7 7 5 4 4 3 7 6 1 5 2 5 2 7 2 2 7 7 2 7 5 6 3 1 7 1 1 1 5 4 5 6 3 2 5 4 4 6 2 4 1 1 7 7 5 2 2 3 1 1 1 5 6 3 6 4 1 3 2 5 7 7 1 7 1 7 4 2 4 3 3 3 3 2 2 5 3 3 2 2 3 2 6 7 2 7 1 2 3 7 5 7 4 5 5 2 6 2 1 7 2 3 2 3 6 3 1 6 4 7 5 4 5 4 2 6 3 2 6 3 7 3 2 3 1 1 3 4 7 3 3 7 5 2 2 1 2 7 3 6 7 7 7 3 1 1 1 1 7 6 4 5 6 6 7 3 3 7 5 1 2 5 7 6 7 1 3 7 7 4 4 4 3 3 7 3 1 6 3 1 2 4 5 4 2 3 5 2 2 3 2 2 1 1 4 5 5 7 6 4 3 5 7 6 7 5 6 7 3 6 7 2 2 4 6 3 4 2 2 4 4 4 6 4 2 1 7 1 6 4 4 7 1 1 2 7 6 4 4 7 2 2 7 3 3 2 3 5 3 4 7 5 6 4 3 6 3 7 6 7 2 5 6 2 4 4 5 1 5 2 5 7 1 6 7 3 5 2 7 7 3 5 6 5 1 6 3 1 6 6 6 5 1 7 7 4 4 3 6 2 2 3 5 3 6 6 3 1 4 7 7 4 4 6 2 4 2 4 2 4 1 5 2 1 5 5 6 7 1 7 5 3 7 4 3 4 5 3 2 7 3 2 3 5 5 6 7 6 5 1 7 7 4 1 7 2 7 2 5 6 5 4 6 6 6 6 5 3 1 1 2 1 2 3 4 6 7 3 7 6 1 5 2 2 7 7 4 4 1 7 5 7 4 2 2 1 5 1 2 4 1 1 4 2 3 7 4 2 7 3 6 7 2 5 7 5 3 3 7 4 7 6 1 3 5 2 2 3 7 3 5 7 1 3 5 4 7 2 3 7 6 7 4 4 4 3 7 5 3 5 7 3 1 6 3 6 6 2 7 4 2 6 4 3 6 2 5 3 2 1 7 5 5 3 7 7 4 5 3 4 4 1 4 2 6 6 5 2 5 6 5 1 1 7 1 3 5 5 6 7 4 2 3 7 3 2 4 5 6 6 7 5 3 4 1 7 1 5 7 5 4 3 4 2 2 4 4 7 7 7 6 2 1 7 5 3 7 1 5 4 3 5 3 6 7 3 2 7 1 1 3 2 1 6 3 7 5 6 6 4 4 2 3 2 1 1 6 7 5 1 2 1 4 4 6 3 4 7 2 2 6 3 4 4 7 4 3 6 1 7 1 4 5 3 5 7 2 1 4 7 5 3 5 3 4 1 6 7 6 6 2 3 7 3 5 5 5 5 1 7 5 2 1 4 2 4 1 1 2 3 5 1 3 4 3 7 4 7 5 2 4 6 2 3 7 6 5 4 3 7 1 5 5 1 1 6 6 5 5 5 5 4 4 2 7 5 1 1 4 4 2 6 2 1 5 5 6 4 7 1 1 7 4 4 1 4 2 3 3 6 5 5 1 3 7 6 1 7 3 2 2 3 7 1 3 6 5 1 1 4 5 7 3 2 3 1 5 2 3 5 5 2 4 4 2 2 1 7 1 2 2 2 4 1 2 5 6 5 5 3 2 4 7 2 4 3 3 7 4 6 6 1 4 5 4 6 7 3 6 5 4 4 6 7 4 6 3 5 1 2 5 2 3 5 1 4 5 3 3 7 1 6 7 2 4 4 6 1 4 7 5 7 3 2 4 4 5 5 7 5 6 3 6 5 1 6 2 4 1 3 4 5 7 1 6 1 2 2 2 6 1 6 2 1 5 6 2 4 2 1 7 4 4 4 2 2 7 2 5 6 4 7 1 1 7 6 2 2 6 3 5 3 6 5 4 4 1 6 6 2 4 6 5 7 5 6 5 3 4 4 7 6 1 6 5 1 1 7 7 6 7 3 7 4 1 1 6 2 4 3 3 7 6 5 5 1 2 4 4 6 5 1 3 5 5 5 4 5 3 3 1 2 5 6 3 5 5 1 7 2 1 1 1 6 4 4 6 6 6 5 1 1 7 3 7 3 5 3 5 1 5 5 2 2 3 2 7 5 7 6 6 7 6 3 2 5 5 6 4 2 3 4 2 2 4 5 2 2 2 7 7 6 6 1 5 5 7 3 4 7 7 7 4 2 2 5 1 1 3 2 7 3 3 1 3 4 7 4 3 5 4 2 1 5 7 4 4 5 5 5 3 4 3 7 6 4 6 3 2 6 2 1 6 4 7 7 7 4 4 7 2 6 1 7 3 6 3 6 4 5 1 4 7 3 3 6 5 6 6 5 7 7 5 6 1 6 4 5 1 6 6 7 7 4 4 1 1 4 3 2 3 3 5 7 3 5 4 5 4 7 4 1 4 1 6 4 6 7 2 4 2 6 1 2 1 6 2 5 1 4 1 1 4 4 1 4 2 2 2 3 5 4 4 2 4 5 4 5 3 6 7 6 7 1 4 7 3 3 5 1 4 4 2 7 7 7 3 1 5 2 2 6 6 6 4 1 1 7 7 4 3 5 5 2 4 2 7 5 4 3 7 7 5 5 4 6 3 4 3 5 6 4 3 3 5 6 3 7 4 7 1 4 4 5 5 7 6 3 4 5 6 1 3 3 4 4 6 5 7 7 4 4 2 6 4 6 2 7 4 3 4 2 7 6 6 3 3 7 6 5 6 2 4 6 2 7 1 5 3 7 3 4 2 2 1 6 7 7 2 1 1 4 1 7 1 6 7 3 6 4 5 7 3 2 3 2 1 3 6 1 1 7 6 7 7 3 4 5 1 5 4 1 7 4 6 7 7 4 3 4 6 1 1 7 1 3 5 5 4 3 7 2 2 2 1 5 4 4 2 4 7 5 4 5 7 5 5 5 2 5 7 4 4 1 1 4 1 5 3 4 1 7 6 1 1 6 5 2 7 1 5 4 4 7 3 3 4 5 7 6 2 5 2 6 4 7 7 6 5 7 5 5 5 2 5 4 5 3 6 3 3 1 7 4 5 7 4 2 3 3 4 2 2 3 4 6 3 3 7 1 7 5 5 3 7 3 5 3 6 2 4 6 7 3 1 6 7 2 4 7 6 1 5 4 3 2 5 3 3 5 3 2 4 7 3 1 2 5 3 4 7 5 1 6 5 5 7 3 7 4 7 4 4 6 6 4 7 4 7 7 2 7 5 3 5 1 3 6 7 6 1 4 2 5 1 7 2 1 1 2 4 7 3 6 6 1 5 2 4 3 1 3 3 5 6 5 7 6 4 4 2 2 7 1 5 5 5 7 5 5 1 7 6 2 2 7 7 7 1 3 1 5 3 3 6 6 5 2 2 7 6 1 7 2 2 6 7 7 2 3 3 1 2 7 2 1 6 1 5 3 1 5 2 3 5 4 7 4 3 1 4 7 5 3 5 7 6 5 4 5 1 5 5 1 4 7 1 1 6 5 3 6 4 2 6 7 6 2 4 7 7 6 4 5 7 3 3 2 5 7 7 4 6 5 4 1 3 3 5 5 5 2 1 1 1 4 7 4 6 3 3 3 7 6 5 4 6 1 6 1 7 6 4 6 1 5 3 1 5 2 5 4 1 6 4 1 1 4 4 3 4 6 6 2 7 1 6 4 2 1 4 5 3 6 1 1 3 4 1 5 3 6 3 3 7 4 1 7 6 3 7 7 7 3 1 5 3 3 7 2 3 1 1 3 6 1 3 5 2 2 2 4 4 4 4 3 5 6 2 3 7 5 2 4 1 2 7 4 3 5 6 3 4 6 5 5 4 1 2 6 7 4 7 3 6 3 6 3 7 4 5 4 3 6 7 3 6 5 4 7 2 2 2 3 4 6 2 7 4 3 3 3 4 2 5 2 4 1 4 2 3 7 6 3 6 3 6 2 5 7 1 1 1 7 3 2 6 2 7 5 6 2 1 5 1 4 7 4 3 2 3 6 1 5 7 6 1 2 4 5 1 2 4 5 2 7 5 4 5 6 2 1 5 7 7 5 2 5 7 4 6 1 5 5 5 3 1 4 4 3 7 3 4 4 5 3 1 4 4 5 1 3 7 4 3 5 7 2 2 6 6 6 6 1 1 1 3 1 4 4 3 3 5 6 4 3 7 4 4 2 1 3 4 7 5 4 3 4 6 2 1 7 5 3 7 5 3 2 6 4 4 6 4 2 2 1 2 7 2 5 1 2 1 2 5 4 5 1 7 1 1 7 5 4 2 6 1 2 6 3 6 1 7 7 7 7 7 2 4 5 6 2 1 6 3 5 1 5 6 5 7 6 3 6 5 3 7 5 4 2 1 7 7 5 5 7 3 3 5 5 1 3 7 5 6 7 6 3 5 2 1 3 4 ";
// var randInput = randString.split(" ");
// var randIndex = 0;
}

function draw() {
    drawReset();
    for (var i = 0; i < BOARD_HEIGHT; i++) {
        for (var j = 0; j < BOARD_WIDTH; j++) {
            if (Board[i][j] >= 0 && Board[i][j] <= nameToIDMap.length) {
                drawPiece(j, i, Board[i][j]);
            }
        }
    }
}

function initialize() {
    for (var i = 0; i < BOARD_HEIGHT; i++) {
        var newRow = [];
        for (var j = 0; j < BOARD_WIDTH; j++) {
            newRow.push(-1);
        }
        Board.push(newRow);
    }
    var arr = [];
    for (var i = 19; i < PIECES.length; i++) {
        arr.push(i);
    }
    if (arr.length > 0) nameToIDMap.push(arr); // X

}

function printBoard() {
    var output = "____________\n";
    for (var i = 0; i < BOARD_HEIGHT; i++) {
        output += "|";
        for (var j = 0; j < BOARD_WIDTH ; j++) {
            if (Board[i][j] != -1) {
                output += Board[i][j];
            }
            else {
                output += ' ';
            }
        }
        output += "|\n";
    }
    output += "____________";
    console.log(output);
}

function calculateFitness(board, numCleared){
    var totalHeight = 0,
        maxHeight = 0,
        numHoles = 0,
        numBlockades = 0,
        heightDifferences = 0,
        firstHeight = 0,
        lastHeight = 0;
    // Calculate: firstHeight & lastHeight:
    for (var i = 0; i < BOARD_HEIGHT; i++) {
        if (Board[i][0] != -1) {
            firstHeight = BOARD_HEIGHT - i;
            break;
        }
    }
    for (var i = 0; i < BOARD_HEIGHT; i++) {
        if (Board[i][BOARD_WIDTH - 1] != -1) {
            lastHeight = BOARD_HEIGHT - i;
            break;
        }
    }

    // Calculate: the rest:
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
            if (board[j][i] != -1) startCountingHeight = true;
            if (startCountingHeight) {
                currHeight++;
                // Data: Count holes
                if (board[j][i] == -1) {
                    numHoles++;
                    lastHole = j;
                }
            }
        }
        // Data: Count maximum column height
        if (currHeight > maxHeight) maxHeight = currHeight;
        // Data: Count difference in adjacent column heights.
        if (i != 0) heightDifferences += Math.abs(currHeight - prevHeight);
        // Data: Count total height.
        totalHeight += currHeight;
        // Data: Count blockades:
        if (lastHole != -1) {
            numBlockades += currHeight - (BOARD_HEIGHT - lastHole);
        }
        heights.push(currHeight);
    }
    var fitness =   coefficients[0] * heightDifferences +
                    coefficients[1] * numHoles +
                    coefficients[2] * (BOARD_HEIGHT - maxHeight) +
                    coefficients[3] * numCleared +
                    coefficients[4] * firstHeight +
                    coefficients[5] * lastHeight +
                    coefficients[6] * numBlockades;
    if (secondLevel) {
        return fitness;
    }
    else {
        secondLevel = true;

        var pieceName = nextPiece;
        var pieceIDs = nameToIDMap[pieceName];
        var bestID = pieceIDs[0], bestCol = 0, bestScore = -999999;
        for (var i = 0; i < pieceIDs.length; i++) {
            for (var j = 0; j <= BOARD_WIDTH - PIECES[pieceIDs[i]][0].length; j++) {
                // copy board
                var board2 = [];
                for (var a = 0; a < board.length; a++) {
                    var newRow = [];
                    for (var b = 0; b < board[0].length; b++) {
                        newRow.push(board[a][b]);
                    }
                    board2.push(newRow);
                }

                if ( !dropPiece(board2, pieceIDs[i], j, 8) ) {
                    continue;
                }
                var numCleared = removeClears(board2, true);
                var score = calculateFitness(board2, numCleared);
                if (score > bestScore) {
                    bestScore = score;
                }
            }
        }

        return fitness + bestScore;
    }
}


var currPiece = generateRandomPiece();
var nextPiece;
var secondLevel = false;

function findBest(board, piece) {
    var pieceName = piece;
    var pieceIDs = nameToIDMap[pieceName];
    var bestID = pieceIDs[0], bestCol = 0, bestScore = -999999;
    for (var i = 0; i < pieceIDs.length; i++) {
        for (var j = 0; j <= BOARD_WIDTH - PIECES[pieceIDs[i]][0].length; j++) {
            secondLevel = false;
            // copy board
            var board2 = [];
            for (var a = 0; a < board.length; a++) {
                var newRow = [];
                for (var b = 0; b < board[0].length; b++) {
                    newRow.push(board[a][b]);
                }
                board2.push(newRow);
            }

            if ( !dropPiece(board2, pieceIDs[i], j, 8) ) {
                continue;
            }

            var numCleared = removeClears(board2, true);
            var score = calculateFitness(board2, numCleared);
            // removePiece();
            if (score > bestScore) {
                bestID = pieceIDs[i];
                bestCol = j;
                bestScore = score;
            }
        }
    }

    var result = []
    result.push(bestID);
    result.push(bestCol);
    result.push(bestScore); // potential
    return result;
}




function runSimulation() {
    nextPiece = generateRandomPiece();

    // copy board
    var board = [];
    for (var a = 0; a < Board.length; a++) {
        var newRow = [];
        for (var b = 0; b < Board[0].length; b++) {
            newRow.push(Board[a][b]);
        }
        board.push(newRow);
    }

    var data1 = findBest(board, currPiece);
    dropPiece(Board, data1[0], data1[1], currPiece);
    totalScore += removeClears(Board, true);

    currPiece = nextPiece;
    setTimeout(runSimulation, gameSpeed);

    //////////////////////////////////////////////////
    draw();
    // printBoard();
    if (gameOver()) {
        console.log("Game Over.");
        clearInterval(gameInterval);
    }
}

function main() {
    initialize();
    printBoard();
    draw();

    console.log("Game Start!\n");
    setTimeout(runSimulation, gameSpeed);
    console.log("Total Score: " + totalScore);
}

main();

