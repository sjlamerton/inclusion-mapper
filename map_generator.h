// Copyright: 2015 Steven Lamerton
// License: MIT, see LICENSE
#ifndef MAP_GENERATOR_H_
#define MAP_GENERATOR_H_

#include <set>
#include <string>

class MapGenerator {
 public:
  void AddInclusion(std::pair<std::string, std::string> inclusion);
  void AddSystemFile(std::string path);
  void PrintMap();
  void RemoveSystemInclusions();

 private:
  std::set<std::pair<std::string, std::string>> inclusions_;
  std::set<std::string> system_files_;
};

#endif

