#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <sstream>
#include "GraphicsDisplay.h"
#include "Subject.h"
#include "SubjectType.h"
#include "SubscriberType.h"
#include "Info.h"
#include "TextDisplay.h"
// extern bool textOnly;

XWindow::XWindow(int width, int height): width(width), height(height) {
  // if(textOnly == true)

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    std::cerr << "Cannot open display" << std::endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[11][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown", "grey"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 11; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         std::cerr << "Bad colour: " << color_vals[i] << std::endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         std::cerr << "Bad colour: " << color_vals[i] << std::endl;
      }
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

XWindow::~XWindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void XWindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void XWindow::drawString(int x, int y, std::string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  Font f = XLoadFont(d, "6x13");
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}


void XWindow::drawBigString(int x, int y, std::string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
  std::ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";

  XFontStruct * f = XLoadQueryFont(d, name.str().c_str());
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f->fid;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}

void XWindow::showAvailableFonts() {
  int count;
  char** fnts = XListFonts(d, "*", 10000, &count);

  for (int i = 0; i < count; ++i) std::cout << fnts[i] << std::endl;
}




//constructor
GraphicsDisplay::GraphicsDisplay(int numRows, int numCols): NUM_ROWS{numRows}, NUM_COLS{numCols}{
  // Initialize current and previous vector of vector of chars
  for (int i = 0; i < NUM_ROWS; ++i) {
    std::vector<char> newRow;

    for (int j = 0; j < NUM_COLS; ++j) {
      newRow.emplace_back(' ');
    }

    prevBoardAllLetters.emplace_back(newRow);
    currentBoardAllLetters.emplace_back(newRow);
  }


  xwp = new XWindow(NUM_COLS*BLOCK_SIZE, (NUM_ROWS+NUM_BLOCKS_AFTER_BOARD)*BLOCK_SIZE);
  //the game
  for(int x=0;x<NUM_ROWS;++x){
    for(int y=0;y<NUM_COLS;++y){
      xwp->fillRectangle(y*BLOCK_SIZE, x*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, XWindow::White);
    }
  }
  //the info
  for(int x=NUM_ROWS;x<NUM_ROWS+NUM_BLOCKS_AFTER_BOARD;++x){
    for(int y=0;y<NUM_COLS;++y){
      xwp->fillRectangle(y*BLOCK_SIZE, x*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, XWindow::Grey);
    }
  }

  xwp->fillRectangle(0, NUM_ROWS*BLOCK_SIZE, NUM_COLS*BLOCK_SIZE, NUM_BLOCKS_AFTER_BOARD*BLOCK_SIZE, XWindow::Grey);
  DrawString(5, NUM_ROWS+1, "Level:    ");
  DrawString(5, NUM_ROWS+2, "Score:    ");
  DrawString(5, NUM_ROWS+3, "Hi Score: ");
  DrawString(5, NUM_ROWS+4, "Next: ");
}

void GraphicsDisplay::DrawString(const int pixelsRight, const int numBlocksDown, const std::string msg){
  xwp->drawString(pixelsRight, numBlocksDown*BLOCK_SIZE, msg);
}

//destructor
GraphicsDisplay::~GraphicsDisplay(){
  delete xwp;
}



void GraphicsDisplay::drawBlock(const char letter, const int row, const int col){
  XWindow::Colors color;
  if(letter == ' '){
    color = XWindow::White;
  } 
  else if(letter == 'O'){
    color = XWindow::Yellow;
  }
  else if(letter == 'S'){
    color = XWindow::Green;
  }
  else if(letter == 'T'){
    color = XWindow::Magenta;
  }
  else if(letter == 'Z'){
    color = XWindow::Red;
  }
  else if(letter == 'J'){
    color = XWindow::Blue;
  }
  else if(letter == 'I'){
    color = XWindow::Cyan;
  }
  else if(letter == 'L'){
    color = XWindow::Orange;
  }
  else if(letter == '*'){
    color = XWindow::Brown;
  }
  else{
    color = XWindow::Black;
  }
  xwp->fillRectangle(col*BLOCK_SIZE, row*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, color);
}

void GraphicsDisplay::PrintDisplay(const int newLevel, const int newCurrentScore, const int newHS, std::string newNextLevel) {
  for (int i = 0; i < NUM_ROWS; ++i){
    for (int j = 0; j < NUM_COLS; ++j){
      char actualLetter = currentBoardAllLetters[i][j];
      if(actualLetter != prevBoardAllLetters[i][j]){
        // std::cout << "Changed " << i << " " << j << " from " <<  prevBoardAllLetters[i][j] << " " << actualLetter << "\n"; 
        drawBlock(actualLetter, i, j);
      }
    }
  }

  xwp->fillRectangle(60, NUM_ROWS*BLOCK_SIZE, 4*BLOCK_SIZE, (NUM_BLOCKS_AFTER_BOARD-1)*BLOCK_SIZE, XWindow::Grey);

  DrawString(5, NUM_ROWS+1, "          " + std::to_string(newLevel));
  DrawString(5, NUM_ROWS+2, "          " + std::to_string(newCurrentScore));
  DrawString(5, NUM_ROWS+3, "          " + std::to_string(newHS));

  //Initial positions
  int initXPos=2; 

  int xPos=initXPos;
  int yPos=NUM_ROWS+4;
  for(char& c: newNextLevel){
    if(c=='\n'){
      xPos=initXPos;
      yPos++;
      continue;
    }
    xPos++;
    if(c==' '){continue;}
    drawBlock(c,yPos,xPos);
  }


  prevBoardAllLetters = currentBoardAllLetters;
}


//draws a new rectangle to reflect the updated cell's status
void GraphicsDisplay::Notify(Subject& notifier){
  if (notifier.GetSubjectType() == SubjectType::ROW) {
    currentBoardAllLetters.erase(currentBoardAllLetters.begin() + notifier.GetInfo().row);

    std::vector<char> newRow;

    for (int i = 0; i < NUM_COLS; ++i) {
      newRow.emplace_back(' ');
    }

    currentBoardAllLetters.insert(currentBoardAllLetters.begin(), newRow);
  } 
  else if (notifier.GetSubjectType() == SubjectType::CELL) {
    currentBoardAllLetters[notifier.GetInfo().row][notifier.GetInfo().col] = notifier.GetInfo().letter;
  }
}


//returns the SubscriberType
SubscriberType GraphicsDisplay::GetSubscriberType(){
  return SubscriberType::DISPLAY;
}
