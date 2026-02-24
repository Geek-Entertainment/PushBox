#include <character/person.h>
#include <ncurses.h>

Person::Person() : Block() {}

Person::Person(int x, int y) : Block(x, y) {}

Person::Person(const Person& person) : Block(person) {}

Person& Person::operator=(const Person& person) {
  if (this != &person) {
    Block::operator=(person);
  }
  return *this;
}

void Person::Draw() { DrawAtPoint(x_, y_, 'P'); }

void Person::Show() { Draw(); }