#pragma once

#include <character/block.h>

class Box : public Block {
 public:
  Box();
  Box(int x, int y);
  Box(const Box& box);
  Box& operator=(const Box& box);
  ~Box() override = default;

  void Draw() override;
  void Show() override;
};