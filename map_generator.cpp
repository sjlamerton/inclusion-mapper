// Copyright: 2015 Steven Lamerton
// License: MIT, see LICENSE

#include <llvm/Support/raw_ostream.h>
#include "map_generator.h"

void MapGenerator::AddInclusion(std::pair<std::string, std::string> inclusion) {
  inclusions_.insert(inclusion);
}

void MapGenerator::AddSystemFile(std::string path) {
  system_files_.insert(path);
}

void MapGenerator::PrintMap() {
  llvm::outs() << "digraph name {\n";
  for (auto& pair : inclusions_) {
    llvm::outs() << "\"" << pair.first << "\""
                 << " -> "
                 << "\"" << pair.second << "\""
                 << ";\n";
  }
  llvm::outs() << "}\n";
}

void MapGenerator::RemoveSystemInclusions() {
  for (auto it = inclusions_.begin(); it != inclusions_.end(); ) {
    if (system_files_.find(it->second) != system_files_.end()) {
     inclusions_.erase(it++);
    } else {
      ++it;
    }
  }
}
