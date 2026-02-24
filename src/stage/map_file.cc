#include <stage/map_file.h>

#include <fstream>
#include <iostream>

MapFile::MapFile() : filename_("") {}

std::vector<std::vector<char>> MapFile::Read(const std::string& filename) {
  filename_ = filename;
  std::ifstream infile(filename_);
  if (!infile.is_open()) {
    std::cerr << "Error opening file: " << filename_ << std::endl;
    return {};
  }

  std::string map_line;
  std::string::size_type map_line_size = 0;
  std::vector<std::vector<char>> result_map;
  while (std::getline(infile, map_line)) {
    if (map_line_size == 0) {
      map_line_size = map_line.size();
    } else if (map_line.size() != map_line_size) {
      std::cerr << "Error: Inconsistent line lengths in map file: " << filename_
                << std::endl;
      return {};
    }
    result_map.push_back({});
    for (char c : map_line) {
      result_map.back().push_back(c);
    }
  }
  return result_map;
}