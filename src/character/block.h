#pragma once

#include <ncurses.h>  // for mvaddch, printw, etc.

// helper to draw a character at (x,y) using ncurses.
// curses uses (row, col) == (y, x).
inline void DrawAtPoint(int x, int y, char ch = ' ') { mvaddch(x, y, ch); }

class Block {
 public:
  Block();
  Block(int x, int y);
  Block(const Block& block);
  Block& operator=(const Block& block);
  virtual ~Block() = default;

  virtual void Draw() = 0;
  virtual void Show() = 0;

 protected:
  int x_;
  int y_;
};
