#pragma once

#include <character/block.h>

class Person : public Block {
 public:
  Person();
  Person(int x, int y);
  Person(const Person& person);
  Person& operator=(const Person& person);
  ~Person() override = default;

  void Draw() override;
  void Show() override;
};