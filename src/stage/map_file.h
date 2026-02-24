#pragma once

#include <string>
#include <vector>

class MapFile {
 public:
  MapFile();
  ~MapFile() = default;

  std::vector<std::vector<char>> Read(const std::string& filename);

 private:
  std::string filename_;
};