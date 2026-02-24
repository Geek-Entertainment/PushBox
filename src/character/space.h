#pragma once

#include <character/block.h>

class Space : public Block {
 public:
  Space();
  Space(bool box_start);
  Space(int x, int y);
  Space(const Space& space);
  Space& operator=(const Space& space);
  ~Space() override = default;

  void Draw() override;
  void Show() override;

 private:
  bool start_box_;
};