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


// Constants
var CUBE_SIZE = 21;

// Aliases
var Container = PIXI.Container,
    autoDetectRenderer = PIXI.autoDetectRenderer,
    loader = PIXI.loader,
    resources = PIXI.loader.resources,
    Sprite = PIXI.Sprite,
    TextureCache = PIXI.utils.TextureCache,
    Rectangle = PIXI.Rectangle,
    graphics = new PIXI.Graphics();



var renderer = autoDetectRenderer(10 * CUBE_SIZE + 3, 30 * CUBE_SIZE);

renderer.backgroundColor = 0x061639;



// Loading images
loader
    .add("img/blockTexture.json")
    .load(setup);

var pieceSprites = [];
var pieceHolder = [];

function setup() {

    //Create the `tileset` sprite from the texture
    var id = PIXI.loader.resources["img/blockTexture.json"].textures;

    pieceSprites.push("O.png");
    pieceSprites.push("I.png");
    pieceSprites.push("J.png");
    pieceSprites.push("L.png");
    pieceSprites.push("T.png");
    pieceSprites.push("S.png");
    pieceSprites.push("Z.png");
    pieceSprites.push("X.png");
}

function drawReset() {
    var length = stage.children.length;
    for (var i = 0; i < length; i++) {
        stage.removeChild(stage.children[0]);
    }

    // renderer.render(stage);
}

function drawPiece(x, y, pieceID) {
    var id = PIXI.loader.resources["img/blockTexture.json"].textures;
    var newPiece = new Sprite(id[pieceSprites[pieceID]]);
    // pieceHolder.push(newPiece);
    newPiece.x = x * CUBE_SIZE;
    newPiece.y = y * CUBE_SIZE;
    stage.addChild(newPiece);
    renderer.render(stage);
}

//Add the canvas to the HTML document
document.body.appendChild(renderer.view);

//Create a container object called the `stage`
var stage = new Container();

//Tell the `renderer` to `render` the `stage`
renderer.render(stage);
