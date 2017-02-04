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
    Rectangle = PIXI.Rectangle;


// Create the renderer
var renderer = autoDetectRenderer(10 * CUBE_SIZE, 20 * CUBE_SIZE);
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


    // pieceSprites.push(new Sprite(id["O.png"]));
    // pieceSprites.push(new Sprite(id["I.png"]));
    // pieceSprites.push(new Sprite(id["J.png"]));
    // pieceSprites.push(new Sprite(id["L.png"]));
    // pieceSprites.push(new Sprite(id["T.png"]));
    // pieceSprites.push(new Sprite(id["S.png"]));
    // pieceSprites.push(new Sprite(id["Z.png"]));

    // var OBLOCK = new Sprite(id["O1.png"]);
    //
    // var IBLOCK1 = new Sprite(id["I1.png"]);
    // var IBLOCK2 = new Sprite(id["I2.png"]);
    //
    // var JBLOCK1 = new Sprite(id["J1.png"]);
    // var JBLOCK2 = new Sprite(id["J2.png"]);
    // var JBLOCK3 = new Sprite(id["J3.png"]);
    // var JBLOCK4 = new Sprite(id["J4.png"]);
    //
    // var LBLOCK1 = new Sprite(id["L1.png"]);
    // var LBLOCK2 = new Sprite(id["L2.png"]);
    // var LBLOCK3 = new Sprite(id["L3.png"]);
    // var LBLOCK4 = new Sprite(id["L4.png"]);
    //
    // var TBLOCK1 = new Sprite(id["T1.png"]);
    // var TBLOCK2 = new Sprite(id["T2.png"]);
    // var TBLOCK3 = new Sprite(id["T3.png"]);
    // var TBLOCK4 = new Sprite(id["T4.png"]);
    //
    // var SBLOCK1 = new Sprite(id["S1.png"]);
    // var SBLOCK2 = new Sprite(id["S2.png"]);
    //
    // var ZBLOCK1 = new Sprite(id["Z1.png"]);
    // var ZBLOCK2 = new Sprite(id["Z2.png"]);
    //
    // pieceSprites.push(OBLOCK);
    // pieceSprites.push(IBLOCK1);
    // pieceSprites.push(IBLOCK2);
    // pieceSprites.push(JBLOCK1);
    // pieceSprites.push(JBLOCK2);
    // pieceSprites.push(JBLOCK3);
    // pieceSprites.push(JBLOCK4);
    // pieceSprites.push(LBLOCK1);
    // pieceSprites.push(LBLOCK2);
    // pieceSprites.push(LBLOCK3);
    // pieceSprites.push(LBLOCK4);
    // pieceSprites.push(TBLOCK1);
    // pieceSprites.push(TBLOCK2);
    // pieceSprites.push(TBLOCK3);
    // pieceSprites.push(TBLOCK4);
    // pieceSprites.push(SBLOCK1);
    // pieceSprites.push(SBLOCK2);
    // pieceSprites.push(ZBLOCK1);
    // pieceSprites.push(ZBLOCK2);
}

function drawPiece(x, y, pieceID) {
    var id = PIXI.loader.resources["img/blockTexture.json"].textures;
    var newPiece = new Sprite(id[pieceSprites[pieceID]]);
    pieceHolder.push(newPiece);
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