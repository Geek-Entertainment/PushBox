#include <character/block.h>

Block::Block() : x_(0), y_(0) {}

Block::Block(int x, int y) : x_(x), y_(y) {}

Block::Block(const Block& block) : x_(block.x_), y_(block.y_) {}

Block& Block::operator=(const Block& block) {
  if (this != &block) {
    x_ = block.x_;
    y_ = block.y_;
  }
  return *this;
}

std::ostream& DrawAtPoint(std::ostream& os, int x, int y, char spare) {
  os << "\033[" << y << ";" << x << "H" << spare;
  return os;
}