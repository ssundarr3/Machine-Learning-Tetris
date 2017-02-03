/**
 * Created by Raymond Zheng on 2/3/2017.
 */
"use strict";

// Aliases
var Container = PIXI.Container,
    autoDetectRenderer = PIXI.autoDetectRenderer,
    loader = PIXI.loader,
    resources = PIXI.loader.resources,
    Sprite = PIXI.Sprite,
    TextureCache = PIXI.utils.TextureCache,
    Rectangle = PIXI.Rectangle;


// Create the renderer
var renderer = autoDetectRenderer(512, 768);
renderer.backgroundColor = 0x061639;


// Loading images
loader
    .add("img/blockTexture.json")
    .load(setup);

function setup() {

    //Create the `tileset` sprite from the texture
    var id = PIXI.loader.resources["img/blockTexture.json"].textures;

    var OBLOCK = new Sprite(id["O.png"]);

    var IBLOCK1 = new Sprite(id["I1.png"]);
    var IBLOCK2 = new Sprite(id["I2.png"]);

    var JBLOCK1 = new Sprite(id["J1.png"]);
    var JBLOCK2 = new Sprite(id["J2.png"]);
    var JBLOCK3 = new Sprite(id["J3.png"]);
    var JBLOCK4 = new Sprite(id["J4.png"]);

    var LBLOCK1 = new Sprite(id["L1.png"]);
    var LBLOCK2 = new Sprite(id["L2.png"]);
    var LBLOCK3 = new Sprite(id["L3.png"]);
    var LBLOCK4 = new Sprite(id["L4.png"]);

    var TBLOCK1 = new Sprite(id["T1.png"]);
    var TBLOCK2 = new Sprite(id["T2.png"]);
    var TBLOCK3 = new Sprite(id["T3.png"]);
    var TBLOCK4 = new Sprite(id["T4.png"]);

    var SBLOCK1 = new Sprite(id["S1.png"]);
    var SBLOCK2 = new Sprite(id["S2.png"]);

    var ZBLOCK1 = new Sprite(id["Z1.png"]);
    var ZBLOCK2 = new Sprite(id["Z2.png"]);
    //
    // texture.frame = new Rectangle(150, 200, 42, 42);
    // var oBlock = new Sprite(texture);
    //
    // texture.frame = new Rectangle(200, 200, 21, 84);
    // var iBlock1 = new Sprite(texture);
    // texture.frame = new Rectangle(200, 299, 84, 21);
    // var iBlock2 = new Sprite(texture);
    //
    // texture.frame = new Rectangle(0, 0, 42, 64);
    // var jBlock1 = new Sprite(texture);
    // texture.frame = new Rectangle(64, 0, 64, 42);
    // var jBlock2 = new Sprite(texture);
    // texture.frame = new Rectangle(128, 0, 42, 64);
    // var jBlock3 = new Sprite(texture);
    // texture.frame = new Rectangle(192, 0, 64, 42);
    // var jBlock4 = new Sprite(texture);
    //
    // texture.frame = new Rectangle(0, 64, 42, 64);
    // var lBlock1 = new Sprite(texture);
    // texture.frame = new Rectangle(64, 64, 64, 42);
    // var lBlock2 = new Sprite(texture);
    // texture.frame = new Rectangle(128, 64, 42, 64);
    // var lBlock3 = new Sprite(texture);
    // texture.frame = new Rectangle(192, 64, 64, 42);
    // var lBlock4 = new Sprite(texture);
    //
    // texture.frame = new Rectangle(0, 128, 64, 42);
    // var tBlock1 = new Sprite(texture);
    // texture.frame = new Rectangle(64, 128, 42, 64);
    // var tBlock2 = new Sprite(texture);
    // texture.frame = new Rectangle(128, 128, 64, 42);
    // var tBlock3 = new Sprite(texture);
    // texture.frame = new Rectangle(192, 128, 42, 64);
    // var tBlock4 = new Sprite(texture);
    //
    // texture.frame = new Rectangle(0, 192, 64, 42);
    // var sBlock1 = new Sprite(texture);
    // texture.frame = new Rectangle(64, 192, 42, 64);
    // var sBlock2 = new Sprite(texture);
    //
    // texture.frame = new Rectangle(0, 256, 64, 42);
    // var zBlock1 = new Sprite(texture);
    // texture.frame = new Rectangle(64, 256, 42, 64);
    // var zBlock2 = new Sprite(texture);


    OBLOCK.x = 32;
    OBLOCK.y = 32;

    stage.addChild(OBLOCK);

    renderer.render(stage);
}


//Add the canvas to the HTML document
document.body.appendChild(renderer.view);

//Create a container object called the `stage`
var stage = new Container();

//Tell the `renderer` to `render` the `stage`
renderer.render(stage);