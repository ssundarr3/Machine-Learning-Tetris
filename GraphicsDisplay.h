#ifndef GRAPHICS_DISPLAY
#define GRAPHICS_DISPLAY
#include <utility>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <vector>
#include <string>
#include <iostream>
#include "Observer.h"

class Subject;
class TextDisplay;
enum class SubscriberType;

class XWindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  int width, height;

 public:
  XWindow(int width=500, int height=500);  // Constructor; displays the window.
  ~XWindow();                              // Destructor; destroys the window.
  XWindow(const XWindow&) = delete;
  XWindow &operator=(const XWindow&) = delete;

  enum Colors {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown, Grey}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour=Black);

  // Draws a string
  void drawBigString(int x, int y, std::string msg, int colour=Black);

  // Prints the first 10000 available fonts
  void showAvailableFonts();
};

class GraphicsDisplay: public Observer{
  XWindow *xwp;
  std::vector<std::vector<char>> prevBoardAllLetters;
  std::vector<std::vector<char>> currentBoardAllLetters;
  const int NUM_ROWS;
  const int NUM_COLS;
  const int BLOCK_SIZE=20;
  const int NUM_BLOCKS_AFTER_BOARD=7;

  public:
    void drawBlock(const char , const int , const int);
    void PrintDisplay(const int, const int, const int, std::string);
    void DrawString(const int , const int, const std::string);
    GraphicsDisplay(int, int);
    ~GraphicsDisplay() override;

    void Notify(Subject&) override;
    SubscriberType GetSubscriberType() override;
};

#endif



