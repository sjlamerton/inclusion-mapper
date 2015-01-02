// Copyright: 2015 Steven Lamerton
// License: MIT, see LICENSE
#ifndef MAP_GENERATOR_H_
#define MAP_GENERATOR_H_

#include <set>

typedef std::pair<std::string, std::string> Inclusion;

class MapGenerator {
 public:
  void AddInclusion(Inclusion inclusion);
  void PrintMap();

 private:
  std::set<Inclusion> inclusions_;
};

#endif

