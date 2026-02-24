#include <character/wall.h>
#include <ncurses.h>

Wall::Wall() : Block() {}

Wall::Wall(int x, int y) : Block(x, y) {}

Wall::Wall(const Wall& wall) : Block(wall) {}

Wall& Wall::operator=(const Wall& wall) {
  if (this != &wall) {
    Block::operator=(wall);
  }
  return *this;
}

void Wall::Draw() { DrawAtPoint(x_, y_, '0'); }

void Wall::Show() { Draw(); }