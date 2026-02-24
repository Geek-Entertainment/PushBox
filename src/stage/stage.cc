#include <character/box.h>
#include <character/person.h>
#include <character/space.h>
#include <character/wall.h>
#include <stage/stage.h>

#include <cstdlib>  // for std::rand, std::srand
#include <ctime>    // for std::time

static const std::size_t DefaultLevel = 1;
static const std::size_t DefaultSize = 10;  // 10x10 grid

Stage::Stage() : level_(DefaultLevel) {
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
  for (const auto& row : blocks_) {
    for (const auto& block : row) {
      if (block) {
        block->Show();
      }
    }
  }
}