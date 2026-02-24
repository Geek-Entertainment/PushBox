#pragma once

#include <character/block.h>

#include <memory>
#include <vector>

class Stage {
 public:
  Stage();
  ~Stage() = default;

  void Init();
  void Init(int level);
  void Show();

  void MapRead(const std::vector<std::vector<char>>& map);

  void RunRight();
  void RunLeft();
  void RunUp();
  void RunDown();

 private:
  std::vector<std::vector<std::shared_ptr<Block>>> blocks_;

  std::size_t level_;

  int person_x_;
  int person_y_;
  int height_;
  int width_;
};