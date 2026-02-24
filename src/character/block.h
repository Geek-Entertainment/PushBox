#pragma once

#include <iostream>

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

extern std::ostream& DrawAtPoint(std::ostream& os, int x, int y, char spare = ' ');