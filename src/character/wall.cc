#include <character/wall.h>

Wall::Wall() : Block() {}

Wall::Wall(int x, int y) : Block(x, y) {}

Wall::Wall(const Wall& wall) : Block(wall) {}

Wall& Wall::operator=(const Wall& wall) {
  if (this != &wall) {
    Block::operator=(wall);
  }
  return *this;
}

void Wall::Draw() { DrawAtPoint(std::cout, x_, y_, '0') << std::flush; }

void Wall::Show() { Draw(); }