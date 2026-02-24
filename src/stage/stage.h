#pragma once

#include <vector>
#include <memory>

#include <character/block.h>

class Stage {
 public:
  Stage();
  ~Stage() = default;

  void Init();
  void Init(int level);
  void Show();

 private:
  std::vector<std::vector<std::shared_ptr<Block>>> blocks_;

  std::size_t level_;
};