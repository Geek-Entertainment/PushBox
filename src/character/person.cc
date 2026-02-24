#include <character/person.h>

Person::Person() : Block() {}

Person::Person(int x, int y) : Block(x, y) {}

Person::Person(const Person& person) : Block(person) {}

Person& Person::operator=(const Person& person) {
  if (this != &person) {
    Block::operator=(person);
  }
  return *this;
}

void Person::Draw() { DrawAtPoint(std::cout, x_, y_, 'P') << std::flush; }

void Person::Show() { Draw(); }