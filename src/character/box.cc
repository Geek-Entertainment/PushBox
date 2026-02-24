#include <character/box.h>
#include <ncurses.h>

Box::Box() : Block() {}

Box::Box(int x, int y) : Block(x, y) {}

Box::Box(const Box& box) : Block(box) {}

Box& Box::operator=(const Box& box) {
  if (this != &box) {
    Block::operator=(box);
  }
  return *this;
}

void Box::Draw() { DrawAtPoint(x_, y_, '#'); }

void Box::Show() { Draw(); }