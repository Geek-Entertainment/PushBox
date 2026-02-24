#pragma once

#include <character/block.h>

class Wall : public Block {
 public:
  Wall();
  Wall(int x, int y);
  Wall(const Wall& wall);
  Wall& operator=(const Wall& wall);
  ~Wall() override = default;

  void Draw() override;
  void Show() override;
};