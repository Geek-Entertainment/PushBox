#include <character/space.h>

Space::Space() : Block(), start_box_(false) {}

Space::Space(bool box_start) : Block(), start_box_(box_start) {}

Space::Space(int x, int y) : Block(x, y) {}

Space::Space(const Space& space) : Block(space), start_box_(space.start_box_) {}

Space& Space::operator=(const Space& space) {
  if (this != &space) {
    Block::operator=(space);
  }
  return *this;
}

void Space::Draw() {
  if (start_box_) {
    DrawAtPoint(x_, y_, 'B');
  } else {
    DrawAtPoint(x_, y_, ' ');
  }
}

void Space::Show() { Draw(); }