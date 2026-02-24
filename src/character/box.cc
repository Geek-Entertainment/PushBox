#include <character/box.h>

Box::Box() : Block() {}

Box::Box(int x, int y) : Block(x, y) {}

Box::Box(const Box& box) : Block(box) {}

Box& Box::operator=(const Box& box) {
  if (this != &box) {
    Block::operator=(box);
  }
  return *this;
}

void Box::Draw() { DrawAtPoint(std::cout, x_, y_, '#') << std::flush; }

void Box::Show() { Draw(); }