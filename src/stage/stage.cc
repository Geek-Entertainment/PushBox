#include <character/box.h>
#include <character/person.h>
#include <character/space.h>
#include <character/wall.h>
#include <stage/stage.h>

#include <cassert>
#include <cstdlib>  // for std::rand, std::srand
#include <ctime>    // for std::time

static const std::size_t DefaultLevel = 1;
static const std::size_t DefaultSize = 10;  // 10x10 grid

Stage::Stage()
    : level_(DefaultLevel), person_x_(0), person_y_(0), height_(0), width_(0) {
  // seed random number generator once per program
  std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// fill blocks_ with random Box/Person/Wall/Space instances
void Stage::Init() {
  level_ = DefaultLevel;

  blocks_.clear();
  blocks_.resize(DefaultSize);
  for (std::size_t x = 0; x < DefaultSize; ++x) {
    blocks_[x].resize(DefaultSize);
    for (std::size_t y = 0; y < DefaultSize; ++y) {
      // pick type: 0=Box,1=Person,2=Wall,3=Space
      int t = std::rand() % 4;
      switch (t) {
        case 0:
          blocks_[x][y] =
              std::make_shared<Box>(static_cast<int>(x), static_cast<int>(y));
          break;
        case 1:
          blocks_[x][y] = std::make_shared<Person>(static_cast<int>(x),
                                                   static_cast<int>(y));
          break;
        case 2:
          blocks_[x][y] =
              std::make_shared<Wall>(static_cast<int>(x), static_cast<int>(y));
          break;
        default:
          blocks_[x][y] =
              std::make_shared<Space>(static_cast<int>(x), static_cast<int>(y));
          break;
      }
    }
  }
}

void Stage::Init(int level) {
  level_ = level;
  // for now ignore level and just recreate as random grid
  Init();
}

void Stage::Show() {
  clear();  // wipe previous contents
  for (const auto& row : blocks_) {
    for (const auto& block : row) {
      if (block) {
        block->Show();
      }
    }
    // do not print newline; screen is positioned by coordinates
  }
  refresh();  // flush to actual terminal
}

void Stage::MapRead(const std::vector<std::vector<char>>& map) {
  blocks_.clear();
  blocks_.resize(map.size());
  for (std::size_t x = 0; x < map.size(); ++x) {
    blocks_[x].resize(map[x].size());
    for (std::size_t y = 0; y < map[x].size(); ++y) {
      char c = map[x][y];
      switch (c) {
        case '#':
          blocks_[x][y] =
              std::make_shared<Box>(static_cast<int>(x), static_cast<int>(y));
          break;
        case 'P':
          blocks_[x][y] = std::make_shared<Person>(static_cast<int>(x),
                                                   static_cast<int>(y));
          if (person_x_ == 0 && person_y_ == 0) {
            person_x_ = static_cast<int>(x);
            person_y_ = static_cast<int>(y);
          } else {
            assert(false && "Error: Multiple 'P' characters in map");
          }
          break;
        case '0':
          blocks_[x][y] =
              std::make_shared<Wall>(static_cast<int>(x), static_cast<int>(y));
          break;
        case 'B':
          blocks_[x][y] = std::make_shared<Space>(true);
          break;
        default:
          blocks_[x][y] =
              std::make_shared<Space>(static_cast<int>(x), static_cast<int>(y));
          break;
      }
    }
  }
  height_ = static_cast<int>(blocks_.size());
  width_ = height_ > 0 ? static_cast<int>(blocks_[0].size()) : 0;
}

void Stage::RunRight() {
  if (person_y_ + 1 >= width_) return;  // out of bounds
  auto& next_block = blocks_[person_x_][person_y_ + 1];
  if (dynamic_cast<Wall*>(next_block.get())) {
    return;  // cannot move into wall
  } else if (dynamic_cast<Box*>(next_block.get())) {
    // try to push box
    if (person_y_ + 2 >= width_) return;  // out of bounds
    auto& next_next_block = blocks_[person_x_][person_y_ + 2];
    if (dynamic_cast<Wall*>(next_next_block.get()) ||
        dynamic_cast<Box*>(next_next_block.get())) {
      return;  // cannot push box into wall or another box
    }
    // push box
    next_next_block = std::make_shared<Box>(
        person_x_, person_y_ + 2);  // move box to next-next position
    next_block = std::make_shared<Person>(
        person_x_, person_y_ + 1);  // move person to next position
    blocks_[person_x_][person_y_] =
        std::make_shared<Space>(person_x_, person_y_);
    person_y_ += 1;
  } else {
    // move person to next position
    auto& current_block = blocks_[person_x_][person_y_];
    current_block = std::make_shared<Space>(person_x_, person_y_);
    person_y_ += 1;
    blocks_[person_x_][person_y_] =
        std::make_shared<Person>(person_x_, person_y_);
  }
}

void Stage::RunLeft() {
  if (person_y_ - 1 < 0) return;  // out of bounds
  auto& next_block = blocks_[person_x_][person_y_ - 1];
  if (dynamic_cast<Wall*>(next_block.get())) {
    return;  // cannot move into wall
  } else if (dynamic_cast<Box*>(next_block.get())) {
    // try to push box
    if (person_y_ - 2 < 0) return;  // out of bounds
    auto& next_next_block = blocks_[person_x_][person_y_ - 2];
    if (dynamic_cast<Wall*>(next_next_block.get()) ||
        dynamic_cast<Box*>(next_next_block.get())) {
      return;  // cannot push box into wall or another box
    }
    // push box
    next_next_block = std::make_shared<Box>(
        person_x_, person_y_ - 2);  // move box to next-next position
    next_block = std::make_shared<Person>(
        person_x_, person_y_ - 1);  // move person to next position
    blocks_[person_x_][person_y_] =
        std::make_shared<Space>(person_x_, person_y_);
    person_y_ -= 1;
  } else {
    // move person to next position
    auto& current_block = blocks_[person_x_][person_y_];
    current_block = std::make_shared<Space>(person_x_, person_y_);
    person_y_ -= 1;
    blocks_[person_x_][person_y_] =
        std::make_shared<Person>(person_x_, person_y_);
  }
}

void Stage::RunUp() {
  if (person_x_ - 1 < 0) return;  // out of bounds
  auto& next_block = blocks_[person_x_ - 1][person_y_];
  if (dynamic_cast<Wall*>(next_block.get())) {
    return;  // cannot move into wall
  } else if (dynamic_cast<Box*>(next_block.get())) {
    // try to push box
    if (person_x_ - 2 < 0) return;  // out of bounds
    auto& next_next_block = blocks_[person_x_ - 2][person_y_];
    if (dynamic_cast<Wall*>(next_next_block.get()) ||
        dynamic_cast<Box*>(next_next_block.get())) {
      return;  // cannot push box into wall or another box
    }
    // push box
    next_next_block = std::make_shared<Box>(
        person_x_ - 2, person_y_);  // move box to next-next position
    next_block = std::make_shared<Person>(
        person_x_ - 1, person_y_);  // move person to next position
    blocks_[person_x_][person_y_] =
        std::make_shared<Space>(person_x_, person_y_);
    person_x_ -= 1;
  } else {
    // move person to next position
    auto& current_block = blocks_[person_x_][person_y_];
    current_block = std::make_shared<Space>(person_x_, person_y_);
    person_x_ -= 1;
    blocks_[person_x_][person_y_] =
        std::make_shared<Person>(person_x_, person_y_);
  }
}

void Stage::RunDown() {
  if (person_x_ + 1 >= height_) return;  // out of bounds
  auto& next_block = blocks_[person_x_ + 1][person_y_];
  if (dynamic_cast<Wall*>(next_block.get())) {
    return;  // cannot move into wall
  } else if (dynamic_cast<Box*>(next_block.get())) {
    // try to push box
    if (person_x_ + 2 >= height_) return;  // out of bounds
    auto& next_next_block = blocks_[person_x_ + 2][person_y_];
    if (dynamic_cast<Wall*>(next_next_block.get()) ||
        dynamic_cast<Box*>(next_next_block.get())) {
      return;  // cannot push box into wall or another box
    }
    // push box
    next_next_block = std::make_shared<Box>(
        person_x_ + 2, person_y_);  // move box to next-next position
    next_block = std::make_shared<Person>(
        person_x_ + 1, person_y_);  // move person to next position
    blocks_[person_x_][person_y_] =
        std::make_shared<Space>(person_x_, person_y_);
    person_x_ += 1;
  } else {
    // move person to next position
    auto& current_block = blocks_[person_x_][person_y_];
    current_block = std::make_shared<Space>(person_x_, person_y_);
    person_x_ += 1;
    blocks_[person_x_][person_y_] =
        std::make_shared<Person>(person_x_, person_y_);
  }
}